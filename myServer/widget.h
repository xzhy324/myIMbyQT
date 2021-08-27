#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mytcpserver.h"
#include "datadb.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_pushButton_sendToAll_clicked();
    void displayMsg(QString msg);
private:
    Ui::Widget *ui;
    MyTcpServer *server;
    DataDB* db;
};
#endif // WIDGET_H
