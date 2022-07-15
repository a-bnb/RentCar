#include "thread.h"

Thread::Thread(tcp sock, QObject* parent):
    QThread(parent),
    sock(sock)
{
}

void Thread::recv()
{
    char recv_msg[1024];
    while(read(sock.sock, recv_msg, sizeof (recv_msg)) != -1)
    {
        emit Thread::push_list((QString)recv_msg);
        memset(recv_msg, 0, sizeof(recv_msg));
    }

}
