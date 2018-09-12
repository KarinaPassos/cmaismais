#include "jarvis.h"
#include <vector>
#include <QDebug>

Jarvis::Jarvis(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("hi");
    resize(600,300);
}

void Jarvis::resizeGL(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
}

void Jarvis::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        pontos.push_back(e->pos());
    }
    else if (e->button() == Qt::RightButton) {
        convexHull();
    }
    update();
}

void Jarvis::initializeGL() {
    initializeOpenGLFunctions();
    glPointSize(7);
    glLineWidth(7);
}

void Jarvis::convexHull(){
    // organiza o vetor, x crescente.
    std::sort(pontos.begin(), pontos.end(),
    [](auto a, auto b){ return a.x() <= b.x(); });
    
    // limpa o vetor de linhas para adicionar o novo hull
    linhas.clear();
    
    // indices dos pontos, como organizei o vator com x crescente,
    // o ponto mais a esquerda eh de indice zero.
    int leftmost = 0;
    int currentpoint = 0;
    
    // algoritimo de jarvis.
    do
    {
        // adiciona o ponto atual no vetor de linhas.
        linhas.push_back(pontos[currentpoint]);
        
        // pega o proximo ponto. o calculo com % pontos.size() 
        // faz com que nao passe do ultimo elemento.
        int testpoint = (currentpoint + 1) % pontos.size();
        
        // testa o angulo dos pontos current, i, test. se 
        // o pongo tiver uma rotacao antioraria, muda o testPoint pra i,
        // continua o teste. isso vai pegar o ponto com maior rotacao antioraira
        // em relacao ao ponto atual.
        for (int i = 0; i < pontos.size(); i++)
        {
           if (rotacaoAntioraria(pontos[currentpoint], pontos[i], pontos[testpoint]))
               testpoint = i;
        }
        
        // seta o ponto atual com o ponto que achamos no for, pra 
        // adicionar no vetor de linhas na proxima execucao.
        currentpoint = testpoint;
    } while (currentpoint != leftmost);  // While we don't come to first point
}

void Jarvis::paintGL(){
    glBegin(GL_POINTS);

    glColor3f(0.0,1.0,0.0);
    for (auto ponto: pontos){
        glVertex3d(ponto.x(),ponto.y(),0.0);
    }

    glEnd();

    glBegin(GL_LINE_STRIP);

    glColor3f(1.0,0.0,0.5);
    for (auto linha: linhas){
        glVertex3d(linha.x(),linha.y(),0.0);
    }

    glEnd();
}
