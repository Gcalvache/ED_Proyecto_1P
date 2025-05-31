#include <iostream>
#include "Menus/MenusGestion.h"

using namespace std;

int main() {
    int opcion;

    do {
        cout << "\n========= Menu Principal =========\n";
        cout << "1. Gestion de Pila\n";
        cout << "2. Gestion de Cola\n";
        cout << "3. Gestion de Lista\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                menuPila();
                break;
            case 2:
                menuCola();
                break;
            case 3:
                menuLista();
                break;
            case 4:
                cout << "Adios\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
