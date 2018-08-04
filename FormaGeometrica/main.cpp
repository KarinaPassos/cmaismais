#include <iostream>
#include "figura.h"
#include <vector>

int main()
{

    Figura *r = new Retangulo(20,7);
    r->descricao();
    Figura *c = new Circulo(2);
    c->descricao();
    Figura *p = new PoligonoRegular(2,3,2);
    p->descricao();

    return 0;
}
