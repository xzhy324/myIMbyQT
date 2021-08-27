#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w[3];
    for (int i =0; i<3; ++i)w[i].show();
//    Widget w;
//    w.show();
    return a.exec();
}
