#include "datadb.h"
#include <QDebug>

DataDB* DataDB::db = nullptr;

DataDB::DataDB()
{
    //完成数据库的创建
    //step1.完成数据库的驱动
    sqldb = QSqlDatabase::addDatabase("QSQLITE");//构造函数应该指定所使用的数据库软件类型
    //step2.配置数据库的基本信息
    sqldb.setDatabaseName("mydb_test.db"); //注意这个需要和所建立的数据库的设置名称相同
    sqldb.setHostName("localhost"); //将字符串替换成数据库存放电脑的ip地址
//    sqldb.setUserName("root");
//    sqldb.setPassword("123456");
//    sqldb.setPort(3306);//如果是本地数据库不需要设置端口号,具体端口号在数据库软件中查询
    //step3.开启数据库
    if(!sqldb.open()){
        QMessageBox::warning(NULL,"error","cannot open db!");
    }

}

DataDB::~DataDB()
{
    db->sqldb.close();
}

//单例设计模式
DataDB* DataDB::getDatabaseInstance()
{
    if(db==nullptr){
        db =new DataDB;
    }
    return db;
}


//静态sql示例
QStringList DataDB::selectAllUserOnline()
{
    QStringList ret;

    //数据库操作类，核心部分是sql语句
    //创建一个操作对象
    QSqlQuery query;
    //向数据库发送需要执行的sql语句
    query.exec("select * from USER");
    //查询结果一次性全部返回到query中，需要遍历该对象
    while(query.next()){
        ret.append(query.value("u_name").toString());
    }
    return ret;
}


//动态sql示例
struct UserInfo DataDB::getUserInfo(QString name, QString pwd)
{
    struct UserInfo user_info={"NoSuchGuy",""};
    QSqlQuery query;
    //向数据库发送一个预编译语句
    query.prepare("select * from user_info where name =:query_name and password =:query_pwd");
    //参数的动态绑定
    query.bindValue(":query_name",QVariant(name));
    query.bindValue(":query_pwd",QVariant(pwd));
    //执行查询
    query.exec();
    //保存查询结果
    while(query.next()){
        user_info.userName = query.value("name").toString();
        user_info.passWord = query.value("password").toString();
    }
    return user_info;
}

void DataDB::insertUser(struct UserInfo userinfo)
{
    QSqlQuery id_query;
    id_query.exec("select max(ID) from user_info;");
    int new_id = 0;
    if(id_query.first()){
        new_id = id_query.value("max(ID)").toInt() + 1;
    }
    qDebug() << "new_id:"<<new_id<<endl;
    QSqlQuery query;
    query.prepare("INSERT INTO user_info "
                  "(ID,name,password) "
                  "VALUES (:ID ,:name ,:password);");
    //参数的动态绑定
    query.bindValue(":ID",new_id);
    query.bindValue(":name",userinfo.userName);
    query.bindValue(":password",userinfo.passWord);
    //执行插入
    query.exec();
}

bool DataDB::verifyUser(QString name,QString pwd)
{
    QSqlQuery q;
    q.prepare("select * from user_info where name=\""+name+"\" and password=\""+pwd+"\";");
    q.exec();
    if(q.first())return true;
    return false;
}



