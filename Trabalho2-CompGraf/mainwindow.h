#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <vector>
#include <QPoint>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>

namespace Ui {
class MainWindow;
}

class MainWindow : public QOpenGLWidget, public QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *e) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height);
    void location(QPointF pontoDeTeste);
private:
    std::vector<QPointF> pontosDoPoligono;
    QPointF pontoDeTeste;
    std::vector<QPointF> pontosDentro;
    std::vector<QPointF> pontosFora;
};

#endif // MAINWINDOW_H

