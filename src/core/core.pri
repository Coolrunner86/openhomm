INCLUDEPATH += $$PWD
VPATH += $$PWD

HEADERS += hrString.hpp \
    hrLodEngine.hpp \
    hrLodEngineIterator.hpp \
    hrSndEngineIterator.hpp \
    hrSndEngine.hpp \
    hrSettings.hpp \
    hrFilesystem.hpp \
    hrFileEngineHandlers.hpp \
    hrAbstractFileEngineIterator.hpp \
    hrAbstractFileEngine.hpp \
    hrAbstractFileEngineHandler.hpp \
    hrFileEngine.hpp \
    $$PWD/hrResourceFile.hpp \
    $$PWD/hrLodFile.hpp \
    $$PWD/hrSndFile.hpp
SOURCES += hrString.cpp \
    hrLodEngine.cpp \
    hrLodEngineIterator.cpp \
    hrSndEngineIterator.cpp \
    hrSndEngine.cpp \
    hrSettings.cpp \
    hrFilesystem.cpp \
    hrFileEngineHandlers.cpp \
    $$PWD/hrLodFile.cpp \
    $$PWD/hrSndFile.cpp
