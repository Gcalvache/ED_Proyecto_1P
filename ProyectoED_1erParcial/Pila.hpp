#ifndef PILA_HPP
#define PILA_HPP

#include <iostream>

using namespace std;

template <typename T>
struct Pila {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
    };

    Nodo* cima;

public:
    Pila() : cima(nullptr) {}

    void insertarPagina(const string& dato) {
        Nodo* nuevo = new Nodo{dato, cima};
        cima = nuevo;
    }

    void retirarPagina() {
        if (cima != nullptr) {
            Nodo* temp = cima;
            cima = cima->siguiente;
            delete temp;
        } else {
            cout << "Stack Underflow (no hay más páginas)" << endl;
        }
    }

    string verPaginaActual() const {
        return (cima != nullptr) ? cima->dato : "Sin página";
    }

    bool estaVacia() {
        return cima == nullptr;
    }

    void mostrarHistorial() const {
        Nodo* actual = cima;
        while (actual) {
            cout << "\n--------------\n";
            cout << actual->dato;
            actual = actual->siguiente;
        }
    }

    int contarPaginas() {
        int contador = 0;
        Nodo* actual = cima;
        while (actual) {
            actual = actual->siguiente;
            contador++;
        }
        return contador;
    }

    ~Pila() {
        while (!estaVacia()) {
            retirarPagina();
        }
    }
};

#endif // PILA_HPP
