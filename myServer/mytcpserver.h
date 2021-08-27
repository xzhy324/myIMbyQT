#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "datadb.h"

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
private:
    MyTcpServer(QObject *parent = 0);
    virtual void incomingConnection(qintptr handle)override;
    QString SocketToUsername(QTcpSocket *const &socket);

    DataDB *db;
    QMap <QString,QTcpSocket*>ClientList;
    static MyTcpServer* _server;

private slots:
    void getMsg();
    void client_disconnected();

public:
    static MyTcpServer* getTcpServerInstance();
    void sendToAllMsg(QString msg);

signals:
    void dealMessage(QString);
};

#endif // MYTCPSERVER_H
