#pragma once

#include "hrResourceFile.hpp"

struct SndEntry
{
    char    name[40];
    quint32 offset;
    quint32 size;
};

typedef QHash<QString, SndEntry> EntryMap;

class hrSndFile : public hrResourceFile
{
public:
    hrSndFile(const QString& path);
    ~hrSndFile();

    QByteArray getEntry(const QString& entryName);
    QStringList entryList();

private:
    QFile _file;
    EntryMap _entryMap;
};
