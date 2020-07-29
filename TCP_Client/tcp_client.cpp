#include "tcp_client.h"
#include "ui_widget.h"
#include<QDateTime>
#include<QMessageBox>
#include<QDebug>

TCP_Client::TCP_Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("TCP客户端");
    isconnected = false;
    tcp_socket = new QTcpSocket();


    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(slot_init()));  //发起连接

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slot_sendMsg()));  //发送信息

    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(slot_disconnected())); //中断连接
}

TCP_Client::~TCP_Client()
{
    delete ui;
}



void TCP_Client::slot_init()
{
    tcp_socket = new QTcpSocket();
    tcp_socket->abort();//重置套接字
    tcp_socket->connectToHost("127.0.0.1",9999);
    connect(tcp_socket,SIGNAL(connected()),this,SLOT(slot_connected()));   //建立连接
}

//处理成功连接到服务器的槽
void TCP_Client::slot_connected()
{
    isconnected = true;
    ui->textBrowser->append("成功连接到服务器   "+QDateTime::currentDateTime().toString("yyyy-M-dd hh:mm:ss"));
    connect(tcp_socket,SIGNAL(readyRead()),this,SLOT(slot_recvMsg()));    //接受信息
    connect(tcp_socket,SIGNAL(disconnected()),this,SLOT(slot_disconnected())); //服务器中断连接
}

//处理断开连接的槽
void TCP_Client::slot_disconnected()
{
    if(isconnected){
        //QMessageBox::warning(this,"警告","与服务器断开连接");
        ui->textBrowser->append("与服务器断开连接");
        isconnected = false;
        tcp_socket->close();
        tcp_socket->deleteLater();
    }
}

//处理发送信息的槽
void TCP_Client::slot_sendMsg()
{
    if(isconnected){
        QString send_msg = ui->lineEdit->text();
        QString user_name = ui->lineEdit_2->text();
        if(!send_msg.isEmpty()){
            QString local_display = QDateTime::currentDateTime().toString("yyyy-M-dd hh:mm:ss")+"\n"+ QString("%1:").arg(user_name)+send_msg;
            ui->textBrowser->append(local_display);
            send_msg = user_name+": "+send_msg;
            tcp_socket->write(send_msg.toUtf8());
            ui->lineEdit->clear();
        }
        else
           QMessageBox::warning(this,"错误","发送内容不能为空");
    }
    else
        QMessageBox::warning(this,"错误","未连接到服务器");

}
//处理接送信息的槽
void TCP_Client::slot_recvMsg()
{
    QString recv_msg = tcp_socket->readAll();
    qDebug()<<recv_msg;
    if(!recv_msg.isEmpty()){
        QString local_display = QDateTime::currentDateTime().toString("yyyy-M-dd hh::mm::ss")+"\n"+ "服务器:"+ recv_msg;
        ui->textBrowser->append(local_display);
    }
}




