#ifndef USER_ADD_H
#define USER_ADD_H

#include <QDialog>
#include <QMessageBox>
#include <iostream>
#include <cstring>
#include "database.h"

namespace Ui {
class user_add;
}

class user_add : public QDialog
{
    Q_OBJECT

public:
    explicit user_add(QString u_id, Database dbs, QWidget *parent = nullptr);
    explicit user_add(Database dbs, QWidget *parent = nullptr);
    ~user_add();
    void edit_set();

private slots:
    void on_check_btn_clicked();

    void on_exit_btn_clicked();

    void on_signup_btn_clicked();

private:
    Ui::user_add *ui;
    Database db;
    QString u_id;
    bool check;
    QSqlQuery sql_query;
    char query[1024];

};

#endif // USER_ADD_H
