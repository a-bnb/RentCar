#include "chat.h"
#include "ui_chat.h"

chat::chat(QString name, tcp sock, Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat),
    db(db),
    sock(sock),
    name(name)
{
    ui->setupUi(this);
    sock.update("update/client/"+name);
    thd = new Thread(sock, this);
    connect(thd, SIGNAL(push_list(QString)), this, SLOT(push_msg(QString)));
    thd->start();
    ui->chat_list->addItem("상담원 연결 대기중...");
}

chat::~chat()
{
    delete ui;
    delete thd;
}

void chat::closeEvent(QCloseEvent *)
{
    write(sock.sock, "chat_end", sizeof("chat_end"));
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
    std::cout<<msg.toStdString()<<std::endl;
    std::string t_msg;
    if(msg == "chat_end")
    {
        this->close();
        return;
    }
    else if(msg.toStdString().find("con_serv") == 0)
    {
        t_msg = msg.toStdString();
        write(sock.sock, t_msg.c_str(), sizeof(t_msg));
        msg = "연결 성공!";
        check = true;
    }
    if(check)
        ui->chat_list->addItem(msg);
}

void chat::on_chat_btn_clicked()
{
    if(!check || ui->chat_edit->text() =="")
        return;
    std::string send_msg = "send_msg/" + ui->chat_edit->text().toStdString();
    write(sock.sock, send_msg.c_str(), sizeof(send_msg));
    ui->chat_list->addItem("["+name+"] "+ui->chat_edit->text());
    ui->chat_edit->clear();
}

void chat::on_chat_edit_returnPressed()
{
    if(!check)
        return;
    this->on_chat_btn_clicked();
}

void chat::on_exit_btn_clicked()
{
    this->close();
}
