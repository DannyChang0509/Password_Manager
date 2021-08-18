QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    click_combobox.cpp \
    dialog_anp.cpp \
    dialog_cv.cpp \
    dialog_dop.cpp \
    dialog_du.cpp \
    dialog_eop.cpp \
    dialog_eui.cpp \
    dialog_su.cpp \
    fileio.cpp \
    item.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Encryptor_and_Decryptor.h \
    click_combobox.h \
    dialog_anp.h \
    dialog_cv.h \
    dialog_dop.h \
    dialog_du.h \
    dialog_eop.h \
    dialog_eui.h \
    dialog_su.h \
    fileio.h \
    item.h \
    mainwindow.h

FORMS += \
    dialog_anp.ui \
    dialog_cv.ui \
    dialog_dop.ui \
    dialog_du.ui \
    dialog_eop.ui \
    dialog_eui.ui \
    dialog_su.ui \
    mainwindow.ui

RC_FILE = icon.rc

TRANSLATIONS += \
    translation_chinese.ts \
    translation_english.ts \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    translation_chinese.ts \
    translation_english.ts
