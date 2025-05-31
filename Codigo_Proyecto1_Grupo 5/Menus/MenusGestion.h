#ifndef MENU_PILAS,_COLAS,_LISTAS_H_INCLUDED
#define MENU_PILAS,_COLAS,_LISTAS_H_INCLUDED
#include "../Pilas/Pila.hpp"
#include "../Listas/Listas.h"
//#include "../Colas/Colas.h"
#include <iostream>

using namespace std;

void menuPila() {
    Pila<string> pila;
    int opcion;
    string pagina;

    do {
        cout << "\n--- Menu Pila---\n";
        cout << "1. Insertar pagina\n";
        cout << "2. Retirar pagina\n";
        cout << "3. Ver pagina actual\n";
        cout << "4. Mostrar historial\n";
        cout << "5. Contar paginas\n";
        cout << "6. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre de la pagina: ";
                getline(cin, pagina);
                pila.insertarPagina(pagina);
                break;
            case 2:
                pila.retirarPagina();
                break;
            case 3:
                cout << "\nPagina actual: " << pila.verPaginaActual() << endl;
                break;
            case 4:
                cout<<"\n";
                pila.mostrarHistorial();
                cout<<"\n";
                break;
            case 5:
                cout << "Total de paginas: " << pila.contarPaginas() << endl;
                break;
            case 6:
                //implementar
                cout << "Volviendo al menu principal\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void menuLista() {
    ListaDinamica<string> lista;
    int opcion;
    string valor;

    do {
        cout << "\n--- Menu Lista Doblemente Enlazada ---\n";
        cout << "1. Insertar\n";
        cout << "2. Eliminar\n";
        cout << "3. Mostrar Adelante\n";
        cout << "4. Mostrar Atras\n";
        cout << "5. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese el valor a insertar: ";
                getline(cin, valor);
                lista.insertar(valor);
                break;
            case 2:
                cout << "Ingrese el valor a eliminar: ";
                getline(cin, valor);
                if (lista.eliminar(valor))
                    cout << "Elemento eliminado.\n";
                else
                    cout << "No se encontró el elemento.\n";
                break;
            case 3:
                cout<<"\n";
                lista.mostrarAdelante();
                break;
            case 4:
                cout<<"\n";
                lista.mostrarAtras();
                break;
            case 5:
                //implementar
                cout << "Volviendo al menu principal\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

//Pendiente Implementar
void menuCola() {
    cout << "\n--- Menu Cola ---\n";

}

#endif // MENU_PILAS,_COLAS,_LISTAS_H_INCLUDED
