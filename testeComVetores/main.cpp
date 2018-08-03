#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct odio {
    std::string professor;
    long long int valor;
};

bool lessThanHate(odio a, odio b){
    return a.valor <= b.valor;
}



int main()
{
    auto myLittleVector = {1,58,12,58,67,101,12,6,3,67,1,101,-72626};

    //std::sort(myLittleVector.begin(), myLittleVector.end(), });
    //[](odio a, odio b){return a.valor >= b.valor;

    std::set<int> odioNaoDuplicado;

    for(auto x : myLittleVector)
        odioNaoDuplicado.insert(x);

    for (auto x : odioNaoDuplicado)
        std::cout << x << std::endl;


    return 0;
}
