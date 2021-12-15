QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    forms/authors/authors.cpp \
    forms/help/help.cpp \
    forms/schedule/schedule.cpp \
    forms/settings/settings.cpp \
    genetic_algorithm/manager.cpp \
    genetic_algorithm/params.cpp \
    genetic_algorithm/population.cpp \
    graph/edge.cpp \
    graph/graph.cpp \
    graph/node.cpp \
    graphic/qcustomplot.cpp \
    main.cpp \
    startwindow.cpp

HEADERS += \
    forms/authors/authors.h \
    forms/help/help.h \
    forms/schedule/schedule.h \
    forms/settings/settings.h \
    genetic_algorithm/manager.h \
    genetic_algorithm/params.h \
    genetic_algorithm/population.h \
    graph/edge.h \
    graph/graph.h \
    graph/node.h \
    graphic/qcustomplot.h \
    startwindow.h

FORMS += \
    forms/authors/authors.ui \
    forms/help/help.ui \
    forms/schedule/schedule.ui \
    forms/settings/settings.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/res.qrc

win32: RC_ICONS = resource/icon.ico
