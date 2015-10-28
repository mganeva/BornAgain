// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/SavePlotAssistant.cpp
//! @brief     Implements class SavePlotAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SavePlotAssistant.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"
#include "IntensityDataIOFactory.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

namespace {
const QString png_extension = ".png";
const QString jpg_extension = ".jpg";
const QString pdf_extension = ".pdf";
const QString int_extension = ".int";
const QString tif_extension = ".tif";

QVector<SavePlotAssistant::Format> initializeFormats() {
    QVector<SavePlotAssistant::Format> result;
    result.push_back(SavePlotAssistant::Format(png_extension, "*.png"));
    result.push_back(SavePlotAssistant::Format(jpg_extension, "*.jpg"));
    result.push_back(SavePlotAssistant::Format(pdf_extension, "*.pdf"));
    result.push_back(SavePlotAssistant::Format(int_extension, "BornAgain ASCII format (*.int)"));
#ifdef BORNAGAIN_TIFF_SUPPORT
    result.push_back(SavePlotAssistant::Format(tif_extension, "32-bits TIFF files (*.tif)"));
#endif
    return result;
}

}

QVector<SavePlotAssistant::Format> SavePlotAssistant::m_formats = initializeFormats();

SavePlotAssistant::Format::Format(const QString &file_extention, const QString &filter)
    : m_file_extention(file_extention)
    , m_filter(filter)
{

}

void SavePlotAssistant::savePlot(const QString &dirname, ColorMapPlot *plot,
                                 IntensityDataItem *item)

{
    QString selectedFilter("*.png");
    QString defaultName = dirname + QString("/untitled");
    QString fileName =QFileDialog::getSaveFileName(0, "Save Plot", defaultName,
        getFilterString(), &selectedFilter);

    QString nameToSave = composeFileName(fileName, selectedFilter);
    qDebug() << "XXX savePLot fileName:" << fileName
             << "selectedFilter:" << selectedFilter
             << "nameToSave" << nameToSave;

    if(!nameToSave.isEmpty()) {
        try {
            saveToFile(nameToSave, plot, item);
        } catch(const std::exception &ex) {
            QString message = "Attempt to save file with the name '";
            message.append(nameToSave);
            message.append("' has failed with following error message\n\n");
            message.append(QString::fromStdString(ex.what()));
            QMessageBox::warning(0, "Houston, we have a problem.", message);
        }
    }

}

void SavePlotAssistant::saveToFile(const QString &fileName, ColorMapPlot *plot, IntensityDataItem *item)
{
    if(isPngFile(fileName)) {
        plot->getCustomPlot()->savePng(fileName);
    }

    else if(isJpgFile(fileName)) {
        plot->getCustomPlot()->saveJpg(fileName);
    }

    else if(isPdfFile(fileName)) {
        plot->getCustomPlot()->savePdf(fileName, true, plot->width(), plot->height());
    }

    else {
        IntensityDataIOFactory::writeOutputData(*item->getOutputData(),
                                                fileName.toStdString());
    }
}

//! Returns string contraining all defined filters in the format suitable for QFileDialog
QString SavePlotAssistant::getFilterString() const
{
    QString result;
    for(int i=0; i<m_formats.size(); ++i) {
        result.append(m_formats[i].m_filter);
        if(i!=m_formats.size()-1) result.append(";;");
    }
    return result;
}

//! Compose file name to save plot from information provided by QFileDialog
QString SavePlotAssistant::composeFileName(const QString &fileName, const QString &filterName) const
{
    QString result;
    if (!fileName.isEmpty() && !filterName.isEmpty()) {
        if(isValidExtension(fileName)) {
            result = fileName;
        } else {
            result = fileName + getExtensionFromFilterName(filterName);
        }
    }
    return result;
}

bool SavePlotAssistant::isValidExtension(const QString &fileName) const
{
    for(int i=0; i<m_formats.size(); ++i) {
        if(fileName.endsWith(m_formats[i].m_file_extention, Qt::CaseInsensitive)) {
            return true;
        }
    }
    return false;
}

QString SavePlotAssistant::getExtensionFromFilterName(const QString &filterName) const
{
    for(int i=0; i<m_formats.size(); ++i) {
        if(m_formats[i].m_filter == filterName) {
            return m_formats[i].m_file_extention;
        }
    }
    return QString();
}

bool SavePlotAssistant::isPngFile(const QString &fileName) const
{
    return fileName.endsWith(png_extension, Qt::CaseInsensitive);
}

bool SavePlotAssistant::isJpgFile(const QString &fileName) const
{
    return fileName.endsWith(jpg_extension, Qt::CaseInsensitive);
}

bool SavePlotAssistant::isPdfFile(const QString &fileName) const
{
    return fileName.endsWith(pdf_extension, Qt::CaseInsensitive);
}
