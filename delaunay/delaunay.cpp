#include "Delaunay.h"
#include <iostream>
#include <QDebug>

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
    }
    if(e->button() == Qt::LeftButton){
        pontos.push_back(e->pos());
    }
    else if (e->button() == Qt::RightButton) {
        pontos.push_back(e->pos());
        Delaunay::triangulacao();
    }
    update();
}

void Delaunay::initializeGL() {
    initializeOpenGLFunctions();
    glPointSize(7);
    glLineWidth(7);
}

void Delaunay::convexHull(){
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

void Delaunay::triangulacao(){
    QPointF p;
    double angle,maxAngle;
    std::queue<Edge> Queue;
    Edge e1,e2,e3;
    Triangle t;

    convexHull();

    for (int i=0;i<linhas.size()-1;i++){
        e.p1 = linhas[i];
        e.p2 = linhas[i+1];
        jarvis.push_back(e);
    }

    e.p1=linhas[linhas.size()-1];
    e.p2=linhas[linhas.size()-2];

    for (int i=0; i < pontos.size(); i++){
        if (pontos[i] == e.p1 || pontos[i] == e.p2) {
            continue;
        }

        double angle = fakeAngle(e.p1,pontos[i],e.p2);
        if (angle > maxAngle){
            p = pontos[i];
            maxAngle = angle;
        } else if (angle == maxAngle){
            if (pow(p.x(),2)+pow(p.y(),2) > (pow(pontos[i].x(),2)+pow(pontos[i].y(),2))){
                    p = pontos[i];
                    maxAngle = angle;
            }
        }
   }

   if (((e.p1.x()-p.x())*(e.p2.y()-p.y())-(e.p2.x()-p.x())*(e.p1.y()-p.y()))>0){
       e1.p1=e.p2;
       e1.p2=p;
       e2.p1=p;
       e2.p2=e.p1;
       e3.p1=e.p1;
       e3.p2=e.p2;
   } else {
       e1.p1=e.p1;
       e1.p2=p;
       e2.p1=p;
       e2.p2=e.p2;
       e3.p1=e.p2;
       e3.p2=e.p1;
   }
   t.e1=e1;
   t.e2=e2;
   t.e3=e3;

   if (std::find(std::begin(jarvis), std::end(jarvis), e1) == std::end(jarvis)) {
       Queue.push(e1);
   }
   if (std::find(std::begin(jarvis), std::end(jarvis), e2) == std::end(jarvis)) {
       Queue.push(e2);
   }

   triangles.push_back(t);

   while (Queue.size()>0){
       e.p1=Queue.front().p1;
       e.p2=Queue.front().p2;

       for (int i = 0; i < pontos.size(); i++){
           if (pontos[i] == e.p1 || pontos[i] == e.p2) {
               continue;
           }

           double angle = fakeAngle(e.p1,pontos[i],e.p2);
           if (angle > maxAngle){
               p = pontos[i];
               maxAngle = angle;
           } else if (angle == maxAngle){
               if (pow(p.x(),2)+pow(p.y(),2) > (pow(pontos[i].x(),2)+pow(pontos[i].y(),2))){
                       p = pontos[i];
                       maxAngle = angle;
               }
           }
      }

      if (((e.p1.x()-p.x())*(e.p2.y()-p.y())-(e.p2.x()-p.x())*(e.p1.y()-p.y()))>0){
          e1.p1=e.p2;
          e1.p2=p;
          e2.p1=p;
          e2.p2=e.p1;
          e3.p1=e.p1;
          e3.p2=e.p2;
      } else {
          e1.p1=e.p1;
          e1.p2=p;
          e2.p1=p;
          e2.p2=e.p2;
          e3.p1=e.p2;
          e3.p2=e.p1;
      }
      t.e1=e1;
      t.e2=e2;
      t.e3=e3;

      Queue.push(e1);
      Queue.push(e2);

      triangles.push_back(t);

      Queue.pop();
   }


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

        for (int i=0;i<triangles.size();i++){
            glColor3f(0.7,(i/10.),1.0-(i/2.));
            glVertex3i(triangles[i].e1.p1.x(),triangles[i].e1.p1.y(),0.0);
            glVertex3i(triangles[i].e2.p1.x(),triangles[i].e2.p1.y(),0.0);
            glVertex3i(triangles[i].e3.p1.x(),triangles[i].e3.p1.y(),0.0);
        }

        glEnd();
    }

}

Delaunay::~Delaunay(){

}
