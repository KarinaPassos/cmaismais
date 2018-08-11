#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("botão esquerdo: adicionar pontos // botão direito: suavizar a poligonal");
    resize(600,300);
}

void MainWindow::resizeGL(int width, int height)
{
    //admito que peguei essa função resizeGL pronta pq eu tava tendo sérios problemas com conversão de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        pontos.push_back(e->pos());
        update();
    }
    else if (e->button() == Qt::RightButton) {
        MainWindow::suavizar();
    }
}

void MainWindow::suavizar(){
    double a1,a2,b1,b2,x1,x2,y1,y2;
    QPointF p1,p2;
    int i = 0;

    if (pontos.size()>2){
        /*reta ax + b, a1x+b1 é a reta de trás e a2x+b2 é a reta da frente
        //explicação do que é cada variável aqui: https://imgur.com/bKZz0zN
        eu dividi tanto a reta de trás quanto a da frente, de cada ponto, em 4 partes, e peguei a parte "mais perto do ponto"
        */

        std::vector<QPointF> aux;
        aux.push_back(pontos.front()); //já coloquei o primeiro ponto no vetor novo, já que ele não vai ser descartado

        for (i=1; i<pontos.size()-1; i++){
            a1 = (pontos[i].y()-pontos[i-1].y())/(pontos[i].x() - pontos[i-1].x());
            b1 = pontos[i-1].y() - a1*pontos[i-1].x();
            x1 = pontos[i-1].x() + 3*(pontos[i].x()-pontos[i-1].x())/4;
            y1 = a1 * x1 + b1;
            p1.setX(x1);
            p1.setY(y1);

            a2 = (pontos[i+1].y()-pontos[i].y())/(pontos[i+1].x() - pontos[i].x());
            b2 = pontos[i].y() - a2*pontos[i].x();
            x2 = pontos[i].x() + (pontos[i+1].x()-pontos[i].x())/4;
            y2 = a2 * x2 + b2;
            p2.setX(x2);
            p2.setY(y2);

            aux.push_back(p1);
            aux.push_back(p2);
        }
        aux.push_back(pontos.back()); //botei o ultimo ponto pq ele nao vai ser descartado
        pontos = aux;
     }
    update();
}

void MainWindow::initializeGL() {
    initializeOpenGLFunctions();
    glLineWidth(7);
}

void MainWindow::paintGL(){
    glBegin(GL_LINE_STRIP);

    int i = 0;
    for (auto ponto : pontos ){
        glVertex3f(ponto.x(),ponto.y(),0.0);
        glColor3f(0.7,(i/10.),1.0-(i/2.));
        i+=1;
    }

    glEnd();
}


MainWindow::~MainWindow()
{

}

