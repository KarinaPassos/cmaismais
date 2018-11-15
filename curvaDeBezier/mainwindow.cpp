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
    p.set(320,118,94);
    pontos.push_back(p);
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
    double sumX = 0;
    double sumY = 0;
    Ponto aux;
    pontosNovos.push_back(pontos[0]);
    for (double j = 0; j<100; j++){
            for (int i = 0; i < pontos.size(); i++){
                sumX= sumX + pow((1-j/100),pontos.size()-i)*pow(j/100,i)*pontos[i].x*binomial_coefficient(pontos.size(), i);
                sumY= sumY + pow((1-j/100),pontos.size()-i)*pow(j/100,i)*pontos[i].y*binomial_coefficient(pontos.size(), i);
                std::cout << "i: " << i << " j: " << j << std::endl;
            }

            aux.set(sumX,sumY,0);
            pontosNovos.push_back(aux);
            sumX = sumY = 0;
        }
    pontosNovos.push_back(pontos[pontos.size()-1]);
    std::cout << pontosNovos.size() << " " << pontos.size() << std::endl;
}



MainWindow::~MainWindow()
{

}
