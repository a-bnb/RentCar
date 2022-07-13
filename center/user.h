#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QTableWidget>
#include <QList>
#include <QSqlError>
#include "database.h"

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(Database db,QWidget *parent = nullptr);
    ~user();

private slots:
    void on_refresh_btn_clicked();

    void on_add_btn_clicked();

    void on_remove_btn_clicked();

    void on_usertable_itemClicked();

    void on_edit_btn_clicked();



    void on_exit_btn_clicked();

private:
    Ui::user *ui;
    Database db;
    bool check;
    QSqlQuery sql_query;
    char query[1024];

};

#endif // USER_H
