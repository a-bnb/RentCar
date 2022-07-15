#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chat.h"

MainWindow::MainWindow(tcp sock, Database db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      sock(sock),
      db(db)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_chat_btn_clicked()
{
    chat window("test", sock, db);
    window.setModal(true);
    window.exec();
    this->show();
}
