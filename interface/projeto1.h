#ifndef projeto1_H
#define projeto1_H
#include <QMouseEvent>
#include <vector>
#include <QPoint>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>

namespace Ui {
class projeto1;
}

class projeto1 : public QOpenGLWidget, public QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit projeto1(QWidget *parent = 0);
    ~projeto1();
    void mousePressEvent(QMouseEvent *e) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height);
    void suavizar();
private:
    std::vector<QPointF> pontos;
};

#endif // projeto1_H
