#ifndef projeto2gl_H
#define projeto2gl_H
#include <QMouseEvent>
#include <vector>
#include <QPoint>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <QColorDialog>

namespace Ui {
class projeto2gl;
}

class projeto2gl : public QOpenGLWidget, public QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit projeto2gl(QWidget *parent = 0);
    ~projeto2gl();
    void mousePressEvent(QMouseEvent *e) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height);
    void location(QPointF pontoDeTeste);
    void limparTela();
    void setCorDentro(QColor c);
    void setCorFora(QColor c);

private:
    std::vector<QPointF> pontosDoPoligono;
    std::vector<QPointF> pontosDentro;
    std::vector<QPointF> pontosFora;
    QPointF pontoDeTeste;
    QColor corDentro;
    QColor corFora;
};

#endif // projeto2gl_H

