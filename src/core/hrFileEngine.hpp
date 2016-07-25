#pragma once

class hrFileEngine
{
public:
    hrFileEngine() {}
    virtual ~hrFileEngine();

    virtual bool addPath(const QString &path) = 0;
    virtual QByteArray readEntry(const QString& name) = 0;
};
