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
    ui->pushButton->setEnabled(false);
    ui->lineEdit_3->setText("127.0.0.1");
    ui->lineEdit_4->setText("9999");

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slot_sendMsg()));  //发送信息
}

TCP_Client::~TCP_Client()
{
    delete ui;
}


//处理接入&断开按钮的槽函数
void TCP_Client::on_pushButton_2_clicked()
{
    if(!isconnected){
        tcp_socket = new QTcpSocket();
        tcp_socket->abort();//重置套接字
        ip = ui->lineEdit_3->text();
        port = ui->lineEdit_4->text().toInt();
        tcp_socket->connectToHost(ip,port);
        connect(tcp_socket,SIGNAL(connected()),this,SLOT(slot_connected()));  //建立连接
        connect(tcp_socket,SIGNAL(readyRead()),this,SLOT(slot_recvMsg()));    //接受信息
        connect(tcp_socket,SIGNAL(disconnected()),this,SLOT(slot_disconnected())); //服务器中断连接
    }
    else{
        ui->pushButton_2->setText("加入聊天室");
    }
}

//处理成功连接到服务器的槽
void TCP_Client::slot_connected()
{
    ui->pushButton->setEnabled(true);
    isconnected = true;
    QString Msg = "欢迎"+ui->lineEdit_2->text()+"进入聊天室";
    tcp_socket->write(Msg.toUtf8());
}

void TCP_Client::slot_disconnected()
{
    if(isconnected){
        QString Msg = "恭送"+ui->lineEdit_2->text()+"离开聊天室";
        tcp_socket->write(Msg.toUtf8());
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
            //QString local_display = QDateTime::currentDateTime().toString("yyyy-M-dd hh:mm:ss")+"\n"+ QString("%1:").arg(user_name)+send_msg;
            //ui->textBrowser->append(local_display);
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
        QString local_display = QDateTime::currentDateTime().toString("yyyy-M-dd hh::mm::ss")+"\n" + recv_msg;
        ui->textBrowser->append(local_display);
    }
}

