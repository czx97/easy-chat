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
}

TCP_Server::~TCP_Server()
{
    delete ui;
}

void TCP_Server::slot_update_widget(QString Msg)
{
    ui->textBrowser->append(Msg);

}

void TCP_Server::on_pushButton_clicked()
{
    port =ui->lineEdit->text().toInt();
    server = new Server(this,port);
    ui->textBrowser->append("成功创建聊天室，等待用户加入...");
    connect(server,&Server::update_widget,this,&TCP_Server::slot_update_widget);
    ui->pushButton->setEnabled(false);
}

void TCP_Server::on_pushButton_2_clicked()
{
    server->close();
    server->deleteLater();
    ui->textBrowser->clear();
    ui->pushButton->setEnabled(true);
}


