#ifndef CAR_ADD_H
#define CAR_ADD_H

#include <QDialog>
#include <QMessageBox>
#include <iostream>
#include <cstring>
#include "database.h"

namespace Ui {
class car_add;
}

class car_add : public QDialog
{
    Q_OBJECT

public:
    explicit car_add(Database db, QWidget *parent = nullptr);
    explicit car_add(QString model, Database db, QWidget *parent = nullptr);
    ~car_add();
    void edit_set();

private slots:
    void on_update_btn_clicked();

    void on_check_btn_clicked();

    void on_exit_btn_clicked();

private:
    Ui::car_add *ui;
    Database db;
    QString model;
    bool check;
    QSqlQuery sql_query;
    char query[1024];
};

#endif // CAR_ADD_H
