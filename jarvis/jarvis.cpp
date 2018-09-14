#include "jarvis.h"
#include <iostream>
#include <vector>
#include <QDebug>

jarvis::jarvis(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("Jarvis");
    resize(600,300);
}

void jarvis::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
}

void jarvis::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton && e->modifiers() == Qt::KeyboardModifier::ControlModifier) {
        linhas.clear();
        pontos.clear();
    }
    if(e->button() == Qt::LeftButton){
        pontos.push_back(e->pos());
    }
    else if (e->button() == Qt::RightButton) {
        pontos.push_back(e->pos());
        jarvis::convexHull();
    }
    update();
}

void jarvis::initializeGL() {
    initializeOpenGLFunctions();
    glPointSize(7);
    glLineWidth(7);
}

void jarvis::convexHull(){
    double  maxAngle=-10.0;
    QPointF p1(0,-1),p2,p3;

    std::sort(pontos.begin(), pontos.end(),
              [](QPointF a, QPointF b){ return a.x() <= b.x(); });

    //qDebug() << "Vetor Organizado";
    for(const auto& ponto : pontos) {
        qDebug() << ponto;
    }
    //qDebug() << "------";

    linhas.clear();
    p2 = pontos.front();

    do {
       linhas.push_back(p2);
       if (p2 == linhas.front() && linhas.size()>1)
           break;
       for (int i = 0; i < pontos.size(); i++){
            if (std::find(std::begin(linhas), std::end(linhas), pontos[i]) != std::end(linhas) && linhas.size()<1) {
                //qDebug() << "Ponto " << pontos[i] << "ja faz parte do hull.";
                continue;
            }

            double angle = fakeAngle(p1,p2,pontos[i]);
            if (angle > maxAngle){
                p3 = pontos[i];
                maxAngle = angle;
                //qDebug() << "testando p1, p2, p3"  << p1 << p2 << p3 << "P3 com max angle." << maxAngle;
            } else if (angle == maxAngle){
                if (pow(p3.x(),2)+pow(p3.y(),2) < (pow(pontos[i].x(),2)+pow(pontos[i].y(),2))){
                        p3 = pontos[i];
                        maxAngle = angle;
                }
            }
       }

       p1 = p2;
       p2 = p3;

       maxAngle = -10.0;

    } while (linhas.back() != p3);
}

double jarvis::fakeAngle(QPointF point1, QPointF point2, QPointF point3){
    point3.setX(point3.x()-point2.x());
    point3.setY(point3.y()-point2.y());
    point1.setX(point1.x()-point2.x());
    point1.setY(point1.y()-point2.y());

    double angle = acos((point3.x()*point1.x() + point3.y()*point1.y())
                        /((sqrt(pow (point3.x(),2) + pow(point3.y(),2)))*(sqrt(pow (point1.x(),2) + pow(point1.y(),2)))));

    if (point3.x()*point1.y()-point3.y()*point1.x() > 0){
        angle = -angle;
    }

    return angle;
}

void jarvis::paintGL(){
    glBegin(GL_POINTS);

    glColor3f(0.0,1.0,0.0);
    for (auto ponto: pontos){
        glVertex3d(ponto.x(),ponto.y(),0.0);
    }

    glEnd();

    if (linhas.size() > 0) {
        glBegin(GL_LINE_STRIP);
        glColor3d(1.0,0.0,0.5);
        for (auto linha: linhas){
            glVertex3d(linha.x(),linha.y(),0.0);
        }
        glVertex3d(linhas[0].x(), linhas[0].y(), 0.0);
        glEnd();
    }
}
