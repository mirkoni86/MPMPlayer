#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QDate>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setOrganizationName("Волощук Константин");
    a.setOrganizationDomain("x.com");
    a.setApplicationName("APlayer");
    w.setWindowTitle("APlayer");
    a.setApplicationVersion("0.1."  + QString::number(QDate::currentDate().year() - 2000)
                                                   + QString::number(QDate::currentDate().month())
                                                   + QString::number(QDate::currentDate().day()));

    w.show();
     return a.exec();
}
