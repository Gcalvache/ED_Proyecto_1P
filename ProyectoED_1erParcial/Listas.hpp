#ifndef LISTAS_HPP
#define LISTAS_HPP

#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct ListaDoble {
private:
    struct Nodo {
        T dato;
        Nodo* anterior;
        Nodo* siguiente;
        Nodo(const T& d) : dato(d), anterior(nullptr), siguiente(nullptr) {}
    };

    Nodo* cabeza;
    Nodo* cola;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr) {}

    ~ListaDoble() {
        Nodo* actual = cabeza;
        while (actual) {
            Nodo* siguiente = actual->siguiente;
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

    Nodo* buscar(const T& dato) const {
        Nodo* actual = cabeza;
        while (actual) {
            if (actual->dato == dato) return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    bool eliminar(const T& dato) {
    Nodo* actual = buscar(dato);
    if (!actual) {
        return false;
    }

    // Caso único nodo
    if (actual == cabeza && actual == cola) {
        cabeza = cola = nullptr;
    }
    // Caso cabeza
    else if (actual == cabeza) {
        cabeza = cabeza->siguiente;
        if (cabeza) cabeza->anterior = nullptr;
    }
    // Caso cola
    else if (actual == cola) {
        cola = cola->anterior;
        if (cola) cola->siguiente = nullptr;
    }
    // Caso intermedio
    else {
        if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
        if (actual->siguiente) actual->siguiente->anterior = actual->anterior;
    }

    delete actual;
    return true;
}
    void mostrarAdelante() const {
        Nodo* actual = cabeza;
        while (actual) {
            actual->dato.mostrar();
            cout << "--------------\n";
            actual = actual->siguiente;
        }
    }

    void mostrarAtras() const {
        Nodo* actual = cola;
        while (actual) {
            actual->dato.mostrar();
            cout << "--------------\n";
            actual = actual->anterior;
        }
    }
   bool modificar(const T& dato) {
    Nodo* aux = buscar(dato);
    if (!aux) return false;

    cout << "Nuevo Telefono: ";
    cin.ignore(); // limpiar buffer si hay un cin >> antes
    getline(cin, aux->dato.telefono);

    cout << "Nuevo Correo: ";
    getline(cin, aux->dato.correo);

    return true;
    }

    // Para uso en main
    Nodo* getCabeza() const { return cabeza; }
};

#endif // LISTAS_HPP
