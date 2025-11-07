/**
 * @file main.cpp
 * @brief Programa principal del decodificador PRT-7
 * @author [Tu Nombre]
 * @date Noviembre 2025
 * 
 * Sistema que lee tramas del protocolo PRT-7 desde un puerto serial
 * (Arduino) y decodifica el mensaje oculto utilizando una lista de
 * carga y un rotor de mapeo tipo César.
 */


#include <iostream>
#include <cstring>
#include <cstdlib>
#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <unistd.h>
    #include <termios.h>
#endif

class PuertoSerial {
private:
#ifdef _WIN32
    HANDLE puerto;
#else
    int puerto;
#endif
    bool conectado;

public:
    PuertoSerial(const char* nombrePuerto);
    ~PuertoSerial();
    bool estaConectado();
    bool leerLinea(char* buffer, int tamanioMax);
};

#ifdef _WIN32
PuertoSerial::PuertoSerial(const char* nombrePuerto) : conectado(false) {
    puerto = CreateFileA(nombrePuerto, GENERIC_READ | GENERIC_WRITE, 0, nullptr,
                         OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    
    if (puerto == INVALID_HANDLE_VALUE) {
        return;
    }
    
    DCB parametros = {0};
    parametros.DCBlength = sizeof(parametros);
    
    if (!GetCommState(puerto, &parametros)) {
        CloseHandle(puerto);
        return;
    }
    
    parametros.BaudRate = CBR_9600;
    parametros.ByteSize = 8;
    parametros.StopBits = ONESTOPBIT;
    parametros.Parity = NOPARITY;
    
    if (!SetCommState(puerto, &parametros)) {
        CloseHandle(puerto);
        return;
    }
    
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    
    if (!SetCommTimeouts(puerto, &timeouts)) {
        CloseHandle(puerto);
        return;
    }
    
    conectado = true;
}

PuertoSerial::~PuertoSerial() {
    if (conectado) {
        CloseHandle(puerto);
    }
}

bool PuertoSerial::estaConectado() {
    return conectado;
}

bool PuertoSerial::leerLinea(char* buffer, int tamanioMax) {
    if (!conectado) return false;
    
    DWORD bytesLeidos;
    int indice = 0;
    char c;
    
    while (indice < tamanioMax - 1) {
        if (!ReadFile(puerto, &c, 1, &bytesLeidos, nullptr)) {
            return false;
        }
        
        if (bytesLeidos > 0) {
            if (c == '\n') {
                buffer[indice] = '\0';
                return true;
            } else if (c != '\r') {
                buffer[indice++] = c;
            }
        }
    }
    
    buffer[indice] = '\0';
    return false;
}

#else
PuertoSerial::PuertoSerial(const char* nombrePuerto) : conectado(false) {
    puerto = open(nombrePuerto, O_RDWR | O_NOCTTY);
    
    if (puerto < 0) {
        return;
    }
    
    struct termios opciones;
    tcgetattr(puerto, &opciones);
    
    cfsetispeed(&opciones, B9600);
    cfsetospeed(&opciones, B9600);
    
    opciones.c_cflag |= (CLOCAL | CREAD);
    opciones.c_cflag &= ~PARENB;
    opciones.c_cflag &= ~CSTOPB;
    opciones.c_cflag &= ~CSIZE;
    opciones.c_cflag |= CS8;
    
    opciones.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    opciones.c_iflag &= ~(IXON | IXOFF | IXANY);
    opciones.c_oflag &= ~OPOST;
    
    tcsetattr(puerto, TCSANOW, &opciones);
    
    conectado = true;
}

PuertoSerial::~PuertoSerial() {
    if (conectado) {
        close(puerto);
    }
}

bool PuertoSerial::estaConectado() {
    return conectado;
}

bool PuertoSerial::leerLinea(char* buffer, int tamanioMax) {
    if (!conectado) return false;
    
    int indice = 0;
    char c;
    
    while (indice < tamanioMax - 1) {
        int bytesLeidos = read(puerto, &c, 1);
        
        if (bytesLeidos > 0) {
            if (c == '\n') {
                buffer[indice] = '\0';
                return true;
            } else if (c != '\r') {
                buffer[indice++] = c;
            }
        }
    }
    
    buffer[indice] = '\0';
    return false;
}
#endif

void procesarTrama(char* linea, ListaDeCarga* carga, RotorDeMapeo* rotor) {
    if (linea == nullptr || linea[0] == '\0') return;
    
    char tipo = linea[0];
    
    if (linea[1] != ',') return;
    
    char* datos = linea + 2;
    
    TramaBase* trama = nullptr;
    
    if (tipo == 'L') {
        char caracter;
        if (datos[0] == 'S' && datos[1] == 'p' && datos[2] == 'a' && 
            datos[3] == 'c' && datos[4] == 'e') {
            caracter = ' ';
        } else {
            caracter = datos[0];
        }
        trama = new TramaLoad(caracter);
    } else if (tipo == 'M') {
        int valor = 0;
        int signo = 1;
        int i = 0;
        
        if (datos[0] == '-') {
            signo = -1;
            i = 1;
        } else if (datos[0] == '+') {
            i = 1;
        }
        
        while (datos[i] >= '0' && datos[i] <= '9') {
            valor = valor * 10 + (datos[i] - '0');
            i++;
        }
        
        valor *= signo;
        trama = new TramaMap(valor);
    }
    
    if (trama != nullptr) {
        trama->procesar(carga, rotor);
        delete trama;
    }
}

int main() {
    std::cout << "Iniciando Decodificador PRT-7. Conectando a puerto COM..." << std::endl;
    
#ifdef _WIN32
    const char* nombrePuerto = "\\\\.\\COM4";
#else
    const char* nombrePuerto = "/dev/ttyUSB0";
#endif
    
    PuertoSerial serial(nombrePuerto);
    
    if (!serial.estaConectado()) {
        std::cout << "Error: No se pudo conectar al puerto serial." << std::endl;
        std::cout << "Modo simulacion activado. Ingrese tramas manualmente (escriba 'FIN' para terminar):" << std::endl;
        
        ListaDeCarga* carga = new ListaDeCarga();
        RotorDeMapeo* rotor = new RotorDeMapeo();
        
        char buffer[256];
        
        while (true) {
            std::cout << "> ";
            std::cin.getline(buffer, 256);
            
            if (buffer[0] == 'F' && buffer[1] == 'I' && buffer[2] == 'N') {
                break;
            }
            
            procesarTrama(buffer, carga, rotor);
        }
        
        std::cout << std::endl << "---" << std::endl;
        std::cout << "Flujo de datos terminado." << std::endl;
        std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
        carga->imprimirMensajeFinal();
        std::cout << "---" << std::endl;
        std::cout << "Liberando memoria... Sistema apagado." << std::endl;
        
        delete carga;
        delete rotor;
        
        return 0;
    }
    
    std::cout << "Conexion establecida. Esperando tramas..." << std::endl << std::endl;
    
    ListaDeCarga* carga = new ListaDeCarga();
    RotorDeMapeo* rotor = new RotorDeMapeo();
    
    char buffer[256];
    
    while (serial.leerLinea(buffer, 256)) {
        procesarTrama(buffer, carga, rotor);
    }
    
    std::cout << std::endl << "---" << std::endl;
    std::cout << "Flujo de datos terminado." << std::endl;
    std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
    carga->imprimirMensajeFinal();
    std::cout << "---" << std::endl;
    std::cout << "Liberando memoria... Sistema apagado." << std::endl;
    
    delete carga;
    delete rotor;
    
    return 0;
}