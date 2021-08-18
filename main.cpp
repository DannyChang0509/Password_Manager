#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::addLibraryPath("./plugins");

    MainWindow w;
    w.setWindowTitle(QObject::tr("Password Manager"));
    w.setWindowIcon(QIcon("icon_s.png"));
    w.show();
    return a.exec();
}
