#include "jarvis.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    jarvis w;
    w.show();

    return a.exec();
}
