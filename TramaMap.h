/**
 * @file TramaMap.h
 * @brief Implementación de tramas de mapeo/rotación
 * @author [Tu Nombre]
 * @date Noviembre 2025
 */

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"

/**
 * @class TramaMap
 * @brief Trama que modifica el estado del rotor de mapeo
 * 
 * Representa una trama de tipo MAP (M,N) que rota el rotor
 * N posiciones, cambiando así el mapeo de caracteres para
 * las siguientes tramas LOAD.
 */
class TramaMap : public TramaBase {
private:
    int rotacion; ///< Cantidad de posiciones a rotar

public:
    /**
     * @brief Constructor
     * @param n Número de posiciones a rotar (positivo o negativo)
     */
    TramaMap(int n);
    
    /**
     * @brief Procesa la trama rotando el rotor
     * @param carga Lista de carga (no utilizada por MAP)
     * @param rotor Rotor que será rotado
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
    
    /**
     * @brief Obtiene el valor de rotación
     * @return Cantidad de posiciones a rotar
     */
    int obtenerRotacion() const;
};

#endif