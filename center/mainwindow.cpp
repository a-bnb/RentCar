#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "tour.h"
#include "car.h"
#include "client_select.h"

mainwindow::mainwindow(Database db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainwindow),
      db(db)
{
    ui->setupUi(this);
}

mainwindow::~mainwindow()
{
    delete ui;
}


void mainwindow::on_user_btn_clicked()
{
    user window(db);
    window.setModal(true);
    window.exec();

}

void mainwindow::on_rent_btn_clicked()
{
    car window(db);
    window.setModal(true);
    window.exec();
}

void mainwindow::on_tour_btn_clicked()
{
    tour window(db);
    window.setModal(true);
    window.exec();

}

void mainwindow::on_chat_btn_clicked()
{
    client_select window(db);
    window.setModal(true);
    window.exec();
}
