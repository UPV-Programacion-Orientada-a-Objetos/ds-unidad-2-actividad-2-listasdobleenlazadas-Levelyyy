/**
 * @file ListaDeCarga.h
 * @brief Implementación de lista doblemente enlazada para almacenar datos
 * @author [Tu Nombre]
 * @date Noviembre 2025
 */

#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

/**
 * @class NodoCarga
 * @brief Nodo de la lista doblemente enlazada
 */
class NodoCarga {
public:
    char dato;              ///< Carácter almacenado
    NodoCarga* siguiente;   ///< Puntero al siguiente nodo
    NodoCarga* previo;      ///< Puntero al nodo anterior
    
    /**
     * @brief Constructor del nodo
     * @param d Carácter a almacenar
     */
    NodoCarga(char d);
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada que almacena el mensaje decodificado
 * 
 * Mantiene el orden de los caracteres decodificados según van
 * llegando las tramas LOAD. Permite inserción al final e impresión.
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza;  ///< Primer nodo de la lista
    NodoCarga* cola;    ///< Último nodo de la lista
    int tamanio;        ///< Cantidad de elementos

public:
    /**
     * @brief Constructor que inicializa lista vacía
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor que libera toda la memoria
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato Carácter a insertar
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje con formato [X][Y][Z]
     */
    void imprimirMensaje();
    
    /**
     * @brief Imprime el mensaje final sin formato
     */
    void imprimirMensajeFinal();
};

#endif