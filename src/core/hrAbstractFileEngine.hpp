#pragma once

#include <QIODevice>
#include "hrAbstractFileEngineIterator.hpp"

class hrAbstractFileEngine
{
public:
    enum FileFlag
    {
        ExeOtherPerm = 0x0001,
        WriteOtherPerm = 0x0002,
        ReadOtherPerm = 0x0004,

        ExeGroupPerm = 0x0010,
        WriteGroupPerm = 0x0020,
        ReadGroupPerm = 0x0040,

        ExeUserPerm = 0x0100,
        WriteUserPerm = 0x0200,
        ReadUserPerm = 0x0400,

        ReadOwnerPerm = 0x4000,
        WriteOwnerPerm = 0x2000,
        ExeOwnerPerm = 0x1000,

        LinkType = 0x10000,
        FileType = 0x20000,
        DirectoryType = 0x40000,
        BundleType = 0x80000,


        HiddenFlag = 0x0100000,
        LocalDiskFlag = 0x0200000,
        ExistsFlag = 0x0400000,
        RootFlag = 0x0800000,
        Refresh = 0x1000000,

        PermsMask  = 0x0000FFFF,
        TypesMask  = 0x000F0000,
        FlagsMask  = 0x0FF00000,
        FileInfoAll = FlagsMask | PermsMask | TypesMask
    };

    enum Extension
    {
        AtEndExtension = 0,
        FastReadLineExtension = 1,
        MapExtension = 2,
        UnMapExtension = 3
    };

    enum FileName
    {
        DefaultName = 0,
        BaseName = 1,
        PathName = 2,
        AbsoluteName = 3,
        AbsolutePathName = 4,
        LinkName = 5,
        CanonicalName = 6,
        CanonicalPathName = 7,
        BundleName = 8
    };

    typedef hrAbstractFileEngineIterator Iterator;
    typedef QFlags<FileFlag> FileFlags;

    hrAbstractFileEngine();
    virtual ~hrAbstractFileEngine();

    virtual bool open(QIODevice::OpenMode flags) = 0;
    virtual void setFileName(const QString &file) = 0;
    virtual bool close() = 0;
    virtual qint64 size() const = 0;
    virtual qint64 pos() const = 0;
    virtual bool atEnd() const = 0;
    virtual bool seek(qint64) = 0;
    virtual qint64 read(char *data, qint64 maxlen) = 0;

    virtual QStringList entryList(QDir::Filters filters, const QStringList &filterNames) const
    {
        QStringList ret;
        QDirIterator it(fileName(), filterNames, filters);

        while(it.hasNext())
        {
            it.next();
            ret << it.fileName();
        }

        return ret;
    }

    virtual FileFlags fileFlags(FileFlags type) const = 0;

    virtual QString fileName(FileName file = DefaultName) const = 0;

    virtual Iterator* beginEntryList(QDir::Filters filters, const QStringList &filterNames) = 0;

    virtual bool supportsExtension(Extension) const = 0;

};
