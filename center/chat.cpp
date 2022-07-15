#include "chat.h"
#include "ui_chat.h"

chat::chat(tcp sock, Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat),
    db(db),
    sock(sock)
{
    ui->setupUi(this);
    name = "center";
    thd = new Thread(sock, this);
    connect(thd, SIGNAL(push_list(QString)), this, SLOT(push_msg(QString)));
    thd->start();
}

chat::~chat()
{
    delete ui;
    delete thd;
}

void chat::closeEvent(QCloseEvent *)
{
    int row=0;
    QListWidgetItem *message;
    query = "INSERT INTO chat_log VALUES ("+name+",시작) ";
    while(true)
    {
        message = ui->chat_list->takeItem(row++);
        if(message==nullptr)
            break;
        query += ", ("+name+","+message->text()+")";
    }
    sql_query.exec(query);
    if(sql_query.lastError().type()!=QSqlError::NoError)
        std::cout<<"error"<<std::endl;
    thd->terminate();
}

void chat::push_msg(QString msg)
{
    if(msg == "chat_end" || msg == "chat_end2")
    {
        this->close();
        return;
    }
    ui->chat_list->addItem(msg);
}

void chat::on_chat_btn_clicked()
{
    if(ui->chat_edit->text() =="")
        return;
    std::string send_msg = "send_msg/" + ui->chat_edit->text().toStdString();
    write(sock.sock, send_msg.c_str(), sizeof(send_msg));
    ui->chat_list->addItem("["+name+"] "+ui->chat_edit->text());
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
