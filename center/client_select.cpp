#include "client_select.h"
#include "ui_client_select.h"
#include "chat.h"
using namespace  std;

vector<string> split(string str, char Delimiter) {
    istringstream iss(str);             // istringstream에 str을 담는다.
    string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
    vector<string> result;

    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
    }

    return result;
}

client_select::client_select(Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client_select),
    db(db)
{
    ui->setupUi(this);
    this->sock.connect_server();
    this->sock.update("update/center/center");
    //this->on_refresh_btn_clicked();
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
    std::cout<<"showclnt"<<std::endl;
    write(sock.sock, "show_clnt", sizeof("show_clnt"));
    read(sock.sock, msg, sizeof(msg));
    vector<string> wait_list = split((string)msg, '/');
    for(string clnt : wait_list)
    {
        std::cout<<clnt<<std::endl;
        if(clnt == "show_end")
            break;
        if(clnt != "list")
            ui->clnt_list->addItem(QString::fromStdString(clnt));
    }
    ui->clnt_list->show();
}

void client_select::on_connect_btn_clicked()
{
    std::string send_msg;
    send_msg = "con_clnt/"+ui->clnt_list->currentItem()->text().toStdString();
    cout<<send_msg<<endl;
    write(sock.sock, send_msg.c_str(), sizeof(send_msg));

    chat window(sock, db);
    window.setModal(true);
    window.exec();
}

void client_select::on_exit_btn_clicked()
{
    this->close();
}

void client_select::on_clnt_list_itemClicked()
{
    check=true;
}
