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
    else if(clnt_msg.find("showclnt") == 0)
    {
        client_wait();
    }
    
}

void Recv::update()
{
    cout<<clnt_msg<<endl;
    vector<string> check_msg = Recv::split(clnt_msg, '/');
    strcpy(user_data->name, check_msg[2].c_str());
    if(check_msg[1] == "center")
        user_data->type=1;
    else
    {
        user_data->type=0;
        wait_list.push_back(*user_data);
    }
        
    
}

void Recv::client_wait()
{
    for(udata client : wait_list)
    {

    }
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