#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <limits>

MainWindow::MainWindow(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("trabalho 2");
    resize(600,300);
}

void MainWindow::resizeGL(int width, int height)
{
    //admito que peguei essa função resizeGL pronta pq eu tava tendo sérios problemas com conversão de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
}

std::pair<QPointF, QPointF> MainWindow::orderPoints(const QPointF& p1, const QPointF& p2) const
{
    return  p2.x() > p1.x() ?
        std::make_pair(p1, p2) : std::make_pair(p2, p1);
}

double MainWindow::intersectionY(const QPointF& p1, const QPointF& p2, const QPointF& pontoDeTeste) const
{
    //calcular a reta que liga os dois pontos
    const double a = (p2.y() - p1.y())/(p2.x() - p1.x());
    const double b = p1.y() - a*p1.x();

    //se a for zero, é pq é paralelo com a reta de teste, então é só ignorar
    // mas se a fosse 0.0000000001 de zero, tambem temos que ignorar.
    // a forma mais pratica de fazer isso eh chamar o qFuzzyIsNull que calcula
    // se 'a' esta muito proxima de zero.
    if (qFuzzyIsNull(a))
        // NaN significa 'not a number', eh a forma de representar infinidades, divisao por zero, etc.
        return std::numeric_limits<double>::quiet_NaN();

    return (pontoDeTeste.y() - b)/a; //calcula o ponto de interseção da reta do poligono com a do ponto
}

void MainWindow::checkLocation(const QPointF& pontoDeTeste){
    int contador = 0;
    for (size_t i=1; i < pontosDoPoligono.size(); i++){
        auto [p1, p2] = orderPoints(pontosDoPoligono[i-1], pontosDoPoligono[i]);
        double xm = intersectionY(p1, p2, pontoDeTeste);

        if (xm <= p2.x() && xm >= pontoDeTeste.x() && xm >= p1.x()){ //checa se o ponto de interseção tá no dominio da semirreta do poligono
            if (qFuzzyCompare(p1.y(),pontoDeTeste.y()) || qFuzzyCompare(p2.y(), pontoDeTeste.y())){ //ignora se bater com a quina pq esse caso tava dando muita dor de cabeça
                return;
            }
            contador++;
        }
    }

    //verifica quantas interseções com o poligono tem pra poder classificar se tá fora ou dentro
    if (contador % 2 == 0)
        pontosFora.push_back(pontoDeTeste);
    else
        pontosDentro.push_back(pontoDeTeste);
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    //botao esquerdo: adicionar pontosDoPoligono
    //botao esquerdo + ctrl: fechar o poligono
    //botao direito: adicionar pontos ver se ta dentro ou fora do poligono

    if(e->button() == Qt::LeftButton){
        if (e->modifiers() & Qt::ControlModifier){
            pontosDoPoligono.push_back(e->pos());
            pontosDoPoligono.push_back(pontosDoPoligono.front());
            update();
        } else {
            pontosDoPoligono.push_back(e->pos());
            update();
        }
    }

    else if (e->button() == Qt::RightButton) {
        if (pontosDoPoligono.back() == pontosDoPoligono.front()){
            checkLocation(e->pos());
            update();
        }
    }
}

void MainWindow::initializeGL() {
    initializeOpenGLFunctions();
    glLineWidth(7);
    glPointSize(7);
}

void MainWindow::paintGL(){
    int i = 0;

    glBegin(GL_LINE_STRIP);
    for (auto pt1 : pontosDoPoligono){
        glColor3d(0.7,(i/10.),1.0-(i/2.));
        glVertex3d(pt1.x(), pt1.y(),0.0);
        i+=1;
    }
    glEnd();

    glBegin(GL_POINTS);
        glColor3f(0.0,1.0,0.0);
        for (auto pt2 : pontosDentro){
            glVertex3d(pt2.x(),pt2.y(),0.0);
        }

        glColor3f(1.0,0.0,0.0);
        for (auto pt3 : pontosFora){
            glVertex3d(pt3.x(),pt3.y(),0.0);
        }
    glEnd();
}
