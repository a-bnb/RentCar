#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Database db;
    db.database_init();
    QApplication a(argc, argv);
    mainwindow w(db);
    w.show();
    return a.exec();
}
