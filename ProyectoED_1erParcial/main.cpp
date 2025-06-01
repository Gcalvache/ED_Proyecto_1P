#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "Pila.hpp"
#include "Colas.hpp"
#include "Listas.hpp"
#include "Contacto.hpp"

using namespace std;

const int ANCHO = 120;
const int ALTO = 40;
const int ORIGEN_X = 275;
const int BASE_Y = 500;

// ANIMACIONES
struct NodoVisual {
    string texto;
    float x, y;
    sf::Color color;
    int id;
    NodoVisual* siguiente;
};

NodoVisual* pilaVisual = nullptr;

void animarInsercionPila(const string& texto, sf::RenderWindow& window, sf::Font& fuente) {
    // Crear nodo visual
    int r = 100 + rand() % 156, g = 100 + rand() % 156, b = 100 + rand() % 156;
    sf::Color color(r, g, b);
    static int idCounter = 1;

    NodoVisual* nuevo = new NodoVisual{texto, 0, 600, color, 0, pilaVisual};
    pilaVisual = nuevo;

    // Reasignar IDs descendentes
    int total = 0;
    for (NodoVisual* t = pilaVisual; t; t = t->siguiente) total++;
    for (NodoVisual* a = pilaVisual; a; a = a->siguiente) a->id = total--;

    int nivel = 0;
    for (NodoVisual* t = pilaVisual; t->siguiente; t = t->siguiente) nivel++;

    float destinoY = 100 + (total) * 70;

    while (nuevo->y > destinoY) {
        nuevo->y -= 10;
        window.clear(sf::Color::White);
        NodoVisual* actual = pilaVisual;
        int i = 0;
        while (actual) {
            float y = (actual == nuevo) ? actual->y : 100 + i * 70;
            sf::RectangleShape rect(sf::Vector2f(250, 60));
            rect.setPosition(ORIGEN_X, y);
            rect.setFillColor(actual->color);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);

            sf::Text textoNodo(actual->texto, fuente, 16);
            textoNodo.setFillColor(sf::Color::Black);
            textoNodo.setPosition(ORIGEN_X + 10, y + 15);
            window.draw(textoNodo);

            sf::CircleShape id(10);
            id.setFillColor(sf::Color::White);
            id.setPosition(ORIGEN_X + 225, y + 10);
            window.draw(id);

            sf::Text idText(to_string(actual->id), fuente, 12);
            idText.setFillColor(sf::Color::Black);
            idText.setPosition(id.getPosition().x + 3, id.getPosition().y);
            window.draw(idText);

            actual = actual->siguiente;
            i++;
        }
        window.display();
        this_thread::sleep_for(chrono::milliseconds(15));
    }
}

void animarEliminacionPila(sf::RenderWindow& window, sf::Font& fuente) {
    if (!pilaVisual) return;

    NodoVisual* eliminar = pilaVisual;

    for (float offset = 0; offset < 100; offset += 10) {
        window.clear(sf::Color::White);
        NodoVisual* actual = pilaVisual;
        int i = 0;
        while (actual) {
            float y = 100 + i * 70;
            if (actual == eliminar) y -= offset;

            sf::RectangleShape rect(sf::Vector2f(250, 60));
            rect.setPosition(ORIGEN_X, y);
            rect.setFillColor(actual->color);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);

            sf::Text texto(actual->texto, fuente, 16);
            texto.setFillColor(sf::Color::Black);
            texto.setPosition(ORIGEN_X + 10, y + 15);
            window.draw(texto);

            sf::CircleShape bolita(10);
            bolita.setFillColor(sf::Color::White);
            bolita.setPosition(ORIGEN_X + 225, y + 10);
            window.draw(bolita);

            sf::Text idText(to_string(actual->id), fuente, 12);
            idText.setFillColor(sf::Color::Black);
            idText.setPosition(bolita.getPosition().x + 3, bolita.getPosition().y);
            window.draw(idText);

            actual = actual->siguiente;
            i++;
        }
        window.display();
        this_thread::sleep_for(chrono::milliseconds(15));
    }

    pilaVisual = pilaVisual->siguiente;
    delete eliminar;

    int total = 0;
    for (NodoVisual* t = pilaVisual; t; t = t->siguiente) total++;
    for (NodoVisual* a = pilaVisual; a; a = a->siguiente) a->id = total--;
}

NodoVisual* colaVisual = nullptr;

void actualizarIndicesCola() {
    int id = 1;
    NodoVisual* actual = colaVisual;
    while (actual) {
        actual->id = id++;
        actual = actual->siguiente;
    }
}

void animarInsercionCola(const string& texto, sf::RenderWindow& window, sf::Font& fuente) {
    int r = 100 + rand() % 156;
    int g = 100 + rand() % 156;
    int b = 100 + rand() % 156;
    sf::Color color(r, g, b);
    static int contadorID = 1;

    NodoVisual* nuevo = new NodoVisual;
    nuevo->texto = texto;
    nuevo->color = color;
    nuevo->id = contadorID++;
    nuevo->siguiente = nullptr;

    int index = 0;
    if (!colaVisual) {
        colaVisual = nuevo;
    } else {
        NodoVisual* actual = colaVisual;
        while (actual->siguiente) {
            actual = actual->siguiente;
            index++;
        }
        actual->siguiente = nuevo;
        index++;
    }

    // Posición inicial (fuera a la izquierda)
    nuevo->x = 0;
    nuevo->y = BASE_Y;

    float destinoX = ORIGEN_X + index * (ANCHO + 20);

    while (nuevo->x < destinoX) {
        nuevo->x += 5;
        window.clear(sf::Color::White);

        NodoVisual* actual = colaVisual;
        int i = 0;
        while (actual) {
            float x = (actual == nuevo) ? actual->x : ORIGEN_X + i * (ANCHO + 20);

            sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
            rect.setPosition(x, BASE_Y);
            rect.setFillColor(actual->color);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);

            sf::Text texto(actual->texto, fuente, 16);
            texto.setFillColor(sf::Color::Black);
            texto.setPosition(x + 10, BASE_Y + 10);
            window.draw(texto);

            sf::CircleShape bolita(10);
            bolita.setFillColor(sf::Color::White);
            bolita.setPosition(x + ANCHO - 25, BASE_Y + 5);
            window.draw(bolita);

            sf::Text idText(to_string(actual->id), fuente, 12);
            idText.setFillColor(sf::Color::Black);
            idText.setPosition(bolita.getPosition().x + 3, bolita.getPosition().y);
            window.draw(idText);

            actual = actual->siguiente;
            i++;
        }

        window.display();
        this_thread::sleep_for(chrono::milliseconds(15));
    }
    nuevo->x = destinoX;

    actualizarIndicesCola();
}

void animarEliminacionCola(sf::RenderWindow& window, sf::Font& fuente) {
    if (!colaVisual) return;

    NodoVisual* eliminar = colaVisual;

    while (eliminar->x < 900) {
        eliminar->x += 10;
        window.clear(sf::Color::White);

        NodoVisual* actual = colaVisual;
        int i = 0;
        while (actual) {
            float x = (actual == eliminar) ? actual->x : ORIGEN_X + i * (ANCHO + 20);

            sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
            rect.setPosition(x, BASE_Y);
            rect.setFillColor(actual->color);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);

            sf::Text texto(actual->texto, fuente, 16);
            texto.setFillColor(sf::Color::Black);
            texto.setPosition(x + 10, BASE_Y + 10);
            window.draw(texto);

            sf::CircleShape bolita(10);
            bolita.setFillColor(sf::Color::White);
            bolita.setPosition(x + ANCHO - 25, BASE_Y + 5);
            window.draw(bolita);

            sf::Text idText(to_string(actual->id), fuente, 12);
            idText.setFillColor(sf::Color::Black);
            idText.setPosition(bolita.getPosition().x + 3, bolita.getPosition().y);
            window.draw(idText);

            actual = actual->siguiente;
            i++;
        }

        window.display();
        this_thread::sleep_for(chrono::milliseconds(15));
    }
        colaVisual = colaVisual->siguiente;
    delete eliminar;

    actualizarIndicesCola();
}

NodoVisual* listaVisual = nullptr;
void dibujarListaDoble(sf::RenderWindow& window, sf::Font& fuente, NodoVisual* cabeza);

void animarInsercionLista(const string& texto, sf::RenderWindow& window, sf::Font& fuente) {
    int r = 100 + rand() % 156;
    int g = 100 + rand() % 156;
    int b = 100 + rand() % 156;
    sf::Color color(r, g, b);
    static int contadorID = 1;

    NodoVisual* nuevo = new NodoVisual;
    nuevo->texto = texto;
    nuevo->x = ORIGEN_X + contadorID * (ANCHO + 20);  // dejarlo fuera del índice
    nuevo->y = 0;  // aparece desde arriba
    nuevo->color = color;
    nuevo->id = contadorID++;
    nuevo->siguiente = nullptr;

    if (!listaVisual) {
        listaVisual = nuevo;
    } else {
        NodoVisual* actual = listaVisual;
        while (actual->siguiente) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }

    // Deslizar el nuevo nodo hacia BASE_Y
    while (nuevo->y < BASE_Y) {
        nuevo->y += 5;
        window.clear(sf::Color::White);
        dibujarListaDoble(window, fuente, listaVisual);
        this_thread::sleep_for(chrono::milliseconds(15));
    }
}

void animarEliminacionLista(sf::RenderWindow& window, sf::Font& fuente) {
    if (!listaVisual) return;

    NodoVisual* actual = listaVisual;
    NodoVisual* anterior = nullptr;
    while (actual && actual->siguiente) {
        anterior = actual;
        actual = actual->siguiente;
    }

    for (float scale = 1.0f; scale >= 0.2f; scale -= 0.05f) {
        window.clear(sf::Color::White);
        dibujarListaDoble(window, fuente, listaVisual);
        this_thread::sleep_for(chrono::milliseconds(20));
    }

    if (!anterior) {
        delete listaVisual;
        listaVisual = nullptr;
    } else {
        delete anterior->siguiente;
        anterior->siguiente = nullptr;
    }

    dibujarListaDoble(window, fuente, listaVisual);
}


void dibujarPilaVisual(sf::RenderWindow& window, sf::Font& fuente) {
    window.clear(sf::Color::White);
    NodoVisual* actual = pilaVisual;
    int nivel = 0;

    while (actual) {
        float y = 100 + nivel * 70;

        sf::RectangleShape rect(sf::Vector2f(250, 60));
        rect.setPosition(ORIGEN_X, y);
        rect.setFillColor(actual->color);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Black);
        window.draw(rect);

        sf::Text texto(actual->texto, fuente, 16);
        texto.setFillColor(sf::Color::Black);
        texto.setPosition(ORIGEN_X + 10, y + 15);
        window.draw(texto);

        sf::CircleShape bolita(10);
        bolita.setFillColor(sf::Color::White);
        bolita.setPosition(ORIGEN_X + 225, y + 10);
        window.draw(bolita);

        sf::Text idText(to_string(actual->id), fuente, 12);
        idText.setFillColor(sf::Color::Black);
        idText.setPosition(bolita.getPosition().x + 3, bolita.getPosition().y);
        window.draw(idText);

        actual = actual->siguiente;
        nivel++;
    }

    window.display();
}
void dibujarColaVisual(sf::RenderWindow& window, sf::Font& fuente) {
    window.clear(sf::Color::White);
    NodoVisual* actual = colaVisual;
    int index = 0;

    while (actual) {
        float x = ORIGEN_X + index * (ANCHO + 20);

        sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
        rect.setPosition(x, BASE_Y);
        rect.setFillColor(actual->color);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Black);
        window.draw(rect);

        sf::Text texto(actual->texto, fuente, 16);
        texto.setFillColor(sf::Color::Black);
        texto.setPosition(x + 10, BASE_Y + 10);
        window.draw(texto);

        sf::CircleShape bolita(10);
        bolita.setFillColor(sf::Color::White);
        bolita.setPosition(x + ANCHO - 25, BASE_Y + 10);
        window.draw(bolita);

        sf::Text idText(to_string(actual->id), fuente, 12);
        idText.setFillColor(sf::Color::Black);
        idText.setPosition(bolita.getPosition().x + 3, bolita.getPosition().y);
        window.draw(idText);

        actual = actual->siguiente;
        index++;
    }

    window.display();
}

void dibujarListaDoble(sf::RenderWindow& window, sf::Font& fuente, NodoVisual* cabeza) {
    window.clear(sf::Color::White);
    NodoVisual* actual = cabeza;
    int index = 0;

    while (actual) {
        float x = ORIGEN_X + index * (ANCHO + 20);
        sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
        rect.setPosition(x, BASE_Y);
        rect.setFillColor(actual->color);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Black);
        window.draw(rect);

        sf::Text texto(actual->texto, fuente, 16);
        texto.setFillColor(sf::Color::Black);
        texto.setPosition(x + 10, BASE_Y + 10);
        window.draw(texto);

        sf::CircleShape bolita(10);
        bolita.setFillColor(sf::Color::White);
        bolita.setPosition(x + ANCHO - 25, BASE_Y + 5);
        window.draw(bolita);

        sf::Text idText(to_string(actual->id), fuente, 12);
        idText.setFillColor(sf::Color::Black);
        idText.setPosition(bolita.getPosition().x + 3, bolita.getPosition().y);
        window.draw(idText);

        actual = actual->siguiente;
        index++;
    }

    window.display();
}

void menuPila(sf::RenderWindow& window) {
    Pila<string> pila;
    int op;
    string dato;
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/consola.ttf");

    do {
        cout << "\n--- PILA ---\n";
        cout << "1. Insertar pagina\n2. Retirar pagina\n3. Ver pagina actual\n4. Mostrar historial\n0. Volver\nOpcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1:
                cout << "Ingrese nombre de pagina: ";
                getline(cin, dato);
                pila.insertarPagina(dato);
                animarInsercionPila(dato, window, font);
                break;
            case 2:
                if (!pila.estaVacia()) {
                    string eliminado = pila.verPaginaActual();
                    animarEliminacionPila(window, font);
                    pila.retirarPagina();
                }
                break;
            case 3:
                cout << "Pagina actual: " << pila.verPaginaActual() << "\n";
                break;
            case 4:
                pila.mostrarHistorial();
                break;
        }
        dibujarPilaVisual(window, font);
    } while (op != 0);
}

void menuCola(sf::RenderWindow& window) {
    Cola<string> cola;
    int op;
    string dato;
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/consola.ttf");

    do {
        cout << "\n--- COLA ---\n";
        cout << "1. Insertar\n2. Eliminar\n3. Mostrar\n0. Volver\nOpcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1:
                cout << "Ingrese dato: ";
                getline(cin, dato);
                cola.insertar(dato);
                animarInsercionCola(dato, window, font);
                break;
            case 2:
                if (cola.getFrente()) {
                    animarEliminacionCola(window, font);
                    cola.eliminar();
                }
                break;
            case 3:
                cola.mostrar();
                break;
        }
        dibujarColaVisual(window, font);
    } while (op != 0);
}

void menuLista(sf::RenderWindow& window) {
    ListaDoble<Contacto<string>> lista;
    int op;
    string nombre, telefono, correo;
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/consola.ttf");

    do {
        cout << "\n--- LISTA ---\n";
        cout << "1. Insertar\n2. Eliminar\n3. Mostrar adelante\n4. Mostrar atras\n5. Modificar\n0. Volver\nOpcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1:
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Teléfono: "; getline(cin, telefono);
                cout << "Correo: "; getline(cin, correo);
                lista.insertar(Contacto<string>(nombre, telefono, correo));
                animarInsercionLista(nombre, window, font);
                break;
            case 2:
                animarEliminacionLista(window, font);
                break;
            case 3:
                lista.mostrarAdelante();
                break;
            case 4:
                lista.mostrarAtras();
                break;
            case 5:
                cout << "Nombre del contacto a modificar: ";
                getline(cin, nombre);
                if (!lista.modificar(Contacto<string>(nombre, "", ""))) {
                    cout << "Contacto no encontrado.\n";
                }
                break;
        }
        dibujarListaDoble(window, font, listaVisual);
    } while (op != 0);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Visualizador de Estructuras", sf::Style::Close);
    int opcion;
    do {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Pila\n2. Cola\n3. Lista\n0. Salir\nOpcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1: menuPila(window); break;
            case 2: menuCola(window); break;
            case 3: menuLista(window); break;
        }
    } while (opcion != 0);

    window.close();
    return 0;
}
