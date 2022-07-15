#ifndef TCP_H
#define TCP_H

#include <QMessageBox>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

class tcp
{
public:
    int sock = 0;
    std::string ip = "10.10.20.233";
    std::string port = "9010";
    struct sockaddr_in serv_addr;
    void connect_server()
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());
        serv_addr.sin_port = htons(atoi(port.c_str()));

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        {
            QMessageBox msgBox;
            msgBox.setText("Connect Error");
            msgBox.exec();
            exit(1);
        }
    }
    void update()
    {
        std::string msg = "update/center/center";
        write(sock, msg.c_str(), sizeof(msg));
    }
};

#endif // TCP_H
