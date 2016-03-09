// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleViewComponents.cpp
//! @brief     Implements class SampleViewComponents
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleViewComponents.h"
#include "widgetbox.h"
#include "SampleDesigner.h"
#include "SampleViewProxyModel.h"


SampleWidgetBox *SampleViewComponents::createWidgetBox(
        SampleDesignerInterface *core, QWidget *parent)
{
    return new SampleWidgetBox(core, parent);
}

ItemTreeView *SampleViewComponents::createTreeView(
        SampleModel *sampleModel, QWidget *parent)
{
    ItemTreeView *tree_view = new ItemTreeView(parent);
    SampleViewProxyModel *proxy = new SampleViewProxyModel(parent);
    proxy->setSourceModel(sampleModel);
    tree_view->setModel(proxy);
    return tree_view;
}



