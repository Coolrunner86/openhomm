#pragma once

#include "hrResourceFile.hpp"

struct VidEntry
{
    static const quint32 NAME_SIZE = 40;

    char      name[NAME_SIZE];
    quint32   offset;
};

struct VidEntryExt
{
    VidEntry entry;
    quint32 size;
};

class hrVidFile : public hrResourceFile
{

public:    
    typedef QHash<QString, VidEntryExt> EntryMap;

    hrVidFile(const QString& path);
    ~hrVidFile();

    QByteArray getEntry(const QString& entryName);
    QStringList entryList();

private:
    QFile               _file;
    EntryMap            _entryMap;
};
