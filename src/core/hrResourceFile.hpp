#pragma once

class hrResourceFile
{
public:
    hrResourceFile(const QString& path) : _filename(path) {}
    virtual ~hrResourceFile() {}

    const QString& filename() const
    {
        return _filename;
    }

    virtual QByteArray getEntry(const QString& entryName) = 0;
    virtual QStringList entryList() = 0;

private:
    QString _filename;

};
