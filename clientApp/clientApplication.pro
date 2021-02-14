QT  += core gui
QT  += network


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
    addpenaltydialog.cpp \
    addtransaction.cpp \
    connectdialog.cpp \
    editaccountdialog.cpp \
    helpdialog.cpp \
    helplibdialog.cpp \
    lendbook.cpp \
    lenddialog.cpp \
    librarianwindow.cpp \
    libsearchview.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    memberviewdialog.cpp \
    renewbookdialog.cpp \
    renewmemberdialog.cpp \
    searchlenddialog.cpp \
    searchview.cpp \
    serverconnection.cpp

HEADERS += \
    addpenaltydialog.h \
    addtransaction.h \
    connectdialog.h \
    editaccountdialog.h \
    helpdialog.h \
    helplibdialog.h \
    lendbook.h \
    lenddialog.h \
    librarianwindow.h \
    libsearchview.h \
    logindialog.h \
    mainwindow.h \
    memberviewdialog.h \
    renewbookdialog.h \
    renewmemberdialog.h \
    searchlenddialog.h \
    searchview.h \
    serverconnection.h

FORMS += \
    addpenaltydialog.ui \
    addtransaction.ui \
    connectdialog.ui \
    editaccountdialog.ui \
    helpdialog.ui \
    helplibdialog.ui \
    lendbook.ui \
    lenddialog.ui \
    librarianwindow.ui \
    libsearchview.ui \
    logindialog.ui \
    mainwindow.ui \
    memberviewdialog.ui \
    renewbookdialog.ui \
    renewmemberdialog.ui \
    searchlenddialog.ui \
    searchview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/0b85636ca6384399edbae4cc3d344937.png \
    src/683b5ecbaf5bb893ed1b10cffd392106.jpg \
    src/8f67e404cad80b0862148f6482cc6970.jpg \
    src/954fc3e5f4a257ea4cc5fe59fa054437.jpg \
    src/add (1).png \
    src/add-admin.png \
    src/add-book.png \
    src/add-user.png \
    src/add.png \
    src/book.png \
    src/borrow-icon-5.jpg \
    src/browser.png \
    src/cancel.png \
    src/credit-card-payment.png \
    src/credit-card.png \
    src/edit.png \
    src/ee02ae9a2c8c9fcafe4e7e61586d986f.png \
    src/eraser.png \
    src/exit.png \
    src/f2f58574bab69904590471d4c18a8bc0.jpg \
    src/iconfinder_help_326654.png \
    src/iconfinder_search_322497.png \
    src/information.png \
    src/login.png \
    src/plus.png \
    src/refresh-button.png \
    src/replace.png \
    src/return.png \
    src/search.png \
    src/world-wide-web.png

RESOURCES += \
    img.qrc
