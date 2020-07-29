#include "tcp_server.h"
#include "ui_tcp_server.h"
#include<QDateTime>
#include<QMessageBox>
#include<QDebug>

TCP_Server::TCP_Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCP_Server)
{
    ui->setupUi(this);
    setWindowTitle("TCP服务器");
    /***************初始化连接*********************/
    tcp_server = new QTcpServer(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slot_sendMsg()));
    /***************调用Listen监听端口&绑定IP和端口****************/
    if(tcp_server->listen(QHostAddress::Any,9999)){
        qDebug()<<"listen ok";
        connect(this->tcp_server,SIGNAL(newConnection()),this,SLOT(slot_newconnect()));
    }
    else{
        qDebug()<<"listen err";
    }
}

TCP_Server::~TCP_Server()
{
    delete ui;
}
//建立连接的槽函数
void TCP_Server::slot_newconnect()
{
    tcp_socket = new QTcpSocket(this);
    tcp_socket = tcp_server->nextPendingConnection();
    QHostAddress client_addr = tcp_socket->peerAddress();
    ui->textBrowser->append("欢迎IP: "+client_addr.toString()+"进入聊天室");
    connect(tcp_socket,SIGNAL(readyRead()),this,SLOT(slot_recvMsg()));
    connect(tcp_socket,SIGNAL(disconnected()),this,SLOT(slot_disconnect()));
}
//断开连接的槽函数
void TCP_Server::slot_disconnect()
{
    ui->textBrowser->append("客户端断开连接");
    tcp_socket->close();
    tcp_socket->deleteLater();
}
//处理接受消息的槽函数
void TCP_Server::slot_recvMsg()
{
    QString recv_Msg = tcp_socket->readAll();
    //QHostAddress client_addr = tcp_socket->peerAddress();
    //int client_port =tcp_socket->peerPort();
    QString local_display = QDateTime::currentDateTime().toString("yyyy-M-dd hh:mm:ss")+"\n"+recv_Msg;
    ui->textBrowser->append(local_display);

}
//处理消息发送的槽函数
void TCP_Server::slot_sendMsg()
{
    if(tcp_socket!=nullptr){
        QString send_Msg = ui->lineEdit->text();
        if(!send_Msg.isEmpty()){
            tcp_socket->write(send_Msg.toUtf8());
            QString local_display = QDateTime::currentDateTime().toString("yyyy-M-dd hh:mm:ss")+"\n"+"服务器:"+send_Msg;
            ui->textBrowser->append(local_display);
            ui->lineEdit->clear();
        }
        else
            QMessageBox::warning(this,"错误","发送内容不能为空");

    }
    else {
        QMessageBox::warning(this,"错误","请先建立TCP连接");
    }

}
