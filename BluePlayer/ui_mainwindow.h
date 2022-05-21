/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVideoWidget *widget;
    QToolButton *previous;
    QSlider *horizontalSlider;
    QToolButton *next;
    QToolButton *FullScreen;
    QToolButton *Mode;
    QToolButton *list;
    QToolButton *play;
    QToolButton *volume;
    QSlider *horizontalSlider_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(442, 431);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/bluebird-ico.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QVideoWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 321, 201));
        previous = new QToolButton(centralwidget);
        previous->setObjectName(QString::fromUtf8("previous"));
        previous->setGeometry(QRect(170, 270, 31, 31));
        previous->setIconSize(QSize(72, 72));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(140, 250, 160, 16));
        horizontalSlider->setOrientation(Qt::Horizontal);
        next = new QToolButton(centralwidget);
        next->setObjectName(QString::fromUtf8("next"));
        next->setGeometry(QRect(250, 270, 31, 31));
        next->setIconSize(QSize(72, 72));
        FullScreen = new QToolButton(centralwidget);
        FullScreen->setObjectName(QString::fromUtf8("FullScreen"));
        FullScreen->setGeometry(QRect(410, 270, 21, 19));
        FullScreen->setIconSize(QSize(72, 72));
        Mode = new QToolButton(centralwidget);
        Mode->setObjectName(QString::fromUtf8("Mode"));
        Mode->setGeometry(QRect(100, 240, 31, 31));
        Mode->setIconSize(QSize(72, 72));
        list = new QToolButton(centralwidget);
        list->setObjectName(QString::fromUtf8("list"));
        list->setGeometry(QRect(310, 240, 31, 31));
        list->setIconSize(QSize(72, 72));
        play = new QToolButton(centralwidget);
        play->setObjectName(QString::fromUtf8("play"));
        play->setGeometry(QRect(210, 270, 31, 31));
        play->setIconSize(QSize(72, 72));
        volume = new QToolButton(centralwidget);
        volume->setObjectName(QString::fromUtf8("volume"));
        volume->setGeometry(QRect(350, 240, 21, 19));
        volume->setIconSize(QSize(72, 72));
        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(380, 240, 51, 20));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 442, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\351\237\263\350\247\206\351\242\221\346\222\255\346\224\276\345\231\250", nullptr));
        previous->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        next->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        FullScreen->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        Mode->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        list->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        play->setText(QString());
        volume->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
