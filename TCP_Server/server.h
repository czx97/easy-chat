#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include<QTcpSocket>
#include<QList>
#include"tcpclientsocket.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr,int port=0);
    QList<TcpClientSocket*>client_socket_list;
protected:
    void incomingConnection(qintptr);

signals:
    void update_widget(QString);

public slots:
    void slot_disconnect(int );
    void slot_recvMsg(QString);

};

#endif // SERVER_H
