QT += widgets

HEADERS       = shapeitem.h \
    core.h \
    resources.h \
    dialogWindows.h \
    crisis.h \
    mainbox.h
SOURCES       = main.cpp \
                shapeitem.cpp \
    core.cpp \
    resources.cpp \
    drawRoutines.cpp \
    dialogWindows.cpp \
    menus.cpp \
    crisis.cpp \
    mainbox.cpp
RESOURCES     = \
    bopsource.qrc

# install
TARGET = BoPReviewed

FORMS +=

DISTFILES +=

RC_ICONS = icon.ico
VERSION = 0.1.2
QMAKE_TARGET_PRODUCT = "Balance of Power: Reviewed\0"
QMAKE_TARGET_DESCRIPTION = "Balance of Power: Reviewed\0"
