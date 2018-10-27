#include "mainwindow.h"
#include <iostream>
#include <vector>
#include <limits>

#include "delaunay.h"

MainWindow::MainWindow(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("trabalho 2");
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
    //botao esquerdo: adicionar pontosDoPoligono
    //botao esquerdo + ctrl: fechar o poligono
    //botao direito: adicionar pontos ver se ta dentro ou fora do poligono

    if(e->button() == Qt::LeftButton){
        pontos.push_back(Vector2{
            (double) e->pos().x(),
            (double) e->pos().y()
        });
    }

    else if (e->button() == Qt::RightButton) {
        Delaunay delaunay;
        triangulos = delaunay.triangulate(pontos);
    }
    update();
}

void MainWindow::initializeGL() {
    initializeOpenGLFunctions();
    glLineWidth(7);
    glPointSize(7);
}

void MainWindow::paintGL(){
    glBegin(GL_LINE_STRIP);
    glColor3d(1.0, 0.0, 0.0);

    for (auto triangulo : triangulos){
        glVertex3d(triangulo.p1.x, triangulo.p1.y,0.0);
        glVertex3d(triangulo.p2.x, triangulo.p2.y,0.0);
        glVertex3d(triangulo.p3.x, triangulo.p3.y,0.0);

    }
    glEnd();

    glBegin(GL_POINTS);
        glColor3f(0.0,1.0,0.0);
        for (auto ponto : pontos){
            glVertex3d(ponto.x, ponto.y,0.0);
        }
    glEnd();
}
