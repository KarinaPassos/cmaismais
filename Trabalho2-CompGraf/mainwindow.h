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
    explicit MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height) override;

    // funcoes de geometria.

    /* orderPoints
     * Retorna um std::pair com o membro first sendo o maior ponto e second sendo o menor.
     */
    std::pair<QPointF, QPointF> orderPoints(const QPointF& p1, const QPointF& p2) const;

    /* retorna o ponto de intersessao de testPoint com a reta (p1, p2) ou NAN caso nao exista intersessao.
     */
    double intersectionY(const QPointF& p1, const QPointF& p2, const QPointF& testPoint) const;

    /* checa o ponto de teste em relacao a todas as retas do poligono.
     * e guarda em pontosDentro ou pontosFora */
    void checkLocation(const QPointF& pontoDeTeste);
private:
    std::vector<QPointF> pontosDoPoligono;
    std::vector<QPointF> pontosDentro;
    std::vector<QPointF> pontosFora;
};

#endif // MAINWINDOW_H

