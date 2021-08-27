#include "mytcpserver.h"
#include <QMessageBox>
#include <QDebug>

MyTcpServer* MyTcpServer::_server = nullptr;

MyTcpServer::MyTcpServer(QObject *parent):QTcpServer(parent)
{
    db = DataDB::getDatabaseInstance();
}

void MyTcpServer::incomingConnection(qintptr handle)
{
    //保存当前用户的socket
    QTcpSocket *clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(handle);


    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(getMsg()));
    connect(clientSocket,SIGNAL(disconnected()),this,SLOT(client_disconnected()));

    clientSocket->write("successfully connected!");
    qDebug()<<"client connected\n";

}


/**************************************SLOT*****************************************/
//
void MyTcpServer::getMsg()
{
    QTcpSocket *client_socket = (QTcpSocket*)this->sender();
    QString msg = client_socket->readAll();
    //QMessageBox::warning(nullptr,"warning",buf);
    emit dealMessage(msg);

    QString type = msg.mid(0,3);
    msg = msg.mid(4);
    qDebug()<<msg;
    if(type == "log"){
        int fen_ge = msg.indexOf(':');
        QString username = msg.mid(0,fen_ge);
        QString pwd = msg.mid(fen_ge+1);

        bool verified = db->verifyUser(username, pwd);
        if(verified){
            ClientList.insert(username,client_socket);
            client_socket->write("successfully log in!");
        }else{
            client_socket->write("wrong username or password!");
        }


    }else if(type == "reg"){
        int fen_ge = msg.indexOf(':');
        QString username = msg.mid(0,fen_ge);
        QString pwd = msg.mid(fen_ge+1);
        struct UserInfo userinfo{username,pwd};
        db->insertUser(userinfo);


    }else if(type == "msg"){
        int fen_ge = msg.indexOf(':');
        QString reciever = msg.mid(0,fen_ge);
        QString client_msg = msg.mid(fen_ge+1);
        ClientList.value(reciever)->write(client_msg.toUtf8());


    }

}

void MyTcpServer::client_disconnected()
{
    dealMessage("somebody offline")
    QTcpSocket *cur_socket = (QTcpSocket*)this->sender();
    qDebug()<<"client disconnected"<<endl;
    qDebug()<<&cur_socket<<endl;
    QString username =SocketToUsername(cur_socket);
    dealMessage(username+" offline");
    ClientList.erase( ClientList.find(username));
}
//
/**************************************SLOT*****************************************/



MyTcpServer* MyTcpServer::getTcpServerInstance()
{
    if(_server == nullptr){
        _server = new MyTcpServer();
        _server->listen(QHostAddress::Any, 1234);
        qDebug() <<"server is created!\n";
    }
    return _server;
}


void MyTcpServer::sendToAllMsg(QString msg)
{
    for(auto iter = ClientList.begin();iter != ClientList.end();iter++){
        iter.value()->write(msg.toUtf8());
    }
}

QString MyTcpServer::SocketToUsername(QTcpSocket *const &socket)
{
    QString ret = "NoSuchGuy";
    for(auto iter = ClientList.begin();iter != ClientList.end();iter++){
        if(iter.value()==socket){
            ret = iter.key();
            break;
        }
    }
    return ret;
}






