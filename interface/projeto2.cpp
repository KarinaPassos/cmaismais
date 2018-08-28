#include "projeto2.h"
#include "projeto1.h"
#include "projeto2gl.h"
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>

projeto2::projeto2(QWidget *parent) :
    QWidget(parent)
    {

    GL = new projeto2gl();

    auto layoutVertical = new QBoxLayout(QBoxLayout::TopToBottom);

    auto botaoLimpar = new QPushButton("Limpar figura");
    auto botaoCorDentro = new QPushButton("Cor de dentro");
    auto botaoCorFora = new QPushButton("Cor de fora");

    layoutVertical->addWidget(botaoLimpar);
    layoutVertical->addWidget(botaoCorDentro);
    layoutVertical->addWidget(botaoCorFora);

    auto layoutHorizontal = new QBoxLayout(QBoxLayout::RightToLeft);
    setLayout(layoutHorizontal);

    layoutVertical->addStretch();

    //layoutVertical->setContentsMargins(0,0,0,750);
    botaoLimpar->setMaximumSize(150,25);
    botaoCorDentro->setMaximumSize(150,25);
    botaoCorFora->setMaximumSize(150,25);

    layoutHorizontal->addWidget(GL);
    layoutHorizontal->addLayout(layoutVertical);

    connect(botaoLimpar, &QPushButton::clicked, GL, &projeto2gl::limparTela);
    connect(botaoCorDentro, &QPushButton::clicked, this, &projeto2::escolherCorDentro);
    connect(botaoCorFora, &QPushButton::clicked, this, &projeto2::escolherCorFora);

};

void projeto2::escolherCorDentro(){
    auto corDentro = QColorDialog::getColor();
    GL->setCorDentro(corDentro);
}

void projeto2::escolherCorFora(){
    auto corFora = QColorDialog::getColor();
    GL->setCorFora(corFora);
}
