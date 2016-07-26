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

#include <functional>

typedef QHash<QString, QString> fileSystemCache;
typedef QHashIterator<QString, QString> fileSystemCacheIterator;


class hrFilesystem
{
public:
    bool mount(const QString &path);
    void mount(const QStringList &path_list);

    bool umount(const QString &path);

    void registerExtension(const QString& extension, const std::function<hrResourceFile*, const QString&>& factory);

    QByteArray findResource(const QString& name);




    static void fillGeneralCache(const QString& filename, const QString &archive);
    static QString findInCache(const QString& filename);


    static QString extractFilenameFromPath(const QString& path, const char* ext);
    static QString extractArchnameFromPath(const QString& path, const char* ext);

private:
    bool mountDir(const QString &path);
    void walkDirectory(const QString &path, QStringList &fileList);
    QString adjustCaseInPath(const QString &path, const QDir &baseDir);

    static fileSystemCache _cache;

    QMap<QString, std::function<hrResourceFile*, const QString&>> _extensions;
    QList<QSharedPointer<hrResourceFile>> _files;
};
