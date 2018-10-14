#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <QMainWindow>
#include <QMouseEvent>
#include <vector>
#include <QPoint>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <queue>

struct Edge{
    QPointF p1,p2;
};

struct Triangle{
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
private:
    std::vector<QPointF> pontos;
    std::vector<QPointF> linhas;
    Edge e;
    std::vector<Triangle> triangles;
    std::vector<Edge> jarvis;

};

#endif // DELAUNAY_H
