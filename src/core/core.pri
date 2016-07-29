INCLUDEPATH += $$PWD
VPATH += $$PWD

HEADERS += hrString.hpp \
    hrSettings.hpp \
    hrFilesystem.hpp \
    hrResourceFile.hpp \
    hrLodFile.hpp \
    hrSndFile.hpp \
    $$PWD/hrVidFile.hpp

SOURCES += hrString.cpp \
    hrSettings.cpp \
    hrFilesystem.cpp \
    hrLodFile.cpp \
    hrSndFile.cpp \
    $$PWD/hrVidFile.cpp
