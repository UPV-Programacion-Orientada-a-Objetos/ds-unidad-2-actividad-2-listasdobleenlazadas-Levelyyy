#include "RotorDeMapeo.h"

NodoRotor::NodoRotor(char d) : dato(d), siguiente(nullptr), previo(nullptr) {}

RotorDeMapeo::RotorDeMapeo() : cabeza(nullptr), tamanio(0) {
    for (char c = 'A'; c <= 'Z'; c++) {
        NodoRotor* nuevo = new NodoRotor(c);
        
        if (cabeza == nullptr) {
            cabeza = nuevo;
            cabeza->siguiente = cabeza;
            cabeza->previo = cabeza;
        } else {
            NodoRotor* ultimo = cabeza->previo;
            
            ultimo->siguiente = nuevo;
            nuevo->previo = ultimo;
            nuevo->siguiente = cabeza;
            cabeza->previo = nuevo;
        }
        tamanio++;
    }
}

RotorDeMapeo::~RotorDeMapeo() {
    if (cabeza == nullptr) return;
    
    NodoRotor* actual = cabeza;
    NodoRotor* siguiente;
    
    for (int i = 0; i < tamanio; i++) {
        siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void RotorDeMapeo::rotar(int n) {
    if (cabeza == nullptr || tamanio == 0) return;
    
    int rotaciones = n % tamanio;
    
    if (rotaciones > 0) {
        for (int i = 0; i < rotaciones; i++) {
            cabeza = cabeza->siguiente;
        }
    } else if (rotaciones < 0) {
        for (int i = 0; i > rotaciones; i--) {
            cabeza = cabeza->previo;
        }
    }
}

char RotorDeMapeo::obtenerMapeo(char entrada) {
    if (cabeza == nullptr) return entrada;
    
    if (entrada == ' ') return ' ';
    
    if (entrada < 'A' || entrada > 'Z') return entrada;
    
    NodoRotor* actual = cabeza;
    int posicionEntrada = -1;
    
    for (int i = 0; i < tamanio; i++) {
        if (actual->dato == entrada) {
            posicionEntrada = i;
            break;
        }
        actual = actual->siguiente;
    }
    
    if (posicionEntrada == -1) return entrada;
    
    actual = cabeza;
    for (int i = 0; i < posicionEntrada; i++) {
        actual = actual->siguiente;
    }
    
    return actual->dato;
}