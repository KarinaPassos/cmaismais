#ifndef PROJETO2_H
#define PROJETO2_H
#include <QWidget>
#include <projeto2gl.h>


class projeto2 : public QWidget {
Q_OBJECT
    public:
        void escolherCorDentro();
        void escolherCorFora();
        projeto2(QWidget *parent = nullptr);
    private:
        projeto2gl *GL;
};

#endif // PROJETO2_H
