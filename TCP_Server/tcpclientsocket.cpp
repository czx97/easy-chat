#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject * parent)
{
    connect(this,&TcpClientSocket::readyRead,this,&TcpClientSocket::slot_recv);
    connect(this, &TcpClientSocket::disconnected, this, &TcpClientSocket::slot_disconnect);

}

void TcpClientSocket::slot_recv()
{
    QString recvMsg = this->readAll();
    emit updata_server(recvMsg);
}

void TcpClientSocket::slot_disconnect()
{
    emit client_disconnect(this->socketDescriptor());
}
