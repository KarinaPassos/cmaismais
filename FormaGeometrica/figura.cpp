#include <iostream>
#include "figura.h"

void Retangulo::calcArea(){
    area=altura*base;
}

void Retangulo::descricao(){
    std::cout << "Retangulo com base " << base << " e altura " << altura << " tem area de " << area << std::endl;
}

Retangulo::Retangulo(double b, double a){
    base = b;
    altura = a;
    calcArea();
}

void Circulo::calcArea(){
    area=pi*raio*raio;
}

Circulo::Circulo(double r){
    raio = r;
    calcArea();
}

void Circulo::descricao(){
    std::cout << "Circulo com raio " << raio << " tem area de " << area << std::endl;
}

void PoligonoRegular::calcArea(){
    area=nLados*tamLado*alturaInterna/2;
}

PoligonoRegular::PoligonoRegular(double aI, double tL, int nL){
    alturaInterna = aI;
    tamLado = tL;
    nLados = nL;
    calcArea();
}

void PoligonoRegular::descricao(){
    std::cout << "Poligono regular com " << nLados << " lados, de altura interna " << alturaInterna << " e tamanho do lado " << tamLado << " tem area "
         << area << std::endl;
}
