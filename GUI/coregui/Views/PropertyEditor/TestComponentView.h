// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/TestComponentView.h
//! @brief     Defines class TestComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TESTCOMPONENTVIEW_H
#define TESTCOMPONENTVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class MainWindow;
class QPushButton;
class ComponentProxyModel;
class QTreeView;
class SampleModel;
class SessionModelDelegate;

//! View to tests QListView working with ComponentProxyModel.

class TestComponentView : public QWidget
{
    Q_OBJECT
public:
    TestComponentView(MainWindow *mainWindow = nullptr);

private slots:
    void onUpdateRequest();
    void onAddItemRequest();

private:
    void init_source();

    MainWindow* m_mainWindow;
    SampleModel* m_sourceModel;
    ComponentProxyModel* m_proxyModel;
    QTreeView* m_sourceTree;
    QTreeView* m_proxyTree;
    QPushButton* m_updateButton;
    QPushButton* m_addItemButton;
    SessionModelDelegate* m_delegate;
};

#endif // TESTCOMPONENTVIEW_H
