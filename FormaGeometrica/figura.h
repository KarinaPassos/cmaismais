#ifndef FIGURA_H
#define FIGURA_H
#define pi 3.14159265359

class Figura{
    public:
        double area;
    private:
        virtual void calcArea() = 0;
};

class Retangulo:public Figura{
    public:
       double altura, base;
       Retangulo(double b, double a);
    private:
       void calcArea() override;
};

class Circulo:public Figura{
    public:
       double raio;
       Circulo(double r);
    private:
       void calcArea() override;
};

class PoligonoRegular:public Figura{ //tem que ser public mesmo?
    public:
       int nLados;
       double tamLado;
       double alturaInterna;
       PoligonoRegular(double aI, double tL, int nL);
    private:
       void calcArea() override;
};


#endif // FIGURA_H
