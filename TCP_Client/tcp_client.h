#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpSocket>


namespace Ui {
class Widget;
}

class TCP_Client : public QWidget
{
    Q_OBJECT

public:
    explicit TCP_Client(QWidget *parent = nullptr);
    ~TCP_Client();

protected slots:
    void slot_sendMsg();
    void slot_recvMsg();
    void slot_init();
    void slot_connected();
    void slot_disconnected();

private:
    Ui::Widget *ui;
    bool isconnected;
    QTcpSocket *tcp_socket;
};

#endif // WIDGET_H
