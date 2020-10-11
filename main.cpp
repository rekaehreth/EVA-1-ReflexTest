#include "reflextest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReflexTest w;
    w.show();
    return a.exec();
}
