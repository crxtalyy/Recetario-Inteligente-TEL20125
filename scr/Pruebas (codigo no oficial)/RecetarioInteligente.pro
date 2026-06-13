QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agregarrecetadialog.cpp \
    detallerecetadialog.cpp \
    ingredientesdialog.cpp \
    instruccionesdialog.cpp \
    listarecetasdialog.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    Ingredientes.cpp \
    receta.cpp

HEADERS += \
    agregarrecetadialog.h \
    detallerecetadialog.h \
    ingredientesdialog.h \
    instruccionesdialog.h \
    listarecetasdialog.h \
    logindialog.h \
    mainwindow.h \
    Ingredientes.h \
    receta.h

FORMS += \
    agregarrecetadialog.ui \
    detallerecetadialog.ui \
    ingredientesdialog.ui \
    instruccionesdialog.ui \
    listarecetasdialog.ui \
    logindialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
