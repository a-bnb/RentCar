#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcp.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(tcp sock, Database db, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_chat_btn_clicked();

private:
    Ui::MainWindow *ui;
    tcp sock;
    Database db;

};
#endif // MAINWINDOW_H
