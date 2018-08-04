#ifndef FIGURA_H
#define FIGURA_H
#define pi 3.14159265359

class Figura{
    public:
        virtual void descricao() = 0;
        double area; //deixei publico pq privado nao tava rodando :(
    private:
        virtual void calcArea() = 0;
};

class Retangulo:public Figura{
    public:
       Retangulo(double b, double a);
       void descricao() override;
    private:
       double altura, base;
       void calcArea() override;
};

class Circulo:public Figura{
    public:
       Circulo(double r);
       void descricao() override;
    private:
       double raio;
       void calcArea() override;
};

class PoligonoRegular:public Figura{
    public:
       PoligonoRegular(double aI, double tL, int nL);
       void descricao() override;
    private:
       int nLados;
       double tamLado;
       double alturaInterna;
       void calcArea() override;
};


#endif // FIGURA_H
