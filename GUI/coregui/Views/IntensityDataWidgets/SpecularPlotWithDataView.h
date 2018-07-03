// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularPlotWithDataView.h
//! @brief     Defines class SpecularPlotWithDataView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARPLOTWITHDATAVIEW_H
#define SPECULARPLOTWITHDATAVIEW_H

#include "ScientificPlot.h"
#include "qcustomplot.h"

class BasicAxisItem;
class DataItem;
class DataItem1DView;
class Data1DProperties;
class SpecularPlotEvent;
class UpdateTimer;

//! The SpecularPlotWithDataView class presents data of several 1D DataItems contained in a
//! DataItem1DView. Provides minimal functionality for data plotting and axes interaction. Should be
//! a component for more complicated plotting widgets.

class SpecularPlotWithDataView : public ScientificPlot
{
    Q_OBJECT

public:
    explicit SpecularPlotWithDataView(QWidget* parent = nullptr);

    QSize sizeHint() const override { return QSize(500, 400); }
    QSize minimumSizeHint() const override { return QSize(128, 128); }

    //! Returns PlotEventInfo corresponding to given axes coordinates.
    PlotEventInfo eventInfo(double xpos, double ypos) const override;

    QCustomPlot* customPlot() override { return m_custom_plot; }
    const QCustomPlot* customPlot() const override { return m_custom_plot; }

    //! sets logarithmic scale
    void setLog(bool log);

    //! reset all axes min,max to initial value
    void resetView();

private slots:
    //! updates plot depending on  IntensityDataItem properties
    void onPropertyChanged(const QString& property_name);

    //! Propagate xmin, xmax back to IntensityDataItem
    void onXaxisRangeChanged(QCPRange newRange);

    //! Propagate ymin, ymax back to IntensityDataItem
    void onYaxisRangeChanged(QCPRange newRange);

    //! Replots SpecularPlot.
    void onTimeToReplot();

protected:
    void subscribeToItem() override;
    void unsubscribeFromItem() override;

private:
    //! creates and initializes the color map
    void initPlots();

    void setConnected(bool isConnected);

    //! Connects/disconnects signals related to SpecularPlot's X,Y axes rectangle change.
    void setAxesRangeConnected(bool isConnected);

    void setUpdateTimerConnected(bool isConnected);

    //! Refresh axes' labels, range and graph data.
    void refreshPlotData();

    //! Sets (xmin,xmax) and (ymin,ymax) of SpecularPlot from specular item.
    //! Also sets logarithmic scale on y-axis if necessary.
    void setAxesRangeFromItem(DataItem1DView* item);

    //! Sets X,Y axes labels from item
    void setAxesLabelsFromItem(DataItem1DView* item);

    //! Sets label to axis
    void setLabel(const BasicAxisItem* item, QCPAxis* axis, QString label);

    //! Sets data item values to graphs.
    void setDataFromItem(DataItem1DView* item);

    DataItem1DView* viewItem();
    const DataItem1DView* viewItem() const;

    void modifyAxesProperties(const QString& axisName, const QString& propertyName);

    //! Schedule replot for later execution by onTimeReplot() slot.
    void replot();

    QCustomPlot* m_custom_plot;
    UpdateTimer* m_update_timer;
    std::map<Data1DProperties*, QCPGraph*> m_graph_map;

    bool m_block_update;
};

#endif // SPECULARPLOTWITHDATAVIEW_H