#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>

class TcpClientSocket:public QTcpSocket
{
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent = 0);
private:
    int number;
signals:
    void updata_server(QString);
    void client_disconnect(int socketDescriptor);
protected slots:
    void slot_recv();
    void slot_disconnect();
};

#endif // TCPCLIENTSOCKET_H
