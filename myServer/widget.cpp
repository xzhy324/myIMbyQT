#include "widget.h"
#include "ui_widget.h"
#include "mytcpserver.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 基于当前对象创建TCP服务器并监听特定端口
    server = MyTcpServer::getTcpServerInstance();

}

Widget::~Widget()
{
    delete ui;
}

int Widget::getOnlineNum(){
    return onlineNum;
}

void Widget::on_pushButton_sendToAll_clicked()
{

}




