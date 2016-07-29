// openhomm - open source clone of Heroes of Might and Magic III
// Copyright (C) 2009-2010 openhomm developers team (see AUTHORS)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "precompiled.hpp"

#include <fstream>

#include "hrApplication.hpp"
#include "hrPushButton.hpp"
#include "hrSettings.hpp"

#include "hrCache.hpp"
#include "hrLodFile.hpp"
#include "hrSndFile.hpp"

/*!
  \class hrApplication
*/

/*!
  Constructs application and loads application settings.
  \sa hrSettings
*/
hrApplication::hrApplication(int &argc, char **argv):
        QApplication(argc, argv)
{
    QString logType = hrSettings::get().logType();

    qInstallMessageHandler(&hrApplication::hrLogger);
    qSetMessagePattern("[%{time process}] [%{type}]%{if-category} [%{category}]%{endif} %{message}");

    _filesystem.registerExtension("lod", [](const QString& path) -> hrResourceFile* { return new hrLodFile(path); });
    _filesystem.registerExtension("snd", [](const QString& path) -> hrResourceFile* { return new hrSndFile(path); });
    _filesystem.mount(QStringList() << "data/h3sprite.lod" << "data/h3bitmap.lod" << "data/heroes3.snd" );

    hrCache::getInstance().setFilesystem(&_filesystem);
}

/*!
  Destroys the hrApplication object.
  \sa hrSettings
  */
hrApplication::~hrApplication()
{
}

void hrApplication::hrLogger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString logMessage = qFormatLogMessage(type, context, msg);
    static QMutex mutex;
    QMutexLocker lock(&mutex);
    static std::ofstream logFile("logfile.txt");

    if (logFile)
    {
        logFile << qPrintable(logMessage) << std::endl;
    }

    fprintf(stderr, "%s\n", logMessage.toLocal8Bit().constData());
    fflush(stderr);
}
