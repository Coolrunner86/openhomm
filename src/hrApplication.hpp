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
#pragma once

class hrLodEngineHandler;
class hrSndEngineHandler;
class hrVfsEngineHandler;

class hrApplication : public QApplication
{
    Q_OBJECT
public:
    hrApplication(int &argc, char **argv);
    ~hrApplication();
    static QString getMapName()
    {
        return mapName;
    }
private:
    void createFileEngineHandlers();
    void destroyFileEngineHandlers();
    void loadSettings();
    static void hrLogger (QtMsgType type, const QMessageLogContext &context, const QString &msg);

// data
private:
    hrLodEngineHandler *lodHandler;
    hrSndEngineHandler *sndHandler;
    hrVfsEngineHandler *vfsHandler;

    static QString mapName;
};
