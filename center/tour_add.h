#ifndef TOUR_ADD_H
#define TOUR_ADD_H

#include <QDialog>
#include <QMessageBox>
#include <iostream>
#include <cstring>
#include "database.h"

namespace Ui {
class tour_add;
}

class tour_add : public QDialog
{
    Q_OBJECT

public:
    explicit tour_add(Database db, QWidget *parent = nullptr);
    explicit tour_add(QString name, Database db, QWidget *parent = nullptr);
    ~tour_add();
    void edit_set();

private slots:
    void on_check_btn_clicked();

    void on_update_btn_clicked();

    void on_exit_btn_clicked();

private:
    Ui::tour_add *ui;
    Database db;
    QString name;
    bool check;
    QSqlQuery sql_query;
    char query[1024];
};

#endif // TOUR_ADD_H
