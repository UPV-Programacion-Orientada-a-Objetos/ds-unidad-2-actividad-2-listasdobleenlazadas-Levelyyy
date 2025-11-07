/**
 * @file RotorDeMapeo.h
 * @brief Implementación del rotor de mapeo mediante lista circular
 * @author [Tu Nombre]
 * @date Noviembre 2025
 */

#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

/**
 * @class NodoRotor
 * @brief Nodo de la lista circular doblemente enlazada
 */
class NodoRotor {
public:
    char dato;              ///< Carácter almacenado
    NodoRotor* siguiente;   ///< Puntero al siguiente nodo
    NodoRotor* previo;      ///< Puntero al nodo anterior
    
    /**
     * @brief Constructor del nodo
     * @param d Carácter a almacenar
     */
    NodoRotor(char d);
};

/**
 * @class RotorDeMapeo
 * @brief Disco de cifrado César implementado como lista circular
 * 
 * Contiene el alfabeto A-Z en una lista circular doblemente enlazada.
 * La cabeza indica la posición cero actual. Permite rotar para cambiar
 * el mapeo de caracteres de forma dinámica.
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza;  ///< Posición actual (cero) del rotor
    int tamanio;        ///< Número de elementos en el rotor

public:
    /**
     * @brief Constructor que inicializa el rotor con A-Z
     * 
     * Crea una lista circular con el alfabeto completo,
     * con la cabeza apuntando inicialmente a 'A'.
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor que libera toda la memoria
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor n posiciones
     * @param n Posiciones a rotar (+ adelante, - atrás)
     * 
     * Mueve la cabeza circularmente modificando el mapeo.
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el carácter mapeado según rotación actual
     * @param entrada Carácter a mapear
     * @return Carácter mapeado según posición del rotor
     * 
     * Busca el carácter y devuelve su equivalente según
     * la rotación actual del disco.
     */
    char obtenerMapeo(char entrada);
};

#endif