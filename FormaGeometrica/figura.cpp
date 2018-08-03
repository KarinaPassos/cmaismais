#include <iostream>
#include "figura.h"

void Retangulo::calcArea(){
    area=altura*base;
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

void PoligonoRegular::calcArea(){
    area=nLados*tamLado*alturaInterna/2;
}

PoligonoRegular::PoligonoRegular(double aI, double tL, int nL){
    alturaInterna = aI;
    tamLado = tL;
    nLados = nL;
    calcArea();
}
