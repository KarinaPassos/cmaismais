#include "jarvis.h"
#include <iostream>
#include <vector>

jarvis::jarvis(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("hi");
    resize(600,300);
}

void jarvis::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
}



void jarvis::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        pontos.insert(e->pos());
        update();
    }
    else if (e->button() == Qt::RightButton) {
        jarvis::convexHull();
        update();
    }
}

void jarvis::initializeGL() {
    initializeOpenGLFunctions();
    glPointSize(7);
    glLineWidth(7);
}

void jarvis::convexHull(){
    double maxAngle = 0.0;
    QPointF first,p,p1;
    p.setX(*pontos.begin().x());
    p.setY(*pontos.begin().y());

    for (auto ponto: pontos){
        if (ponto.x() < p.x()){
            p.setX(ponto.x());
            p.setY(ponto.y());
        }
    }

    linhas.insert(p);
    first.setX(p.x());
    first.setY(p.y());

    int b = 0;

    while (b == 0){
        for (auto ponto: pontos){
            if (fakeAngle(p,ponto) > maxAngle){
                maxAngle = fakeAngle(p,ponto);
                p1 = ponto;
            } else if (fakeAngle(p,ponto) == maxAngle){
                if (((ponto.x()-p.x())*(ponto.x()-p.x())+(ponto.y()-p.y())*(ponto.y()-p.y()))>((p1.x()-p.x())*(p1.x()-p.x())+(p1.y()-p.y())*(p1.y()-p.y())))
                    //calcula a distancia, pra no caso de terem dois pontos com o mesmo angulo, catar o com a maior distancia
                    p1 = ponto;
            }
        }
        linhas.insert(p1);
        std::cout << b << std::endl;

        p = p1;
        if (p.x() == first.x() && p.y() == first.y())
            b = 1;
    }


    for (auto linha: linhas){
        std::cout << "(" << linha.x() << "," << linha.y() << ")" << std::endl;
    }
    std::cout << linhas.size() << std::endl;

}

double jarvis::fakeAngle(QPointF origin, QPointF point){

    point.setX(point.x() - origin.x());
    point.setY(point.y() - origin.y());

    return (1 - (point.x())/sqrt(point.x()*point.x()+point.y()*point.y()));

}

void jarvis::paintGL(){
    glBegin(GL_POINTS);

    glColor3f(0.0,1.0,0.0);
    for (auto ponto: pontos){
        glVertex3f(ponto.x(),ponto.y(),0.0);
    }

    glEnd();

    glBegin(GL_LINE_STRIP);

    glColor3f(1.0,0.0,0.0);
    for (auto linha: linhas){
        glVertex3f(linha.x(),linha.y(),0.0);
    }

    glEnd();
}
