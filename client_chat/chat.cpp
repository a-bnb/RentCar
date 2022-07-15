#include "chat.h"
#include "ui_chat.h"

chat::chat(tcp sock, Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat),
    db(db),
    sock(sock)
{
    ui->setupUi(this);
    thd = new Thread(sock, this);
    connect(thd, SIGNAL(recv()), this, SLOT(push_msg(QString)));
    thd->start();
}

chat::~chat()
{
    delete ui;
}

void chat::closeEvent(QCloseEvent *)
{
    write(sock.sock, "chat_end", sizeof("chat_end"));
    delete thd;
}

void chat::push_msg(QString msg)
{
    if(msg == "chat_end")
    {
        this->close();
        return;
    }
    ui->chat_browser->append(msg);
}

void chat::on_chat_btn_clicked()
{
    std::string chat = ui->chat_edit->text().toStdString();
    std::string send_msg = "send_msg/" + chat;
    write(sock.sock, send_msg.c_str(), sizeof(send_msg));
    ui->chat_edit->clear();
}

void chat::on_chat_edit_returnPressed()
{
    this->on_chat_btn_clicked();
}

void chat::on_exit_btn_clicked()
{
    write(sock.sock, "chat_end", sizeof("chat_end"));
    this->close();
}
