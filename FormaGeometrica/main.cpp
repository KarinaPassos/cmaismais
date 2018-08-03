#include <iostream>
#include "figura.h"

using namespace std;

int main()
{

    Retangulo *r = new Retangulo(20,7);
    Circulo *c = new Circulo(2);
    PoligonoRegular *p = new PoligonoRegular(2,3,2);

    cout << "Retangulo com base " << r->base << " e altura " << r->altura << " tem area de " << r->area << endl;
    cout << "Circulo com raio " << c->raio << " tem area de " << c->area << endl;
    cout << "Poligono regular com " << p->nLados << " lados, altura interna " << p->alturaInterna << " e tamanho do lado " << p->tamLado << " tem area "
         << p->area << endl;

    return 0;
}
