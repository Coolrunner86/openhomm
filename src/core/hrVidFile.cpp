#include "hrVidFile.hpp"

hrVidFile::hrVidFile(const QString& path) :
    hrResourceFile(path),
    _file(path)
{
    if(!_file.open(QIODevice::ReadOnly))
    {
        qCritical("Can't open %s", qPrintable(path));
        return;
    }

    quint32 count = 0;

    if ( _file.read( (char *) &count, 4 ) == 4 )
    {
        VidEntryExt extEntries[count];

        for ( quint32 i = 0; i < count; ++i )
        {
            memset(&extEntries[i], 0, sizeof(VidEntryExt) );

            _file.read( (char *) &extEntries[i].entry, sizeof(VidEntry));

            for ( int j = 0; j < VidEntry::NAME_SIZE; ++j )
            {
                if ( extEntries[i].entry.name[j] == '\0' )
                {
                    extEntries[i].entry.name[j] = '.';
                    break;
                }
            }
        }

        extEntries[count - 1].size = _file.size() - extEntries[count - 1].entry.offset;

        for (quint32 i = 1; i < count; i++)
        {
            extEntries[i - 1].size = extEntries[i].entry.offset - extEntries[i - 1].entry.offset;
            _entryMap.insert(QString(extEntry.entry.name).toLower(), extEntries[i]);
        }
    }
}

hrVidFile::~hrVidFile()
{
    _file.close();
}

QByteArray hrVidFile::getEntry(const QString& entryName)
{
    QByteArray result;

    QString lowerName = entryName.toLower();

    if ( !_entryMap.contains(lowerName) )
        return result;

    VidEntryExt extEntry = _entryMap.value(lowerName);

    if ( _file.seek(extEntry.entry.offset) )
        result = _file.read(entry.size);

    return result;
}

QStringList hrVidFile::entryList()
{
    return _entryMap.keys();
}
