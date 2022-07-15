#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include "tcp.h"

class Thread :public QThread
{
    Q_OBJECT

public:
    tcp sock;
    explicit Thread(tcp sock, QObject* parent = 0);
    void run();


signals:
    void push_list(const QString &msg);
};

#endif // THREAD_H
