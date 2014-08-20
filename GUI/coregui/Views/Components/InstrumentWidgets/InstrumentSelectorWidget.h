#ifndef INSTRUMENT_SELECTOR_WIDGET_H
#define INSTRUMENT_SELECTOR_WIDGET_H


#include <QWidget>
class InstrumentModel;
class QListView;
class QAction;
class QItemSelectionModel;
class QItemSelection;

class InstrumentSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentSelectorWidget(InstrumentModel *model, QWidget *parent = 0);

    QSize sizeHint() const { return QSize(200, 600); }
    QSize minimumSizeHint() const { return QSize(128, 300); }

    void setInstrumentModel(InstrumentModel *model);

    QItemSelectionModel *getSelectionModel();
    QListView *getListView() { return m_listView; }

signals:
    void selectionChanged(const QItemSelection&, const QItemSelection&);

public slots:
    void updateSelection();
//    void onRowsInserted(const QModelIndex &parent, int first, int last);

private:
    InstrumentModel *m_instrumentModel;
    QListView *m_listView;
};


#endif

