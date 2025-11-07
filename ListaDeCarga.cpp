#include "ListaDeCarga.h"
#include <iostream>

NodoCarga::NodoCarga(char d) : dato(d), siguiente(nullptr), previo(nullptr) {}

ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr), tamanio(0) {}

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        NodoCarga* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);
    
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }
    tamanio++;
}

void ListaDeCarga::imprimirMensaje() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "[" << actual->dato << "]";
        actual = actual->siguiente;
    }
}

void ListaDeCarga::imprimirMensajeFinal() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->dato;
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}