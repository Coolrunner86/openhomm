#pragma once

struct LodEntry
{
    char name[12];  // null-terminated, sometimes null-padded too, sometimes padded with, well, something after the null
    quint32 junk;   //
    quint32 offset; // includes the header size, no preprocessing required
    quint32 size;   // real size
    quint32 type;   // what's in the file - probably not used by the game directly, more on that below
    quint32 csize;  // compressed size
};

struct LodHeader
{
    quint32 magic;  // always 0x00444f4c, that is, a null-terminated "LOD" string
    quint32 type;   // 200 for base archives, 500 for expansion pack archives, probably completely arbitrary numbers
    quint32 files;  // quantity of files
};

const quint32 LOD_MAGIC = 0x00444f4c;
typedef QHash<QString, LodEntry> EntryMap;
//typedef QHashIterator<QString, LodEntry> LodFatIterator;

#include "hrResourceFile.hpp"

class hrLodFile : public hrResourceFile
{
public:
    hrLodFile(const QString& path);
    ~hrLodFile();

    QByteArray getEntry(const QString& entryName);
    QStringList entryList();

private:
    QFile _file;
    EntryMap _entryMap;
};

#endif // HRLODFILE_H
