#include "hrLodFile.hpp"

hrLodFile::hrLodFile(const QString &path) :
    hrResourceFile(path),
    _file(path)
{
    if(!_file.open(QIODevice::ReadOnly))
    {
        qCritical("Can't open %s", qPrintable(path));
        return;
    }

    LodHeader head;
    _file.read((char *)&head, sizeof(head));

    if ( head.magic != LOD_MAGIC )
    {
        qCritical("%s is not LOD archive", qPrintable(path));
        return;
    }

    _file.seek(0x5C);//TODO replace magic number

    for ( quint32 i = 0; i < head.files; ++i )
    {
        LodEntry entry;

        _file.read((char *)&entry, sizeof(entry));
        _entryMap.insert(QString(entry.name).toLower(), entry);
    }
}

hrLodFile::~hrLodFile()
{
    _file.close();
}

QStringList hrLodFile::entryList()
{
    return _entryMap.keys();
}

QByteArray hrLodFile::getEntry(const QString &entryName)
{
    QByteArray result;

    QString lowerName = entryName.toLower();

    if ( !_entryMap.contains(lowerName) )
        return result;

    LodEntry entry = _entryMap.value(lowerName);

    _file.seek(entry.offset);

    if ( entry.csize == 0 )
        result = _file.read(entry.size);
    else
    {
        QByteArray ba = _file.read(entry.csize);

        char *l = (char*)&entry.size;

        ba.prepend(l[0]);
        ba.prepend(l[1]);
        ba.prepend(l[2]);
        ba.prepend(l[3]);

        result = qUncompress(ba);
    }

    return result;
}

