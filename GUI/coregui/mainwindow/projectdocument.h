#ifndef PROJECTDOCUMENT_H
#define PROJECTDOCUMENT_H

#include <QObject>
#include <QString>

class JobQueueModel;
class QIODevice;
class QModelIndex;
class JobItem;
class SessionModel;


namespace ProjectDocumentXML
{
    const QString InfoTag("DocumentInfo");
    const QString InfoNameAttribute("ProjectName");
}


//! Project document class handles all data related to the opened project
//! (sample, jobModel, project specific windows settings)
//!
//! e.g. if project file is /home/users/development/Untitled/Untitled.pro
//! getProjectName()     - 'Untitled'
//! getProgectPath()     - '/home/users/development'
//! getProjectDir()      - 'home/users/development/Untitled
//! getProjectFileName() - '/home/users/development/Untitled/Untitled.pro'
class ProjectDocument : public QObject
{
    Q_OBJECT

public:
    ProjectDocument();
    ProjectDocument(const QString &projectfilename);
    ProjectDocument(const QString &path, const QString &name);

    bool save();
    bool load();

    QString getProjectPath() const { return m_project_path; }
    QString getProjectName() const { return m_project_name; }

    void setProjectPath(const QString &text) { m_project_path = text; }
    void setProjectName(const QString &text) { m_project_name = text; emit modified();}
    void setProjectFileName(const QString &text);

    QString getProjectFileName();
    QString getProjectDir();

    bool isModified() { return m_modified; }
    void setSessionModel(SessionModel *model);
    void setJobQueueModel(JobQueueModel *model);

    bool hasValidNameAndPath();

signals:
    void modified();

public slots:
    void onDataChanged(const QModelIndex &, const QModelIndex &);

private:
    bool writeTo(QIODevice *device);
    bool readFrom(QIODevice *device);

    void saveOutputData();
    void loadOutputData();

    QString m_project_path;
    QString m_project_name;
    SessionModel *m_sessionModel;
    JobQueueModel *m_jobQueueModel;
    bool m_modified;
};


#endif
