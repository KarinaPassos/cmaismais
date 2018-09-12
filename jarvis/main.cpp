#include "jarvis.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Jarvis w;
    w.show();

    return a.exec();
}
