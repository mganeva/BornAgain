// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorWidget.h
//! @brief     Defines class JobSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef JOBSELECTORWIDGET_H
#define JOBSELECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class JobModel;
class JobItem;
class JobSelectorToolBar;
class JobSelectorActions;
class JobListWidget;
class JobPropertiesWidget;

namespace Manhattan
{
class MiniSplitter;
}

//! The JobSelectorWidget class represents left panel of JobView. Contains a tree to select jobs
//! on the top and job property editor at the bottom.

class BA_CORE_API_ JobSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JobSelectorWidget(JobModel* jobModel, QWidget* parent = nullptr);

    void setModel(JobModel* jobModel);

    QSize sizeHint() const { return QSize(210, 600); }
    QSize minimumSizeHint() const { return QSize(64, 300); }

    const JobItem* currentJobItem() const;

signals:
    void selectionChanged(JobItem*);

public slots:
    void makeJobItemSelected(JobItem*);

private slots:
    void onSelectionChanged(JobItem* jobItem);

private:
    Manhattan::MiniSplitter* m_splitter;
    JobSelectorActions* m_jobSelectorActions;
    JobSelectorToolBar* m_toolBar;
    JobListWidget* m_jobListWidget;
    JobPropertiesWidget* m_jobProperties;
    JobModel* m_jobModel;
};

#endif // JOBSELECTORWIDGET_H
