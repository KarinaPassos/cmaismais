#ifndef JARVIS_H
#define JARVIS_H
#include <QMouseEvent>
#include <unordered_set>
#include <QPoint>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <qmath.h>

namespace Ui {
class jarvis;
}

class jarvis : public QOpenGLWidget, public QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit jarvis(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *e) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height);
    void convexHull();
    double fakeAngle(QPointF origin, QPointF point);
private:
    std::unordered_set<QPointF> pontos;
    std::unordered_set<QPointF> linhas;
};

#endif // projeto1_H
