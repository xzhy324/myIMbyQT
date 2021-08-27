#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    db = DataDB::getDatabaseInstance();
    // 基于当前对象创建TCP服务器并监听特定端口
    server = MyTcpServer::getTcpServerInstance();
    //当接受到msg时，在服务器端显示
    connect(server,SIGNAL(dealMessage(QString)),this,SLOT(displayMsg(QString)));
}

Widget::~Widget()
{
    delete ui;
    delete server;
    delete db;
}


void Widget::on_pushButton_sendToAll_clicked()
{
    QString msg = ui->lineEdit->text();
    server->sendToAllMsg(msg);
}

void Widget::displayMsg(QString msg)
{

    ui->server_display->insertPlainText(msg+"\n");
}




