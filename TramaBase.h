/**
 * @file TramaBase.h
 * @brief Clase base abstracta para el protocolo PRT-7
 * @author [Tu Nombre]
 * @date Noviembre 2025
 */

#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Interfaz abstracta para todas las tramas del protocolo
 * 
 * Define el contrato que deben cumplir todas las tramas mediante
 * el método virtual puro procesar(). Utiliza polimorfismo para
 * permitir el procesamiento uniforme de diferentes tipos de tramas.
 */
class TramaBase {
public:
    /**
     * @brief Procesa la trama según su tipo específico
     * @param carga Puntero a la lista donde se almacenan datos decodificados
     * @param rotor Puntero al rotor que realiza el mapeo de caracteres
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
    
    /**
     * @brief Destructor virtual para correcta limpieza polimórfica
     */
    virtual ~TramaBase() {}
};

#endif