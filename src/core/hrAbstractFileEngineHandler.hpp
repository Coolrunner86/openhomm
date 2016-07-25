#pragma once

class hrAbstractFileEngineHandler
{
public:
    hrAbstractFileEngineHandler();
    virtual ~hrAbstractFileEngineHandler();

    virtual hrAbstractFileEngine* create(const QString & fileName) const = 0;
};

