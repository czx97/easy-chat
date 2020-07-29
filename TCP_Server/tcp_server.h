#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QWidget>
#include"server.h"

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
    void slot_update_widget(QString Msg);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::TCP_Server *ui;
    int port;
    Server *server;
};

#endif // TCP_SERVER_H
