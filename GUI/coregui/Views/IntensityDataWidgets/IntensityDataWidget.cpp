// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.cpp
//! @brief     Implements class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IntensityDataWidget.h"
#include "IntensityDataPlotWidget.h"
#include "IntensityDataPropertyWidget.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "ModelMapper.h"
#include <QVBoxLayout>
#include <QDebug>


IntensityDataWidget::IntensityDataWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_plotWidget(0)
    , m_propertyWidget(0)
    , m_currentItem(0)
{
    setMinimumSize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("IntensityDataWidget"));
    setObjectName(QLatin1String("IntensityDataWidget"));

    m_plotWidget = new IntensityDataPlotWidget(this);
    connect(m_plotWidget, SIGNAL(savePlotRequest()), this, SIGNAL(savePlotRequest()));

    m_propertyWidget = new IntensityDataPropertyWidget(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

    hlayout->addWidget(m_plotWidget);
    hlayout->addWidget(m_propertyWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);
}


void IntensityDataWidget::setItem(SessionItem *item)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(item);
    Q_ASSERT(jobItem);
    setIntensityData(jobItem->getIntensityDataItem());
}

void IntensityDataWidget::setIntensityData(IntensityDataItem *intensityItem)
{
    m_plotWidget->setItem(intensityItem);
    m_propertyWidget->setItem(intensityItem);

    if (m_currentItem == intensityItem) {
        return;

    } else {
        if(m_currentItem)
            m_currentItem->mapper()->unsubscribe(this);

        m_currentItem = intensityItem;
        if (!m_currentItem) return;

        setPropertyPanelVisible(m_currentItem->getItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool());

        m_currentItem->mapper()->setOnPropertyChange(
                     [this](const QString &name)
        {
            if(name == IntensityDataItem::P_PROPERTY_PANEL_FLAG) {
                setPropertyPanelVisible(m_currentItem->getItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool());
            }
        }, this);
    }

}

void IntensityDataWidget::togglePropertyPanel()
{
    if(m_currentItem) {
        bool current_flag = m_currentItem->getItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool();
        m_currentItem->setItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG, !current_flag);
    }
}

void IntensityDataWidget::setPropertyPanelVisible(bool visible)
{
    if(visible) {
        m_propertyWidget->setItem(m_currentItem);

    } else {
        m_propertyWidget->setItem(0);
    }
    m_propertyWidget->setVisible(visible);
}

void IntensityDataWidget::toggleProjections()
{
    if(m_currentItem) {
        bool current_flag = m_currentItem->getItemValue(IntensityDataItem::P_PROJECTIONS_FLAG).toBool();
        m_currentItem->setItemValue(IntensityDataItem::P_PROJECTIONS_FLAG, !current_flag);
    }
}

void IntensityDataWidget::onResetView()
{
    m_plotWidget->resetView();
}

void IntensityDataWidget::savePlot(const QString &dirname)
{
    m_plotWidget->savePlot(dirname);
}
