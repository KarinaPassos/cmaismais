#include "Delaunay.h"
#include <QDebug>
#include <stdlib.h>
#include <time.h>

Delaunay::Delaunay(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("Delaunay");
    resize(600,300);
}

void Delaunay::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
}

void Delaunay::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton && e->modifiers() == Qt::KeyboardModifier::ControlModifier) {
        linhas.clear();
        pontos.clear();
        triangles.clear();
        jarvis.clear();
    }

    if (e->button() == Qt::RightButton && e->modifiers() == Qt::KeyboardModifier::ControlModifier){
        QPointF p = findPoint(Queue.front());
        setTriangle(Queue.front().p1,Queue.front().p2,p);
        Queue.pop();
    }
    if(e->button() == Qt::LeftButton){
        pontos.push_back(e->pos());
    }
    else if (e->button() == Qt::RightButton) {
        Delaunay::triangulacao();
    }
    update();
}

void Delaunay::initializeGL() {
    initializeOpenGLFunctions();
    glPointSize(7);
    glLineWidth(5);
}

void Delaunay::convexHull(){
    double  maxAngle=-10.0;
    QPointF p1(0,-1),p2,p3;

    std::sort(pontos.begin(), pontos.end(),
              [](QPointF a, QPointF b){ return a.x() <= b.x(); });

    linhas.clear();
    p2 = pontos.front();

    do {
       linhas.push_back(p2);
       if (p2 == linhas.front() && linhas.size()>1)
           break;
       for (int i = 0; i < pontos.size(); i++){
            if (std::find(std::begin(linhas), std::end(linhas), pontos[i]) != std::end(linhas) && linhas.size()<1) {
                continue;
            }

            double angle = fakeAngle(p1,p2,pontos[i]);
            if (angle > maxAngle){
                p3 = pontos[i];
                maxAngle = angle;
            }
       }

       p1 = p2;
       p2 = p3;

       maxAngle = -10.0;

    } while (linhas.back() != p3);
}

double Delaunay::fakeAngle(QPointF point1, QPointF point2, QPointF point3){
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

bool Delaunay::find(Edge e,std::vector<Triangle>& triangles){
    for (int i=0; i<triangles.size(); i++){
        if ((e == triangles[i].e1)==1 || (e == triangles[i].e2)==1 || (e == triangles[i].e3)==1)
            return true;
    }
    return false;
}

void Delaunay::setJarvis(){
    Edge aux;
    for (int i=0; i<linhas.size()-2; i++){
        aux.p1 = linhas[i];
        aux.p2 = linhas[i+1];
        jarvis.push_back(aux);
    }

}

QPointF Delaunay::findPoint(Edge e){
    QPointF p;
    double angle, maxAngle;
    angle = maxAngle = 0.0;
    Edge aux;

    print(e);

    for (auto ponto: pontos){
        aux.p1=ponto;
        aux.p2=e.p2;
        if(find(aux,triangles)==true)
            continue;
        aux.p1=e.p1;
        aux.p2=ponto;
        if(find(aux,triangles)==true)
            continue;

        if (ponto==e.p1 || ponto==e.p2)
            continue;

        angle = fakeAngle(e.p1,ponto,e.p2);

        if (angle<0)
            angle = -angle;

        if (angle>maxAngle){
            p = ponto;
            maxAngle = angle;
        }
    }
    std::cout<<"("<<p.x()<<","<<p.y()<<") \n"<<std::endl;

    return p;
}

bool Delaunay::orientation(QPointF point1, QPointF point2, QPointF point3){
    if ((((point1.x()-point3.x())*(point2.y()-point3.y())-(point2.x()-point3.x())*(point1.y()-point3.y()))>0))
        return true;
    else
        return false;
}

void Delaunay::setTriangle(QPointF point1, QPointF point2, QPointF point3){
    Edge aux;

    aux.p1=point1;
    aux.p2=point2;

    if ((point1.x() == 0 && point1.y() == 0) || (point2.x() == 0 && point2.y() == 0) || (point3.x() == 0 && point3.y() == 0))
        return;

    Triangle t;
    Edge e1,e2,e3;

    e1.p1=point1;
    e1.p2=point2;
    e2.p1=point2;
    e2.p2=point3;
    e3.p1=point3;
    e3.p2=point1;

    aux.p1=point3;
    aux.p2=point2;
    if (std::find(std::begin(jarvis), std::end(jarvis), e2) == std::end(jarvis)){
        if (find(aux,triangles) == false)
            Queue.push(aux);
    }
    aux.p1=point1;
    aux.p2=point3;
    if (std::find(std::begin(jarvis), std::end(jarvis), e2) == std::end(jarvis)){
        if (find(aux,triangles) == false)
            Queue.push(aux);
    }


    t.e1=e1;
    t.e2=e2;
    t.e3=e3;
    triangles.push_back(t);


}

void Delaunay::triangulacao(){
    convexHull();
    setJarvis();

    std::cout << "linhas[0]: (" << linhas[0].x() << "," << linhas[0].y() << ")" << std::endl;
    std::cout << "linhas[1]: (" << linhas[1].x() << "," << linhas[1].y() << ")" << std::endl;
    std::cout << "linhas[1]: (" << linhas[2].x() << "," << linhas[2].y() << ")" << std::endl;

    for (auto ponto: pontos)
        std::cout << "(" << ponto.x() << "," << ponto.y() << ")" << std::endl;

    QPointF p = findPoint(jarvis[0]);
    setTriangle(jarvis[0].p1,jarvis[0].p2,p);
}


void Delaunay::paintGL(){
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

    if (triangles.size()>0){
        glBegin(GL_TRIANGLES);
        srand (time(NULL));


        std::cout << "tsize: " << triangles.size() << std::endl;
        for (int i=0;i<triangles.size();i++){
            glColor3f((rand()%100)/(100.0),(rand()%100)/(100.0),(rand()%100)/(100.0));
            /*std::cout << "(" << triangles[i].e1.p1.x() << "," << triangles[i].e1.p1.y() << ") (" << triangles[i].e1.p2.x() << "," << triangles[i].e1.p2.y() << ") \n (" <<
                         triangles[i].e2.p1.x() << "," << triangles[i].e2.p1.y() << ") (" << triangles[i].e2.p2.x() << "," << triangles[i].e2.p2.y() << ") \n (" <<
                         triangles[i].e3.p1.x() << "," << triangles[i].e3.p1.y() << ") (" << triangles[i].e3.p2.x() << "," << triangles[i].e3.p2.y() << ") \n " << std::endl;
            */
            glVertex3f(triangles[i].e1.p1.x(),triangles[i].e1.p1.y(),0.0);
            glVertex3f(triangles[i].e2.p1.x(),triangles[i].e2.p1.y(),0.0);
            glVertex3f(triangles[i].e3.p1.x(),triangles[i].e3.p1.y(),0.0);
        }

        glEnd();
    }

}

Delaunay::~Delaunay(){

}
