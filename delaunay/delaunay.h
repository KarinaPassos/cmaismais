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
        bool operator ==(Edge e) {
             if (e.p1 == p1 && e.p2 == p2)
                 return true;
             return false;
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
    bool find(Edge e);
private:
    std::vector<QPointF> pontos;
    std::vector<QPointF> linhas;
    Edge e;
    std::vector<Triangle> triangles;
    std::vector<Edge> jarvis;

};

#endif // DELAUNAY_H
