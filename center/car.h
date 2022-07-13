#ifndef CAR_H
#define CAR_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QTableWidget>
#include "database.h"

namespace Ui {
class car;
}

class car : public QDialog
{
    Q_OBJECT

public:
    explicit car(Database db, QWidget *parent = nullptr);
    ~car();

private slots:
    void on_refresh_btn_clicked();

    void on_add_btn_clicked();

    void on_remove_btn_clicked();

    void on_edit_btn_clicked();

    void on_reserv_btn_clicked();

    void on_exit_btn_clicked();

    void on_table_itemClicked();

private:
    Ui::car *ui;
    Database db;
    QSqlQuery sql_query;
    char query[1024];
    bool check;
};

#endif // CAR_H
