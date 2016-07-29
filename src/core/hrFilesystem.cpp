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
#include "hrFilesystem.hpp"
#include "hrSettings.hpp"

const char* MOUNT_SUCCESSFULLY = "\tSuccessfully mounted!";
const char* MOUNT_FAILED       = "\tFailed to mount!";

Q_LOGGING_CATEGORY(fsCat, "fs.main");

/**
*  Find a case-correct path.
 *  @param path a case-insensitive path
 *  @param baseDir a existing base directory. Certainly does not require case correction.
 *  @return Right path or null string on error.
 */
QString hrFilesystem::adjustCaseInPath(const QString &path, const QDir &baseDir)
{
    QStringList pathElements = path.split('/');
    QDir current = baseDir;

    for ( int j = 0; j < pathElements.size()-1; j++ )
    {
        QString next = pathElements[j];

        if (!current.exists(next))
        {
            QStringList candidates = current.entryList(QStringList() << next, QDir::Dirs | QDir::Readable ); // flag QDir::CaseSensitive does not set by default and this is that we need

            if (candidates.size() == 0)
            {
                qCCritical(fsCat) << QString("Directory `%1` not found in directory `%2`").arg(next).arg(current.path());
                return QString();
            }

            if (candidates.size() != 1)
                qCWarning(fsCat) << QString("Ambiguous element `%1` in directory `%2`, selecting `%3`").arg(next).arg(current.path()).arg(candidates.first());

            next = candidates.first();
        }

        if (!current.cd(next))
        {
            qCCritical(fsCat) << QString("Cannot enter directory `%1` in directory `%2`").arg(next).arg(current.path());
            return QString();
        }
    }

    QString last = pathElements.last();

    if (!current.exists(last))
    {
        QStringList candidates = current.entryList(QStringList() << last, QDir::Dirs | QDir::Files | QDir::Readable ); // flag QDir::CaseSensitive does not set by default and this is that we need

        if (candidates.size() == 0)
        {
            qCCritical(fsCat) << QString("File or directory `%1` not found in directory `%2`").arg(last).arg(current.path());
            return QString();
        }

        if (candidates.size() != 1)
            qCWarning(fsCat) << QString("Ambiguous element `%1` in directory `%2`, selecting `%3`").arg(last).arg(current.path()).arg(candidates.first());

        last = candidates.first();
    }

    return current.filePath(last);
}

bool hrFilesystem::mount(const QString &path)
{
    QDir gameRoot = hrSettings::get().gameDir();

    Q_ASSERT(gameRoot.exists());

    QString normalPath = adjustCaseInPath(path, gameRoot);

    if (normalPath.isNull() || !QFile::exists(normalPath))
        return false;

    qCInfo(fsCat) << QString("Trying to mount: %1").arg(normalPath);

    if ( QFileInfo(normalPath).isDir() )
    {
        if ( !mountDir(normalPath))
        {
            qCCritical(fsCat) << "\tFailed to mount dir " << normalPath;
            return false;
        }

        qCInfo(fsCat) << "\tDirectory " << normalPath << MOUNT_SUCCESSFULLY;
    }
    else
        mountFile(normalPath);

    return true;
}
/*!
  \overload
*/

void hrFilesystem::mount(const QStringList &path_list)
{
    for ( int i = 0; i < path_list.size(); i++)
        mount(path_list[i]);
}

/*!
  not implemented yet
*/
bool hrFilesystem::umount(const QString &path)
{
    Q_UNUSED(path);
    return false;
}

void hrFilesystem::registerExtension(const QString& extension, const std::function<hrResourceFile*(const QString&)>& factory)
{
    _extensions.insert(extension, factory);
}

QByteArray hrFilesystem::findResource(const QString& name)
{
    QByteArray result;

    for(const auto& file : _files)
    {
        result = file->getEntry(name);

        if(result.size() > 0)
            break;
    }

    return result;
}

void hrFilesystem::walkDirectory(const QString &path, QStringList &fileList)
{
    QDir mounted(path);
    QFileInfoList entries = mounted.entryInfoList();

    for ( int i = 0; i < entries.size(); i++)
    {
        if ( entries[i].fileName() == "." || entries[i].fileName() == "..")
            continue;

        if ( entries[i].isDir() )
        {
            walkDirectory(entries[i].absoluteFilePath(), fileList);
            continue;
        }

        fileList.append(entries[i].absoluteFilePath());
    }
}

bool hrFilesystem::mountDir(const QString &path)
{
    QStringList fileList;
    walkDirectory(path, fileList);

    for(auto& file : fileList)
    {
        file.remove(path);
        file.remove(0, 1); // remove first '/'

        if(!mountFile(file))
            return false;
    }

    return true;
}

bool hrFilesystem::mountFile(const QString& path)
{
    QString extension = path.right(path.length() - (path.lastIndexOf('.') + 1));

    if ( !_extensions.contains(extension) )
    {
        qCCritical(fsCat) << "\tUnsupported archive type";
        return false;
    }

    auto& creator = _extensions.value(extension);
    _files.append(QSharedPointer<hrResourceFile>(creator(path)));//TODO errors support

    qCInfo(fsCat) << MOUNT_SUCCESSFULLY;

    return true;
}

///**
// *  Extract archive name from full path.
// *  @param path a case-sensitive path
// *  @param ext Must be ".lod" or ".snd" or something else
// *  @return Archive name or null string on error.
// */
//QString hrFilesystem::extractArchnameFromPath(const QString& path, const char* ext)
//{
//    QString archive;
//    int index = path.indexOf(ext);

//    if ( index == -1 )
//        return QString();

//    archive = path.left(index + qstrlen(ext));
//    archive.remove(0, qstrlen(ext) + 1);

//    return archive;
//}

///**
// *  Extract filename with path from full path.
// *  @param path a case-sensitive path
// *  @param ext Must be ".lod" or ".snd" or something else
// *  @return Archive name or null string on error.
// */
//QString hrFilesystem::extractFilenameFromPath(const QString& path, const char* ext)
//{
//    int index = path.indexOf(ext);

//    if ( index == -1 )
//        return QString();

//    return path.right(path.length() - index - qstrlen(ext) - 1 );
//}
