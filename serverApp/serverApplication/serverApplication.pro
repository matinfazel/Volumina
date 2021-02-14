QT -= gui
QT += core
QT += sql
QT += network

CONFIG += c++11 console
CONFIG -= app_bundle

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
        basecontroller.cpp \
        book.cpp \
        bookitem.cpp \
        clienttask.cpp \
        httpserver.cpp \
        lend.cpp \
        librarian.cpp \
        main.cpp \
        member.cpp \
        repository.cpp \
        taskconfirm.cpp \
        authservice.cpp \
        convertorservice.cpp \
        transactionitem.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    basecontroller.h \
    book.h \
    bookitem.h \
    clienttask.h \
    httpserver.h \
    lend.h \
    librarian.h \
    member.h \
    taskconfirm.h \
    authservice.h \
    convertorservice.h \
    repository.h \
    transactionitem.h
