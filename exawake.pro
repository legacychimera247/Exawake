TARGET = exawake

CONFIG += sailfishapp

SOURCES += \
    src/exawake.cpp \
    src/wol.cpp/wol.cpp \
    src/wolmodel.cpp

DISTFILES += qml/exawake.qml \
    qml/components/ServerEditDialog.qml \
    qml/cover/CoverPage.qml \
    qml/pages/About.qml \
    qml/pages/Main.qml \
    rpm/exawake.spec \
    translations/*.ts \
    exawake.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += sailfishapp_i18n

#TRANSLATIONS += translations/exawake-de.ts

HEADERS += \
    src/wolmodel.h
