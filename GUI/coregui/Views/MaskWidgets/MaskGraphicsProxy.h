// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskGraphicsProxy.h
//! @brief     Defines class MaskGraphicsProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKGRAPHICSPROXY_H
#define MASKGRAPHICSPROXY_H

#include "ColorMapPlot.h"
#include "MaskEditorHelper.h"
#include <QGraphicsProxyWidget>

class ParameterizedItem;
class ISceneAdaptor;
class ColorMapSceneAdaptor;

//! Graphics proxy to place QWidget inside QGraphicsScene, used by MaskEditorCanvas.

class MaskGraphicsProxy : public QGraphicsProxyWidget
{
    Q_OBJECT

public:
    MaskGraphicsProxy();
    virtual ~MaskGraphicsProxy();

    int type() const { return MaskEditorHelper::MASKGRAPHICSPROXY; }

    void setItem(ParameterizedItem *item);
    void setSceneAdaptor(ISceneAdaptor *sceneAdaptor);
    void setInZoomMode(bool value);

    void resetView();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);

private:
    ColorMapPlot *m_colorMap;
    ColorMapSceneAdaptor *m_sceneAdaptor;
    bool m_send_signals_to_colormap;
};

#endif