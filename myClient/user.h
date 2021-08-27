#ifndef USER_H
#define USER_H

#include <QWidget>

class User
{
public:
    User();
    QString getUsername();
    QString getPwd();
private:
    QString m_username;
    QString m_pwd;
};

#endif // USER_H
