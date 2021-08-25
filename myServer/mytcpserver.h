#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
private:
    static MyTcpServer* _server;
    MyTcpServer();
    QList <QTcpSocket*> client_sockets;

private slots:
    void getMsg();
private:
    virtual void incomingConnection(qintptr handle)override;
public:
    static MyTcpServer* getTcpServerInstance();
};

#endif // MYTCPSERVER_H
