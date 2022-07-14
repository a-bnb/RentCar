#ifndef __RECV_H_
#define __RECV_H_

#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <unistd.h>
#include "udata.h"
#include "size.h"
#include "database.h"
#include "event.h"

using namespace std;

class Recv : public Event
{
    public:
        Recv(){}
        ~Recv() {}
        void Recv_main(udata *userdata, string clnt_msg);
        vector<string> split(string str, char Delimiter);
        void update();
        void client_wait();
        void connect_client();
        void connect_server();
        void send_msg();
        void chat_end();

    private:
        char query[SIZE_CONST::BUF_SIZE];
        vector<udata> wait_list;
        udata* user_data;
        string clnt_msg;

};


#endif