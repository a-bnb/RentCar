#ifndef CLIENT_SELECT_H
#define CLIENT_SELECT_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QListWidget>
#include <vector>
#include <sstream>
#include "database.h"
#include "tcp.h"

namespace Ui {
class client_select;
}

class client_select : public QDialog, public tcp
{
    Q_OBJECT

public:
    explicit client_select(Database db, QWidget *parent = nullptr);
    ~client_select();
    void closeEvent(QCloseEvent *);

private slots:
    void on_refresh_btn_clicked();

    void on_connect_btn_clicked();

    void on_exit_btn_clicked();

    void on_clnt_list_itemClicked();

private:
    Ui::client_select *ui;
    Database db;
    tcp sock;
    bool check;
    QSqlQuery sql_query;
    char query[1024];
    char msg[1024];
};

#endif // CLIENT_SELECT_H
