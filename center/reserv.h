#ifndef RESERV_H
#define RESERV_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QTableWidget>
#include "database.h"

namespace Ui {
class reserv;
}

class reserv : public QDialog
{
    Q_OBJECT

public:
    explicit reserv(Database db, QWidget *parent = nullptr);
    ~reserv();

private slots:
    void on_refresh_btn_clicked();

    void on_add_btn_clicked();

    void on_remove_btn_clicked();

    void on_edit_btn_clicked();

    void on_exit_btn_clicked();

    void on_table_itemClicked();

private:
    Ui::reserv *ui;
    Database db;
    QSqlQuery sql_query;
    char query[1024];
    bool check;
};

#endif // RESERV_H
