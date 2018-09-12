#pragma once

#include <QMouseEvent>
#include <QPoint>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <qmath.h>

class Jarvis : public QOpenGLWidget, public QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit Jarvis(QWidget *parent = nullptr);
    ~Jarvis() override = default;

    void mousePressEvent(QMouseEvent *e) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void convexHull();
    double fakeAngle(QPointF point1, QPointF point2,  QPointF point3);
private:
    std::vector<QPointF> pontos;
    std::vector<QPointF> linhas;
};
