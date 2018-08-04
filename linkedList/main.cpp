#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T value;
    Node *next;
};

template <typename T>
struct LinkedList {
    Node<T> *firstNode;
    Node<T> *lastNode;
};

template <typename T>
LinkedList<T> inicializarLista (){
    LinkedList<T> list;
    list.firstNode = nullptr;
    list.lastNode = nullptr;
    return list;
}

template <typename T>
void adicionarItem (LinkedList<T> *list, T value) {
    Node<T> *aux = new Node<T>;
    aux->value = value;
    aux->next = nullptr;

    if (list->firstNode == nullptr){
        list->firstNode = aux;
        list->lastNode = aux;
    }
    else if (list->firstNode!=nullptr) {
        list->lastNode->next = aux;
        list->lastNode = aux;
    }
}

template <typename T>
void removerItem (LinkedList<T> *list, T value){

    if(list->firstNode==nullptr){
         return;
    }
    else if (list->firstNode->next==nullptr){
         if (list->firstNode->value==value)
            delete list->firstNode;
         return;
    }

    Node<T> *aux1;
    Node<T> *aux2;

    aux1 = list->firstNode;
    aux2 = list->firstNode->next;

    if (aux1->value==value){
         delete aux1;
         list->firstNode=aux2;
         return;
    }
    while (aux2->value!=value){
         aux1 = aux2;
         aux2 = aux2->next;
         if (aux1==nullptr)
             return;
    }
    aux1->next=aux2->next;
    delete aux2;
}

template <typename T>
void printarLista (LinkedList<T> *list){
    Node<T> *aux = new Node<T>;
    aux=list->firstNode;
    while(aux!=nullptr){
        cout << aux->value << " ";
        aux=aux->next;
    }
}

int main (){
    LinkedList<double> teste;
    teste = inicializarLista<double>();
    adicionarItem(&teste,1.1);
    adicionarItem(&teste,24.7);
    adicionarItem(&teste,17.6);
    adicionarItem(&teste,3.3);
    printarLista(&teste);
    cout << "\n";
    removerItem(&teste,1.1);
    printarLista(&teste);
}
