#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("trabalho 5");
    resize(600,600);
}

void MainWindow::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton && e->modifiers() == Qt::KeyboardModifier::ControlModifier) {
        pontosNovos.clear();
    }
    if(e->button() == Qt::LeftButton){
        start();
        update();
    }
    else if (e->button() == Qt::RightButton) {
        bezier();
        update();
    }

}

void MainWindow::initializeGL() {
    initializeOpenGLFunctions();
    glPointSize(7);
}

void MainWindow::paintGL(){
    glBegin(GL_LINE_STRIP);

    int i = 0;
    for (auto ponto: pontos ){
        glVertex3f(ponto.x,ponto.y,0.0);
        glColor3f(0.7,(i/10.),1.0-(i/2.));
        i+=1;
    }

    glEnd();

    glBegin(GL_POINTS);

    i = 0;
    for (auto ponto: pontos ){
        glVertex3f(ponto.x,ponto.y,0.0);
        glColor3f(0.7,(i/10.),1.0-(i/2.));
        i+=1;
    }

    glEnd();

    glBegin(GL_LINE_STRIP);

    i = 0;
    for (auto ponto: pontosNovos){
        glVertex3f(ponto.x,ponto.y,0.0);
        glColor3f(0.0,1.0,0.0);
        i+=1;
    }

    glEnd();


}

void MainWindow::start(){
    if (pontos.size()>0)
        return;

    Ponto p;
    /*p.set(320,118,94);
    pontos.push_back(p);*/
    p.set(210,58,17);
    pontos.push_back(p);
    p.set(101,18,207);
    pontos.push_back(p);
    p.set(222,187,356);
    pontos.push_back(p);
    p.set(55,507,302);
    pontos.push_back(p);
    p.set(559,501,207);
    pontos.push_back(p);
}

int MainWindow::fatorial(int n)
{
    if (n == 1 || n == 0)
        return 1;
    else if (n < 0)
        return -1;
    else
        return n * fatorial(n - 1);
}

int MainWindow::binomial_coefficient(int n, int k){
    return fatorial(n)/(fatorial(k)*fatorial(n-k));
}



void MainWindow::bezier(){
    double sumX,sumY,sumZ;
    sumX = sumY = sumZ = 0;
    double c = 1000;
    Ponto aux;

    for (double j = 0; j<c; j++){
            for (int i = 0; i < pontos.size(); i++){
                sumX= sumX + pow((1.0-j/c),pontos.size()-(i+1))*pow(j/c,i)*pontos[i].x*binomial_coefficient(pontos.size()-1, i);
                sumY= sumY + pow((1.0-j/c),pontos.size()-(i+1))*pow(j/c,i)*pontos[i].y*binomial_coefficient(pontos.size()-1, i);
                sumZ= sumZ + pow((1.0-j/c),pontos.size()-(i+1))*pow(j/c,i)*pontos[i].z*binomial_coefficient(pontos.size()-1, i);
            }

            aux.set(sumX,sumY,sumZ);
            pontosNovos.push_back(aux);
            sumX = sumY = sumZ = 0;
        }

}



MainWindow::~MainWindow()
{

}
