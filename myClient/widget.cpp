#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //初始化连接
    clientSocket = new QTcpSocket(this);
    clientSocket->connectToHost("localhost",1234);

    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(recvMsg()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::recvMsg()
{
    QByteArray buf = clientSocket->readAll();
    ui->textBrowser->insertPlainText(QString::fromUtf8(buf)+'\n');
}

void Widget::sendMsg(QString msg)
{
    clientSocket->write(msg.toUtf8());
    qDebug()<<msg<<endl;
}

void Widget::on_sendButton_clicked()
{
    QString curInput = ui->inputEdit->toPlainText();
    QString recieverName = ui->lineEdit_reciever->text();
    if(curInput!=""){
        if(recieverName==""){
            QMessageBox::warning(NULL,"warning","the reciever cannot be empty!");
        }else{
            QString msg = "msg/"+recieverName+":"+curInput;
            sendMsg(msg);
        }

    }else{
        QMessageBox::warning(NULL,"warning","the msg cannot be empty!");
    }
}

void Widget::on_loginButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString pwd = ui->lineEdit_pwd->text();
    QString msg = "log/" + username + ":" + pwd;
    sendMsg(msg);
}

void Widget::on_registerButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString pwd = ui->lineEdit_pwd->text();
    QString msg = "reg/" + username + ":" + pwd;
    sendMsg(msg);
}
