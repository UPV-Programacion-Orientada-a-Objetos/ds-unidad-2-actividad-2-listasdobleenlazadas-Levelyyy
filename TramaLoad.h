/**
 * @file TramaLoad.h
 * @brief Implementación de tramas de carga de datos
 * @author [Tu Nombre]
 * @date Noviembre 2025
 */

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"

/**
 * @class TramaLoad
 * @brief Trama que contiene un fragmento de dato a decodificar
 * 
 * Representa una trama de tipo LOAD (L,X) que contiene un carácter
 * que debe ser decodificado usando el rotor de mapeo y almacenado
 * en la lista de carga.
 */
class TramaLoad : public TramaBase {
private:
    char caracter; ///< Carácter a decodificar

public:
    /**
     * @brief Constructor
     * @param c Carácter que contiene la trama
     */
    TramaLoad(char c);
    
    /**
     * @brief Procesa la trama decodificando el carácter
     * @param carga Lista donde se inserta el carácter decodificado
     * @param rotor Rotor usado para decodificar
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
    
    /**
     * @brief Obtiene el carácter almacenado
     * @return Carácter de la trama
     */
    char obtenerCaracter() const;
};

#endif