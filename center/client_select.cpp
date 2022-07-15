#include "client_select.h"
#include "ui_client_select.h"
#include "chat.h"

client_select::client_select(Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client_select),
    db(db)
{
    ui->setupUi(this);
    this->sock.connect_server();
    this->sock.update();
    this->on_refresh_btn_clicked();
}

client_select::~client_select()
{
    delete ui;
}

void client_select::closeEvent(QCloseEvent *)
{
    shutdown(sock.sock, SHUT_RDWR);
}

void client_select::on_refresh_btn_clicked()
{
    ui->clnt_list->clear();
    write(sock.sock, "show_clnt", sizeof("show_clnt"));
    QString recv_msg;
    while(true)
    {
        read(sock.sock, msg, sizeof(msg));
        recv_msg = QString::fromLocal8Bit(msg);
        if(recv_msg == "show_end")
        {
            return;
        }
        ui->clnt_list->addItem(recv_msg);
    }
}

void client_select::on_connect_btn_clicked()
{
    std::string send_msg;
    send_msg = "con_clnt/"+ui->clnt_list->currentItem()->text().toStdString();
    write(sock.sock, send_msg.c_str(), sizeof(send_msg));

    this->close();
    chat window(sock, db);
    window.setModal(true);
    window.exec();
    this->show();
}

void client_select::on_exit_btn_clicked()
{
    this->close();
}

void client_select::on_clnt_list_itemClicked()
{
    check=true;
}
