#include "delaunay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Delaunay w;
    w.show();

    return a.exec();
}
