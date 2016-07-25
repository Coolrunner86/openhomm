#pragma once

class hrAbstractFileEngineIterator
{
public:
    hrAbstractFileEngineIterator(QDir::Filters filters, const QStringList & nameFilters) {}
    virtual	~hrAbstractFileEngineIterator();

    virtual QString	currentFileName() const = 0;
    virtual bool hasNext() const = 0;
    virtual QString	next() = 0;

//    virtual QFileInfo currentFileInfo() const;
//    QString currentFilePath() const;
//    QDir::Filters	filters() const;
//    QStringList nameFilters() const;
//    QString path() const;
};

