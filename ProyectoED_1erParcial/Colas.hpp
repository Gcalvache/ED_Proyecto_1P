#ifndef COLAS_HPP
#define COLAS_HPP

#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Cola {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d, Nodo* s = nullptr) : dato(d), siguiente(s) {}
    };

    Nodo* frente;
    Nodo* final;

public:
    Cola() : frente(nullptr), final(nullptr) {}

    ~Cola() {
        while (!estaVacia()) {
            eliminar();
        }
    }

    bool estaVacia() const {
        return frente == nullptr;
    }

    void insertar(const T& dato) {
        Nodo* nuevo = new Nodo(dato);
        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        cout << "Elemento \"" << dato << "\" agregado a la cola.\n";
    }

    void eliminar() {
        if (estaVacia()) {
            cout << "La cola está vacía.\n";
            return;
        }
        Nodo* temp = frente;
        cout << "Elemento \"" << temp->dato << "\" eliminado de la cola.\n";
        frente = frente->siguiente;
        delete temp;
        if (!frente) final = nullptr;
    }

    void mostrar() const {
        if (estaVacia()) {
            cout << "La cola está vacía.\n";
            return;
        }
        Nodo* actual = frente;
        cout << "Elementos en la cola:\n";
        while (actual) {
            cout << actual->dato << "\n";
            actual = actual->siguiente;
        }
    }

    // Para acceso externo seguro (como visualización)
    Nodo* getFrente() const {
        return frente;
    }
};

#endif // COLAS_HPP
