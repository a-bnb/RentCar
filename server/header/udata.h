#ifndef __UDATA_H_
#define __UDATA_H_

#include <string>

using namespace std;

typedef struct
{
    int fd;
    int type;
    int chat_fd;
    string name;
}udata;

#endif
