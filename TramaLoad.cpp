#include "TramaLoad.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include <iostream>

TramaLoad::TramaLoad(char c) : caracter(c) {}

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    char decodificado = rotor->obtenerMapeo(caracter);
    carga->insertarAlFinal(decodificado);
    
    std::cout << "Trama recibida: [L," << caracter << "] -> Procesando... -> Fragmento '" 
              << caracter << "' decodificado como '" << decodificado << "'. Mensaje: ";
    carga->imprimirMensaje();
    std::cout << std::endl;
}

char TramaLoad::obtenerCaracter() const {
    return caracter;
}