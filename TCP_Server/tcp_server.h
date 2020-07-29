#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>

namespace Ui {
class TCP_Server;
}

class TCP_Server : public QWidget
{
    Q_OBJECT

public:
    explicit TCP_Server(QWidget *parent = nullptr);
    ~TCP_Server();
protected slots:
    void slot_newconnect();
    void slot_sendMsg();
    void slot_recvMsg();
    void slot_disconnect();

private:
    Ui::TCP_Server *ui;
    QTcpServer *tcp_server;
    QTcpSocket *tcp_socket;
};

#endif // TCP_SERVER_H
