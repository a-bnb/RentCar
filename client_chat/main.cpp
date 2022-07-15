#include "mainwindow.h"
#include "tcp.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Database db;
    tcp sock;
    db.database_init();
    sock.connect_server();
    MainWindow w(sock, db);
    w.show();
    return a.exec();
}
