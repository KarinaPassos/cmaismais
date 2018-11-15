#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("trabalho 5");
    resize(600,600);
}

void MainWindow::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        start();
        update();
    }
    else if (e->button() == Qt::RightButton) {
    }
}

void MainWindow::initializeGL() {
    initializeOpenGLFunctions();
    glPointSize(7);
}

void MainWindow::paintGL(){
    glBegin(GL_POINTS);

    int i = 0;
    for (auto ponto: pontos ){
        glVertex3f(ponto.x,ponto.y,0.0);
        glColor3f(0.7,(i/10.),1.0-(i/2.));
        i+=1;
    }

    glEnd();
}

void MainWindow::start(){
    Ponto p = new Ponto(0.0,0.0,0.0);
    p.set(245,118,94);
    pontos.push_back(p);
    p.set(21,58,17);
    pontos.push_back(p);
    p.set(101,18,207);
    pontos.push_back(p);
    p.set(222,187,356);
    pontos.push_back(p);
    p.set(55,507,302);
    pontos.push_back(p);
    p.set(559,501,207);
    pontos.push_back(p);
}

void MainWindow::bezier(){

}

MainWindow::~MainWindow()
{

}
