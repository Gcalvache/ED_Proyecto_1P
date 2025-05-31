#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdint>
#include "Pila.hpp"

using namespace std;

struct NodoVisual {
    string texto;
    float y;
    sf::Color color;
    int id; // identificador para mostrar en la bolita
    NodoVisual* siguiente;
};

NodoVisual* pilaVisual = nullptr;

const int ANCHO = 250;
const int ALTO = 60;
const int ORIGEN_X = 275;
const int BASE_Y = 500;

void dibujarPila(sf::RenderWindow& window, sf::Font& fuente) {
    NodoVisual* actual = pilaVisual;
    int index = 0;

    while (actual) {
        float posY = 100 + index * (ALTO + 10);

        sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
        rect.setPosition(ORIGEN_X, posY);
        rect.setFillColor(actual->color);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Black);
        window.draw(rect);

        // Texto dentro del nodo
        sf::Text texto;
        texto.setFont(fuente);
        texto.setString(actual->texto);
        texto.setCharacterSize(16);
        texto.setFillColor(sf::Color::Black);
        texto.setPosition(ORIGEN_X + 10, posY + 15);
        window.draw(texto);

        // Círculo decorativo
        sf::CircleShape decorador(10);
        decorador.setFillColor(sf::Color::White);
        decorador.setPosition(ORIGEN_X + ANCHO - 25, posY + 10);
        window.draw(decorador);

        // Número dentro del círculo
        sf::Text numero;
        numero.setFont(fuente);
        numero.setString(to_string(actual->id));
        numero.setCharacterSize(12);
        numero.setFillColor(sf::Color::Black);
        numero.setPosition(decorador.getPosition().x + 3, decorador.getPosition().y);
        window.draw(numero);

        actual = actual->siguiente;
        index++;
    }
}

void animarInsercion(const string& texto, sf::RenderWindow& window, sf::Font& fuente) {
    // Generar color fuerte aleatorio (evitar tonos claros)
    int r = 100 + rand() % 156;
    int g = 100 + rand() % 156;
    int b = 100 + rand() % 156;
    sf::Color color(r, g, b);
    static int contadorID = 1;
    // Crear nuevo nodo con id provisional
    NodoVisual* nuevo = new NodoVisual{texto, 0, color, 0, pilaVisual};
    // Reasignar los IDs en orden visual ascendente
    pilaVisual = nuevo;
    int total = 0;
    NodoVisual* tempContador = pilaVisual;
    while (tempContador) {
        total++;
        tempContador = tempContador->siguiente;
    }
    NodoVisual* actual = pilaVisual;
    int id = total;
    while (actual) {
        actual->id = id--;
        actual = actual->siguiente;
    }
    pilaVisual = nuevo;

    int nivel = 0;
    NodoVisual* temp = pilaVisual;
    while (temp->siguiente) {
        nivel++;
        temp = temp->siguiente;
    }
    float objetivoY = 100 + nivel * (ALTO + 10);

    for (float scale = 0.2f; scale <= 1.0f; scale += 0.05f) {
        window.clear(sf::Color::White);
        NodoVisual* actual = pilaVisual;
        int index = 0;
        while (actual) {
            float posY = 100 + index * (ALTO + 10);
            sf::RectangleShape rect(sf::Vector2f(ANCHO * scale, ALTO * scale));
            rect.setOrigin(ANCHO * scale / 2, ALTO * scale / 2);
            rect.setPosition(ORIGEN_X + ANCHO / 2, posY + ALTO / 2);
            rect.setFillColor(actual->color);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);

            sf::Text texto;
            texto.setFont(fuente);
            texto.setString(actual->texto);
            texto.setCharacterSize(16 * scale);
            texto.setFillColor(sf::Color::Black);
            texto.setPosition(rect.getPosition().x - rect.getSize().x / 2 + 10, rect.getPosition().y - 10);
            window.draw(texto);

            sf::CircleShape decorador(10 * scale);
            decorador.setFillColor(sf::Color::White);
            decorador.setPosition(rect.getPosition().x + rect.getSize().x / 2 - 25 * scale, rect.getPosition().y - 15 * scale);
            window.draw(decorador);

            sf::Text numero;
            numero.setFont(fuente);
            numero.setString(to_string(actual->id));
            numero.setCharacterSize(12 * scale);
            numero.setFillColor(sf::Color::Black);
            numero.setPosition(decorador.getPosition().x + 3, decorador.getPosition().y);
            window.draw(numero);

            actual = actual->siguiente;
            index++;
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void animarEliminacion(sf::RenderWindow& window, sf::Font& fuente) {
    if (!pilaVisual) return;

    NodoVisual* eliminar = pilaVisual;
    for (float scale = 1.0f; scale >= 0.2f; scale -= 0.05f) {
        window.clear(sf::Color::White);
        NodoVisual* actual = pilaVisual;
        int index = 0;
        while (actual) {
            float posY = 100 + index * (ALTO + 10);
            if (actual == eliminar) {
                sf::RectangleShape rect(sf::Vector2f(ANCHO * scale, ALTO * scale));
                rect.setOrigin(ANCHO * scale / 2, ALTO * scale / 2);
                rect.setPosition(ORIGEN_X + ANCHO / 2, posY + ALTO / 2);
                rect.setFillColor(actual->color);
                rect.setOutlineThickness(2);
                rect.setOutlineColor(sf::Color::Black);
                window.draw(rect);

                sf::Text texto;
                texto.setFont(fuente);
                texto.setString(actual->texto);
                texto.setCharacterSize(16 * scale);
                texto.setFillColor(sf::Color::Black);
                texto.setPosition(rect.getPosition().x - rect.getSize().x / 2 + 10, rect.getPosition().y - 10);
                window.draw(texto);

                sf::CircleShape decorador(10 * scale);
                decorador.setFillColor(sf::Color::White);
                decorador.setPosition(rect.getPosition().x + rect.getSize().x / 2 - 25 * scale, rect.getPosition().y - 15 * scale);
                window.draw(decorador);

                sf::Text numero;
                numero.setFont(fuente);
                numero.setString(to_string(actual->id));
                numero.setCharacterSize(12 * scale);
                numero.setFillColor(sf::Color::Black);
                numero.setPosition(decorador.getPosition().x + 3, decorador.getPosition().y);
                window.draw(numero);
            }
            actual = actual->siguiente;
            index++;
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    pilaVisual = pilaVisual->siguiente;
    delete eliminar;

    // Reasignar los IDs en orden visual ascendente
    int total = 0;
    NodoVisual* tempContador = pilaVisual;
    while (tempContador) {
        total++;
        tempContador = tempContador->siguiente;
    }
    NodoVisual* actual = pilaVisual;
    while (actual) {
        actual->id = total--;
        actual = actual->siguiente;
    }
}

void menu() {
    cout << "\n--- NAVEGADOR WEB ---\n";
    cout << "1. Visitar nueva página\n";
    cout << "2. Ir atrás\n";
    cout << "3. Ver página actual\n";
    cout << "4. Mostrar historial\n";
    cout << "5. Contar páginas\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Visualización de Pila con SFML");
    window.setFramerateLimit(60);

    sf::Font fuente;
    if (!fuente.loadFromFile("C:/Users/josed/OneDrive - UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE/Documentos/Proyectos C++/ProyectoEDP1/SFLMEj1/bin/Debug/arial.ttf")) {
        cout << "No se pudo cargar la fuente desde la ruta especificada.\n";
        return 1;
    }

    Pila<string> pilaLogica;
    int opcion;
    string pagina;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        menu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre de la página: ";
                getline(cin, pagina);
                pilaLogica.insertarPagina(pagina);
                animarInsercion(pagina, window, fuente);
                break;
            case 2:
                if (!pilaLogica.estaVacia()) {
                    pilaLogica.retirarPagina();
                    animarEliminacion(window, fuente);
                } else {
                    cout << "No hay páginas para regresar.\n";
                }
                break;
            case 3:
                cout << "Página actual: " << pilaLogica.verPaginaActual() << endl;
                break;
            case 4:
                pilaLogica.mostrarHistorial();
                break;
            case 5:
                cout << "Total de páginas: " << pilaLogica.contarPaginas() << endl;
                break;
            case 6:
                window.close();
                break;
            default:
                cout << "Opción inválida.\n";
        }

        window.clear(sf::Color::White);
        dibujarPila(window, fuente);
        window.display();
    }

    while (pilaVisual) {
        NodoVisual* temp = pilaVisual;
        pilaVisual = pilaVisual->siguiente;
        delete temp;
    }
    //
    return 0;
}
