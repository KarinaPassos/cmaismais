#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <vector>
#include <QPoint>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>

#include "vector2.h"
#include "triangle.h"

class MainWindow : public QOpenGLWidget, public QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height) override;

private:
    std::vector<Triangle> triangulos;
    std::vector<Vector2> pontos;
};

#endif // MAINWINDOW_H

