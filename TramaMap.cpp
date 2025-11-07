#include "TramaMap.h"
#include "RotorDeMapeo.h"
#include <iostream>

TramaMap::TramaMap(int n) : rotacion(n) {}

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    rotor->rotar(rotacion);
    
    std::cout << std::endl << "Trama recibida: [M," << rotacion 
              << "] -> Procesando... -> ROTANDO ROTOR ";
    if (rotacion >= 0) {
        std::cout << "+";
    }
    std::cout << rotacion << "." << std::endl << std::endl;
}

int TramaMap::obtenerRotacion() const {
    return rotacion;
}