// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataView.h
//! @brief     Declares class ImportDataView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef IMPORTDATAVIEW_H
#define IMPORTDATAVIEW_H

#include "WinDllMacros.h"
#include "ItemStackPresenter.h"
#include "RealDataEditorWidget.h"
#include <QWidget>

class ImportDataToolBar;
class QSplitter;
class ItemSelectorWidget;
class RealDataModel;

//! The ImportDataView class is a main view for importing experimental data.

class BA_CORE_API_ ImportDataView : public QWidget
{
    Q_OBJECT

public:
    ImportDataView(class MainWindow *mainWindow);

public slots:
    void onSelectionChanged(SessionItem *item);

private:
    void setupConnections();

    ImportDataToolBar *m_toolBar;
    QSplitter *m_splitter;
    ItemSelectorWidget *m_selectorWidget;
    ItemStackPresenter<RealDataEditorWidget> *m_stackedWidget;
    RealDataModel *m_realDataModel;
};

#endif
