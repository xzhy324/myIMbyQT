#ifndef DATADB_H
#define DATADB_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>

struct UserInfo{
    QString userName;
    QString passWord;
};


//数据库操作的封装类，采用单实例设计模式，且数据库的连接应该在软件ui界面初始化的时候执行
class DataDB
{
private:
    static DataDB* db;
    QSqlDatabase sqldb;
public:
    explicit DataDB();
    ~DataDB();

    struct UserInfo getUserInfo(QString name,QString pwd);

    QStringList selectAllUserOnline();

    bool verifyUser(QString name,QString pwd);

    static DataDB* getDatabaseInstance();

    //数据库插入新用户的功能
    void insertUser(struct UserInfo);
};

#endif // DATADB_H
