#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpSocket *clientSocket;
    void sendMsg(QString msg);

private slots:
    void recvMsg();
    void on_sendButton_clicked();
    void on_loginButton_clicked();
    void on_registerButton_clicked();
};
#endif // WIDGET_H
