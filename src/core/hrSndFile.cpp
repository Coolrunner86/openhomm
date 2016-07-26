#include "hrSndFile.hpp"

hrSndFile::hrSndFile(const QString &path) :
    hrResourceFile(path),
    _file(path)
{    
    if ( !_file.open(QIODevice::ReadOnly ) )
    {
        qCritical("Can't open %s", qPrintable(filename));
        return;
    }

    quint32 count = 0;

    if ( _file.read( (char *) &count, 4 ) == 4 )
    {
        for ( quint32 i = 0; i < count; ++i )
        {
            SndEntry entry;
            memset(&entry, 0, sizeof(entry) );

            _file.read( (char *) &entry, sizeof(SndEntry));

            for ( int i = 0; i < 40; ++i )
            {
                if ( entry.name[i] == '\0' )
                {
                    entry.name[i] = '.';
                    break;
                }
            }

            _entryMap.insert(QString(entry.name).toLower(), entry);
        }
    }
}

hrSndFile::~hrSndFile()
{
    _file.close();
}

QByteArray hrSndFile::getEntry(const QString &entryName)
{
    QByteArray result;

    if ( !_entryMap.contains(entryName) )
    {
        //TODO log
        return result;
    }

    SndEntry entry = _entryMap.value(entryName);

    if ( _file.seek(entry.offset) )
        result = _file.read(entry.size);

    return result;
}

QStringList hrSndFile::entryList()
{
    return _entryMap.keys();
}
