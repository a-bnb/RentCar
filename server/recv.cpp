#include "header/recv.h"
#include "header/database.h"
#include "header/udata.h"
#include "header/size.h"

using namespace std;

void Recv::Recv_main(udata* userdata, string msg)
{
    clnt_msg = msg;
    user_data = userdata;
    if(clnt_msg.find("login") == 0)
    {
        login();
    }
    else if(clnt_msg.find("idcheck") == 0)
    {
        id_check();
    }
    else if(clnt_msg.find("signup") == 0)
    {
        sign_up();
    }    
    else if(clnt_msg.find("choose_date") == 0)
    {
        choose_date();
    }
    else if(clnt_msg.find("update") == 0)
    {        
        update();
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