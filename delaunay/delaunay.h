#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <QMainWindow>
#include <QMouseEvent>
#include <vector>
#include <QPoint>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <queue>

class Edge{
    public:
        QPointF p1,p2;
        int operator ==(Edge e) {
             if (e.p1 == p1 && e.p2 == p2)
                 return 1;
             else if (e.p1 == p2 && e.p2 == p1)
                 return -1;
             return 0;
        }
};

class Triangle{
    public:
        Edge e1,e2,e3;
};

namespace Ui {
class Delaunay;
}

class Delaunay : public QOpenGLWidget, public QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit Delaunay(QWidget *parent = 0);
    ~Delaunay();
    void mousePressEvent(QMouseEvent *e) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height);
    void triangulacao();
    void convexHull();
    double fakeAngle(QPointF currentPoint, QPointF loopPoint, QPointF testPoint);
    bool find(Edge e,std::vector<Triangle>& triangles);
    QPointF maxAnglePoint(QPointF point1, QPointF point2, QPointF point3);
    void setJarvis();
    QPointF findPoint(Edge e);
    bool orientation(QPointF point1, QPointF point2, QPointF point3);
    void setTriangle(QPointF point1, QPointF point2, QPointF point3);
private:
    std::vector<QPointF> pontos;
    std::vector<QPointF> linhas;
    std::vector<Triangle> triangles;
    std::vector<Edge> jarvis;
};

#endif // DELAUNAY_H
