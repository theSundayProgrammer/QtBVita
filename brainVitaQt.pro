QT += widgets

SOURCES = main.cpp \
    pegwidget.cpp \
    bvboard.cpp

# install
target.path =  ./build
NSTALLS += target

HEADERS += \
    pegwidget.h \
    bvboard.h

DISTFILES += \
    README.md


