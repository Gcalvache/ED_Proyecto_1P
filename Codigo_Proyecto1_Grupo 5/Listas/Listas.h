#ifndef LISTAS_HPP
#define LISTAS_HPP
#include <iostream>

using namespace std;


template <typename T>
struct ListaDinamica{
private:
    struct Nodo{
        T dato;
        Nodo* anterior;
        Nodo* siguiente;
        Nodo(const T& d) : dato(d), anterior(nullptr), siguiente(nullptr) {}
};
    Nodo* cabeza;
    Nodo* cola;
public:
    ListaDinamica() : cabeza(nullptr), cola(nullptr) {}

    ~ListaDinamica(){
        Nodo* actual = cabeza;
        while (actual){
            Nodo* siguiente = actual -> siguiente;
            delete actual;
            actual = siguiente;
        }
    }
void insertar (const T& dato){
    Nodo* nuevo = new Nodo(dato);
    if(!cabeza){
        cabeza=cola=nuevo;
        return;
    }
    Nodo* actual=cabeza;
    while(actual && actual->dato <dato){
        actual= actual ->siguiente;
    }
    if(actual==cabeza){
        nuevo->siguiente = cabeza;
        cabeza->anterior =nuevo;
        cabeza=nuevo;
    }else if(!actual){
        cola->siguiente =nuevo;
        nuevo->anterior =cola;
        cola=nuevo;
    }else{
        Nodo* anterior = actual->anterior;
        anterior->siguiente = nuevo;
        nuevo->anterior= anterior;
        nuevo->siguiente = actual;
        actual->anterior =nuevo;
    }
}

Nodo* buscar (const T& dato) const{
    Nodo* actual = cabeza;
    while(actual){
        if(actual->dato == dato){
            return actual;
        }
        actual=actual->siguiente;
    }
    return nullptr;
}

bool eliminar(const T& dato){
    Nodo* actual = buscar(dato);
    if(!actual){
        return false;
    }
    if(actual==cabeza && actual==cola){
        cabeza=cola=nullptr;
    }else if(actual==cabeza){
        cabeza=cabeza->siguiente;
        cabeza->anterior=nullptr;
    }else if(actual==cola){
        cola=cola->anterior;
        cola->siguiente=nullptr;
    }else{
        actual->anterior->siguiente = actual ->siguiente;
        actual->siguiente->anterior= actual-> anterior;
    }
    delete actual;
    return true;
}

void mostrarAdelante()const{
    Nodo* actual=cabeza;
    while(actual){
        cout<<actual->dato<<endl;
        cout<<"------------------------------------\n";
        actual=actual->siguiente;
    }
}

void mostrarAtras()const{
    Nodo* actual=cola;
    while(actual){
        cout<<actual->dato<<endl;
        cout<<"------------------------------------\n";
        actual=actual->anterior;
    }
}

bool modificar(const T& dato){

    Nodo* actual = cabeza;

    while(actual && actual->dato == dato){
        actual = actual ->siguiente;
    }

    if(!actual){
        return false;
    }

    string nuevaLetra;
    cout<<"Ingrese un nueva Letra: ";
    getline(cin, nuevaLetra);

    actual ->dato.T =nuevaLetra;
    return true;

}


};
#endif // LISTAS_HPP
