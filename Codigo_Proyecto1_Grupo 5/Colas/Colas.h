#ifndef COLAS_HPP
#define COLAS_HPP
#include <iostream>

using namespace std;

template <typename T>
struct Nodo{
    T dato;
    Nodo<T>* siguiente;

    Nodo(T d, Nodo<T>* s =nullptr) : dato(d), siguiente(s) {}
};

struct ColaDinamica{
private:
    Nodo<T>* frente;
    Nodo<T>* cola;
public:
    ColaDinamica() : frente(nullptr), cola(nullptr){}

    ~ColaDinamica(){
        while (!estaVacia()){
            desencolar();
        }
    }
    bool estaVacia(){
        retun frente == nullptr;
    }

    void encolar(cont T& nuevaLetra){
        Nodo<T>* nuevo = new Nodo<T>(nuevaLetra, nullptr);

        if(estaVacia()){
            frente = nuevo;
            cola = nuevo;
        }else{
            cola->siguiente = nuevo;
            cola =nuevo;
        }
        cout<<"Vocal: " <<nuevaVocal.T <<" A sido agregado.\n";
    }

    void desencolar(){
        if(estaVacia()){
            cout<<"No hay Letras agregadas.\n";
            return;
        }
        Nodo<T>* temp = frente;
        cout<<"Letra revisada: "<<temp->dato.T<<".\n";
        frente = frente->siguiente;
        delete temp;

        if(frente==nullptr){
            cola = nullptr;
        }
    }

    void mostrarFrente(){
        if(estaVacia()){
            cout<<"No hay letras en cola.\n";
        }else{
            cout<<"Siguientes letras: "<<frente->dato.T<<".\n";
        }
    }

    void mostrarTodos(){
        if(estaVacia()){
            cout<<"No hay letras en la cola.\n";
            return;
        }
        cout<<"Letras en cola.\n";
        Nodo<T>* actual = frente;
        while(actual != nullptr){
            cout<<actual->dato.T<<".\n";
            actual = actual->siguiente;
        }
    }
};


#endif // COLAS_HPP
