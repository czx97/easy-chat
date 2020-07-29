#include "server.h"
#include<QHostAddress>

Server::Server(QObject *parent,int port) : QTcpServer(parent)
{
    listen(QHostAddress::Any,port);

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"客户端连入";
    TcpClientSocket *tcpclientsocket = new TcpClientSocket(this);
    tcpclientsocket->setSocketDescriptor(socketDescriptor);
    client_socket_list.append(tcpclientsocket);


    connect(tcpclientsocket,&TcpClientSocket::updata_server,this,&Server::slot_recvMsg);
    connect(tcpclientsocket,&TcpClientSocket::client_disconnect,this,&Server::slot_disconnect);

}
//收到客户端断开连接请求的处理槽函数
void Server::slot_disconnect(int socketDescriptor)
{
    for(int i=0;i<client_socket_list.count();i++){
        QTcpSocket *item = client_socket_list.at(i);
        if(item->socketDescriptor() == socketDescriptor){
            item->close();
            item->deleteLater();
            client_socket_list.removeAt(i);
            emit update_widget(QString("%s退出聊天室").arg(socketDescriptor));
            return;
        }

    }
    return;
}
//收到客户端发送信息信号的处理槽函数
void Server::slot_recvMsg(QString Msg)
{
    for(int i=0;i<client_socket_list.count();i++){
        QTcpSocket* item = client_socket_list.at(i);
        item->write(Msg.toUtf8());
    }
    emit update_widget(Msg);

}
