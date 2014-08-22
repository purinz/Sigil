/************************************************************************
 **
 **  Copyright (C) 2014
 **
 **  This file is part of Sigil.
 **
 **  Sigil is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Sigil is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#ifndef PLUGINRUNNER_H
#define PLUGINRUNNER_H

#include <QString>
#include <QStringList>
#include <QDialog>
#include <QProgressBar>
#include <QProcess>
#include "Misc/TempFolder.h"

#include "ResourceObjects/CSSResource.h"
#include "ResourceObjects/FontResource.h"
#include "ResourceObjects/HTMLResource.h"
#include "ResourceObjects/ImageResource.h"
#include "ResourceObjects/MiscTextResource.h"
#include "ResourceObjects/SVGResource.h"
#include "ResourceObjects/OPFResource.h"
#include "ResourceObjects/NCXResource.h"
#include "ResourceObjects/VideoResource.h"
#include "ResourceObjects/AudioResource.h"
#include "ResourceObjects/VideoResource.h"
#include "ResourceObjects/XMLResource.h"

#include "ui_PluginRunner.h"

class MainWindow;
class Book;
class BookBrowser;
class FolderKeeper;
class Resource;
class OPFResource;
class NCXResource;
class TempFolder;

class PluginRunner : public QDialog

{
    Q_OBJECT

public:

    enum PluginFields {
        NameField        = 0,
        AuthorField      = 1,
        DescriptionField = 2,
        TypeField        = 3,
        EngineField      = 4
    };

    enum FileInfoFields {
        hrefField = 0,
        idField   = 1,
        mimeField = 2
    };

    PluginRunner(QString name, QWidget * parent);
    ~PluginRunner();

public slots:

private slots:
    void startPlugin();
    void cancelPlugin();
    void processError(QProcess::ProcessError error);
    void processOutput();
    void pluginFinished(int exitcode, QProcess::ExitStatus exitstatus );

private:

    bool processResultXML();

    bool deleteFiles(const QStringList &);
    bool addFiles(const QStringList &);
    bool modifyFiles(const QStringList &);

    void connectSignalsToSlots();

    QProcess m_process;

    MainWindow * m_mainWindow;
    QSharedPointer<Book> m_book;
    BookBrowser * m_bookBrowser;

    TempFolder m_folder;
    QString m_outputDir;

    QString m_launcherPath;
    QString m_enginePath;
    QString m_engine;
    QString m_pluginName;
    QString m_pluginPath;
    QString m_pluginsFolder;
    QString m_bookRoot;
    QString m_pluginType;
    QByteArray m_pluginOutput;
    QString m_algorithm;

    QStringList m_filesToDelete;
    QStringList m_filesToAdd;
    QStringList m_filesToModify;
    QString m_result;

    QHash < QString, Resource * > m_hrefToRes; 

    bool m_ready;

    static const QString SEP;
    static const QString OPFFILEINFO;
    static const QString NCXFILEINFO;
    static const QStringList CHANGESTAGS;

    Ui::PluginRunner ui;

};

#endif