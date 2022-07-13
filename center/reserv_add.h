#ifndef RESERV_ADD_H
#define RESERV_ADD_H

#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <iostream>
#include <cstring>
#include "database.h"

namespace Ui {
class reserv_add;
}

class reserv_add : public QDialog
{
    Q_OBJECT

public:
    explicit reserv_add(Database db, QWidget *parent = nullptr);
    explicit reserv_add(QString id, Database db, QWidget *parent = nullptr);
    ~reserv_add();
    void edit_set();

private slots:
    void on_refresh_btn_clicked();

    void on_add_btn_clicked();


    void on_calendar_clicked(const QDate &date);

    void on_Car_table_itemClicked(QTableWidgetItem *item);

    void on_user_table_itemClicked(QTableWidgetItem *item);

    void on_exit_btn_clicked();

private:
    Ui::reserv_add *ui;
    Database db;
    bool check;
    int price_base;
    QString id;
    QSqlQuery sql_query;
    char query[1024];
};

#endif // RESERV_ADD_H
