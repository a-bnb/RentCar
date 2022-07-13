#ifndef TOUR_H
#define TOUR_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QTableWidget>
#include "database.h"

namespace Ui {
class tour;
}

class tour : public QDialog
{
    Q_OBJECT

public:
    explicit tour(Database db, QWidget *parent = nullptr);
    ~tour();

private slots:
    void on_add_btn_clicked();

    void on_refresh_btn_clicked();

    void on_remove_btn_clicked();

    void on_table_itemClicked();

    void on_edit_btn_clicked();

    void on_exit_btn_clicked();

private:
    Ui::tour *ui;
    Database db;
    QSqlQuery sql_query;
    char query[1024];
    bool check;
};

#endif // TOUR_H
