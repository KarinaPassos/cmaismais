#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <QMainWindow>
#include <QMouseEvent>
#include <vector>
#include <QPoint>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>

namespace Ui {
class MainWindow;
}

class Ponto {
public:

    double x,y,z;

    void print(){
        std::cout << "(" << x << "," << y << "," << z << ")" << std::endl;
    }

    void set(double _x, double _y, double _z){
        x = _x;
        y = _y;
        z = _z;
    }

    Ponto (double _x, double _y, double _z){
        x = _x;
        y = _y;
        z = _z;
    }


};

class MainWindow : public QOpenGLWidget, public QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *e) ;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height);
    void bezier();
    void start();
private:
    std::vector<Ponto> pontos;
};

#endif // MAINWINDOW_H
