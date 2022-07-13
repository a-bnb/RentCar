#include "header/server.h"

void Server::Main_Func()
{
    struct sockaddr_in addr, client_addr;
    socklen_t addrlen, clnt_len;
    int listen_fd; 
    int port, client_fd, read_cnt, i;
    char buf[SIZE_CONST::BUF_SIZE];  

    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0))==-1)
        exit(1);

    addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listen_fd, (struct sockaddr *)&addr, addrlen) == -1)
        exit(1);

    listen(listen_fd, 5);

    events = (struct epoll_event *)malloc(sizeof(struct epoll_event) * SIZE_CONST::EPOLL_SIZE);
    if((epoll_fd = epoll_create(100)) == -1)
        exit(1);

    ev.events = EPOLLIN;
    ev.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);
    memset(user_fds, -1, sizeof(int) * SIZE_CONST::BUF_SIZE);
    
    while(true)
    {
        event_cnt = epoll_wait(epoll_fd, events, SIZE_CONST::EPOLL_SIZE, -1);
        if(event_cnt == -1)
            exit(1);
        for(i=0; i<event_cnt; i++)
        {
            if(events[i].data.fd == listen_fd)
            {
                clnt_len = sizeof(struct sockaddr);
                client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &clnt_len);
                user_fds[client_fd] = 1;
                
                user_data = new udata;
                user_data->fd = client_fd;

                ev.events = EPOLLIN;
                ev.data.ptr = user_data;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev);
            }
            else
            {
                user_data = (udata*)events[i].data.ptr;
                memset(buf, 0x00, SIZE_CONST::BUF_SIZE);
                read_cnt = read(user_data->fd, buf, SIZE_CONST::BUF_SIZE);
                if(read_cnt<=0)
                {
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, user_data->fd, events);
                    close(user_data->fd);
                    user_fds[user_data->fd] = -1;
                    delete user_data;
                }
                else    
                {
                    cout<<"buf:"<<buf<<endl;
                    string clnt_msg(buf);
                    Server::Recv_main(user_data, clnt_msg);
                }
                
            }
        }
    }
}


