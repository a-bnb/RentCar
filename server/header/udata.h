#ifndef __UDATA_H_
#define __UDATA_H_

#include <string>

using namespace std;

typedef struct
{
    int fd;
    int type;
    int chat_fd;
    char name[30];
}udata;

#endif
