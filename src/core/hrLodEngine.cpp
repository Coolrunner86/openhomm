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
#include "hrLodEngineIterator.hpp"
#include "hrLodEngine.hpp"
#include "hrFilesystem.hpp"

LodFiles hrLodEngine::_cache;

/*!
  \class hrLodEngine
  \brief The hrLodEngine class
*/

hrLodEngine::hrLodEngine(const QString& path) : hrAbstractFileEngine(), _lf(NULL), _buffer(NULL)
{
    this->setFileName(path);
}

hrLodEngine::~hrLodEngine()
{
    this->close();
}

void hrLodEngine::setFileName(const QString &file)
{
    _archivename = hrFilesystem::extractArchnameFromPath(file, ".lod");
    _filename    = hrFilesystem::extractFilenameFromPath(file, ".lod");

    _filename = _filename.toLower();
}

bool hrLodEngine::open(QIODevice::OpenMode flags)
{
    if ( flags & QIODevice::WriteOnly )
        qWarning("Write mode not supported. Ignored");


    if ( _cache.find(_archivename) == _cache.end() )
    {
        qWarning("File %s not found in cache", qPrintable(_archivename));
        return false;
    }
    _lf = _cache[_archivename];

    bool res = false;

    if ( !_filename.isEmpty() )
        res = preloadFile();

    return res;
}
bool hrLodEngine::close()
{
    if ( _buffer != NULL )
    {
        if ( _buffer->isOpen() )
            _buffer->close();

        delete _buffer;
        _buffer = NULL;
    }
    return true;
}

qint64 hrLodEngine::size() const
{
    if ( _buffer != NULL )
        return _buffer->size();

    return 0;
}
qint64 hrLodEngine::pos() const
{
    if ( _buffer != NULL )
        return _buffer->pos();

    return 0;
}
bool hrLodEngine::atEnd() const
{
    if ( _buffer != NULL )
        return _buffer->atEnd();

    return true;
}
bool hrLodEngine::seek(qint64 offset)
{
    if ( _buffer != NULL )
        return _buffer->seek(offset);

    return false;
}
qint64 hrLodEngine::read(char *data, qint64 maxlen)
{
    if ( _buffer != NULL )
        return _buffer->read(data, maxlen);

    return 0;
}

QStringList hrLodEngine::entryList(QDir::Filters filters, const QStringList &filterNames) const
{
    if ( _lf != NULL )
        return _lf->fat.keys();

    return hrAbstractFileEngine::entryList(filters, filterNames);
}

hrAbstractFileEngine::FileFlags hrLodEngine::fileFlags(FileFlags type) const
{
    hrAbstractFileEngine::FileFlags ret = 0;

    if(type & TypesMask)
        ret |= FileType;

    if(type & FlagsMask)
        ret |= ExistsFlag;

    return ret;
}

QString hrLodEngine::fileName(FileName) const
{
    return _filename;
}

hrAbstractFileEngine::Iterator* hrLodEngine::beginEntryList(QDir::Filters filters, const QStringList &filterNames)
{
    return new hrLodEngineIterator(filters, filterNames);
}

bool hrLodEngine::supportsExtension(Extension ext) const
{
    return ext == AtEndExtension;
}

bool hrLodEngine::preloadFile()
{
    if ( _buffer == NULL )
        _buffer = new QBuffer;

    LodEntry entry = _lf->fat.value(_filename);
    _lf->file->seek(entry.offset);

    if ( entry.csize == 0 )
    {
        QByteArray ba = _lf->file->read(entry.size);
        _buffer->setData(ba);
        _buffer->open(QIODevice::ReadOnly);

        return true;
    }
    else
    {
        QByteArray ba = _lf->file->read(entry.csize);

        char *l = (char*)&entry.size;

        ba.prepend(l[0]);
        ba.prepend(l[1]);
        ba.prepend(l[2]);
        ba.prepend(l[3]);

        QByteArray unc = qUncompress(ba);

        _buffer->setData(unc);
        _buffer->open(QIODevice::ReadOnly);

        return true;
    }

    return false;
}

bool hrLodEngine::fillInternalCache(const QString &filename)
{
    LodFile* lf = new LodFile;

    lf->file = new QFile(filename);

    if ( lf->file->open(QIODevice::ReadOnly) )
    {
        LodHeader head;
        lf->file->read((char *)&head, sizeof(head));
        if ( head.magic != LOD_MAGIC )
        {
            qCritical("%s is not LOD archive", qPrintable(filename));
            return false;
        }

        lf->file->seek(0x5C);

        for ( quint32 i = 0; i < head.files; ++i )
        {
            LodEntry entry;
            lf->file->read((char *)&entry, sizeof(entry));
            lf->fat.insert(QString(entry.name).toLower(), entry);
            hrFilesystem::fillGeneralCache(QString(entry.name), filename);
        }
        _cache.insert(filename, lf);
        return true;
    }
    else
    {
        qCritical("Can't open %s", qPrintable(filename));
        delete lf;
    }
    return false;
}






























hrLodEngineNew::hrLodEngineNew(const QString& path) : hrFileEngine(), _lf(NULL), _buffer(NULL)
{
    addPath(path);
}

hrLodEngineNew::~hrLodEngineNew()
{

}

bool hrLodEngineNew::addPath(const QString& path)
{
    QFileInfo info(path);

    if(!info.isDir())
    {
        //TODO log
        return false;
    }

    QStringList filesList = QDir(path).entryList(".lod", QDir::Files);

    for(const auto& file : filesList)
        addFile(file);

    return true;
}

QByteArray hrLodEngineNew::readEntry(const QString& name)
{
    QByteArray result;

    if ( !_entryMap.contains(name) )
    {
        //TODO log
        return result;
    }

    QSharedPtr<LodFile> lf = _entryMap.value(name);
    LodEntry entry = lf->fat.value(name);

    lf->file.seek(entry.offset);

    if ( entry.csize == 0 )
        result = _lf->file.read(entry.size);
    else
    {
        QByteArray ba = lf->file.read(entry.csize);

        char *l = (char*)&entry.size;

        ba.prepend(l[0]);
        ba.prepend(l[1]);
        ba.prepend(l[2]);
        ba.prepend(l[3]);

        result = qUncompress(ba);
    }

    return result;
}

void hrLodEngineNew::addFile(const QString& path)
{
    QSharedPointer<LodFile> lf = new LodFile;
    lf->file.setFileName(path);

    if ( !lf->file.open(QIODevice::ReadOnly) )
    {
        qCritical("Can't open %s", qPrintable(path));
        return;
    }

    LodHeader head;
    lf->file.read((char *)&head, sizeof(head));

    if ( head.magic != LOD_MAGIC )
    {
        qCritical("%s is not LOD archive", qPrintable(path));
        return;
    }

    lf->fileseek(0x5C);//TODO replace magic number

    for ( quint32 i = 0; i < head.files; ++i )
    {
        LodEntry entry;

        lf->file.read((char *)&entry, sizeof(entry));
        lf->fat.insert(QString(entry.name).toLower(), entry);

        _entryMap.insert(QString(entry.name).toLower(), lf);
    }
}
