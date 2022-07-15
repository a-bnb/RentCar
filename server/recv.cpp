#include "header/recv.h"
#include "header/database.h"
#include "header/udata.h"
#include "header/size.h"

using namespace std;

void Recv::Recv_main(udata* userdata, string msg)
{
    clnt_msg = msg;
    user_data = userdata;
    if(clnt_msg.find("update") == 0)
    {
        update();
    }
    else if(clnt_msg.find("show_clnt") == 0)
    {
        show_wait();
    }
    else if(clnt_msg.find("con_clnt") == 0)
    {
        connect_client();
    }
    else if(clnt_msg.find("con_serv") == 0)
    {
        connect_server();
    }
    else if(clnt_msg.find("send_msg") == 0)
    {
        send_msg();
    }
    else if(clnt_msg.find("chat_end") == 0)
    {
        chat_end();
    }
    
}

void Recv::update()
{
    cout<<clnt_msg<<endl;
    vector<string> check_msg = Recv::split(clnt_msg, '/');
    user_data->name = check_msg[2];
    if(check_msg[1] == "center")
        user_data->type=1;
    else if(check_msg[1] == "client")
    {
        user_data->type=0;
        wait_list.push_back(*user_data);
    }
    cout<<user_data->name<<": "<<user_data->fd<<endl;
}

void Recv::show_wait()
{
    string msg = "list";
    for(udata client : wait_list)
    {
        if(client.name != "")
            msg += "/"+client.name;
    }
    msg += "/show_end";
    write(user_data->fd, msg.c_str(), sizeof(msg));

}

void Recv::connect_client()
{
    cout<<"\nconnect_client()"<<endl;
    vector<string> check_msg = Recv::split(clnt_msg, '/');
    string msg = "con_serv/";
    udata empty;
    empty.name = "";
    for(udata &client : wait_list)
    {
        if(client.name == check_msg[1])
        {
            msg += to_string(user_data->fd);
            cout<<"msg: "<<msg<<endl;
            write(client.fd, msg.c_str(), sizeof(msg));
            user_data->chat_fd = client.fd;
            client = empty;
            break;
        }
    }
}

void Recv::connect_server()
{
    cout<<"\nconnect_server()"<<endl;
    vector<string> check_msg = Recv::split(clnt_msg, '/');
    user_data->chat_fd = stoi(check_msg[1]);
    cout<<"client chat_fd: "<<user_data->chat_fd<<endl;
}

void Recv::send_msg()
{
    cout<<"\nsend_msg()"<<endl;
    vector<string> check_msg = Recv::split(clnt_msg, '/');
    char buf[1024];
    string msg;
    cout<<user_data->name<<".chat_fd: "<<user_data->chat_fd<<endl;
    msg = "[" + user_data->name + "] " + check_msg[1];    
    strcpy(buf,msg.c_str());
    write(user_data->chat_fd, buf, sizeof(buf));
}

void Recv::chat_end()
{
    write(user_data->chat_fd, "chat_end2", sizeof("chat_end2"));
    user_data->chat_fd = 0;
}

vector<string> Recv::split(string str, char Delimiter) {
    istringstream iss(str);             // istringstream에 str을 담는다.
    string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼 
    vector<string> result;
 
    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
    }
 
    return result;
}