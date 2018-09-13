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
        pontos.push_back(e->pos());
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
    QPointF p1,p2,p3;

    p1.setX(0);
    p1.setY(1);

    p2.setX(pontos.front().x());
    p2.setY(pontos.front().y());

    for (auto ponto: pontos){
       if (ponto.x() < p2.x()){
             p2.setX(ponto.x());
             p2.setY(ponto.y());
       }
    }

    linhas.push_back(p2);
    double angle;

    bool b;

    do {
        for (auto ponto: pontos){
            b = false;
            for (auto linha: linhas){
                //std::cout<<"("<<linha.x()<<","<<linha.y()<<")"<<std::endl; //loop infinito, ta adicionando o msm ponto trilhoes de vezes
                if (abs(ponto.x() - linha.x())>0.000000001 && abs(ponto.y() - linha.y())>0.000000001)
                    b = true;
            }

            if (b == true){
                continue;
            }

            angle = fakeAngle(p1,p2,ponto);
            if (angle > maxAngle){
                maxAngle = angle;
                p3 = ponto;
            }
        }

        linhas.push_back(p3);

        p1 = p2;
        p2 = p3;

    } while (abs(linhas.front().x() - linhas.back().x())>0.000000001 && abs(linhas.front().y() - linhas.back().y())>0.000000001);

}

double jarvis::fakeAngle(QPointF point1, QPointF point2, QPointF point3){
    point3.setX(point3.x()-point2.x());
    point3.setY(point3.y()-point2.y());

    return (1 - (point3.x()*point1.x() + point3.y()*point1.y())/((sqrt(pow (point3.x(),2) + pow(point3.y(),2)))*(sqrt(pow (point1.x(),2) + pow(point1.y(),2)))));
}

void jarvis::paintGL(){
    glBegin(GL_POINTS);

    glColor3f(0.0,1.0,0.0);
    for (auto ponto: pontos){
        std::cout<<"("<<ponto.x()<<","<<ponto.y()<<")"<<std::endl;
        glVertex3f(ponto.x(),ponto.y(),0.0);
    }

    glEnd();

    glBegin(GL_LINE_STRIP);

    glColor3f(1.0,0.0,0.5);
    for (auto linha: linhas){
        std::cout<<"("<<linha.x()<<","<<linha.y()<<")"<<std::endl;
        glVertex3f(linha.x(),linha.y(),0.0);
    }

    glEnd();
}
