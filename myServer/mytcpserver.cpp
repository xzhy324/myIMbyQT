#include "mytcpserver.h"
#include <QMessageBox>
#include <QDebug>

MyTcpServer* MyTcpServer::_server = nullptr;

MyTcpServer::MyTcpServer()
{
}
void MyTcpServer::incomingConnection(qintptr handle)
{
    //保存当前用户的socket
    QTcpSocket *clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(handle);
    client_sockets.append(clientSocket);
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(getMsg()));
    qDebug()<<"client connected\n";
}

void MyTcpServer::getMsg()
{
    QTcpSocket *cur_socket = (QTcpSocket*)this->sender();
    QString buf = cur_socket->readAll();
    QMessageBox::warning(nullptr,"warning",buf);
}

MyTcpServer* MyTcpServer::getTcpServerInstance()
{
    if(_server == nullptr){
        _server = new MyTcpServer();
        _server->listen(QHostAddress::Any, 1234);
        qDebug() <<"server is created!\n";
    }
    return _server;
}
