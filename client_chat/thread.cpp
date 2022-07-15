#include "thread.h"

Thread::Thread(tcp sock, QObject* parent):
    QThread(parent),
    sock(sock)
{
}

void Thread::run()
{
    char recv_msg[1024];
    while(true)
    {
        if(read(sock.sock, recv_msg, sizeof(recv_msg)) < 0)
            break;
        std::cout<<"msg: "<<recv_msg<<std::endl;
        emit Thread::push_list(QString::fromLocal8Bit(recv_msg));
        memset(recv_msg, 0, sizeof(recv_msg));
    }

}
