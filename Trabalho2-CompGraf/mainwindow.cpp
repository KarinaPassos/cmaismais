#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>

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

void MainWindow::location(QPointF pontoDeTeste){
    double a,b,xm;
    int contador;
    contador = 0;
    QPointF p1,p2;

    for (int i=1; i<pontosDoPoligono.size(); i++){


        //ver qual dos dois pontos tá na frente e qual tá atrás
        if (pontosDoPoligono[i].x() > pontosDoPoligono[i-1].x()){
            p1 = pontosDoPoligono[i-1];
            p2 = pontosDoPoligono[i];
        } else if (pontosDoPoligono[i].x() < pontosDoPoligono[i-1].x()){
            p1 = pontosDoPoligono[i];
            p2 = pontosDoPoligono[i-1];
        } else {
            return;
        }

        //calcular a reta que liga os dois pontos
        a = (p2.y() - p1.y())/(p2.x() - p1.x());
        b = p1.y() - a*p1.x();


        if (a == 0) //se a for zero, é pq é paralelo com a reta de teste, então é só ignorar
            continue;

        xm = (pontoDeTeste.y() - b)/a; //calcula o ponto de interseção da reta do poligono com a do ponto

        if (xm <= p2.x() && xm >= pontoDeTeste.x() && xm >= p1.x()){ //checa se o ponto de interseção tá no dominio da semirreta do poligono
            if (p1.y() == pontoDeTeste.y() || p2.y() == pontoDeTeste.y()){
                return;
            }
            contador++;
        }
    }

    if ((contador%2)==0) //verifica quantas interseções com o poligono tem pra poder classificar se tá fora ou dentro
        pontosFora.push_back(pontoDeTeste);
    if ((contador%2)==1)
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
            MainWindow::location(e->pos());
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
    glBegin(GL_LINE_STRIP);

    int i = 0;
    for (auto pt1 : pontosDoPoligono){
        glColor3f(0.7,(i/10.),1.0-(i/2.));
        glVertex3f(pt1.x(),pt1.y(),0.0);
        i+=1;
    }

    glEnd();

    glBegin(GL_POINTS);

    glColor3f(0.0,1.0,0.0);
    for (auto pt2 : pontosDentro){
        glVertex3f(pt2.x(),pt2.y(),0.0);
    }

    glColor3f(1.0,0.0,0.0);
    for (auto pt3 : pontosFora){
        glVertex3f(pt3.x(),pt3.y(),0.0);
    }

    glEnd();
}


MainWindow::~MainWindow()
{

}

