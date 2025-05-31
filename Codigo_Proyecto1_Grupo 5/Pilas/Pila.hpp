#ifndef PILA_HPP
#define PILA_HPP

#include <iostream>

using namespace std;

/**
 * @brief Clase genérica para representar una pila (estructura LIFO).
 *
 * @tparam T Tipo de datos que almacena la pila.
 */
template <typename T>
class Pila {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
    };

    Nodo* cima;

public:
    Pila() : cima(nullptr) {}

    void insertarPagina(const T& dato) {
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

    T verPaginaActual() const {
        return (cima != nullptr) ? cima->dato : "Sin página";
    }

    bool estaVacia() const {
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

    int contarPaginas() const {
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
