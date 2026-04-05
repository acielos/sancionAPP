#include "GestorSanciones.h"
#include "tipos.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

GestorSanciones::~GestorSanciones() {
    if (getFicheroSancionesActivo()) {
        ficheroSanciones.close();
    }
};

GestorSanciones::GestorSanciones(cadena nFSanciones, cadena nFRadares, cadena nFVehiculos, cadena nFTipoSancion) {

    // Comprobamos si el de las sanciones existe, si no lo creamos
    ficheroSanciones.open(nFSanciones, std::ios::in | std::ios::out | std::ios::binary);

    // Si no está, lo creamos
    if (ficheroSanciones.fail()) {
        ficheroSanciones.close();
        ficheroSanciones.clear();
        ficheroSanciones.open(nFSanciones, std::ios::out | std::ios::binary);
        ficheroSanciones.close();
        ficheroSanciones.clear();
        ficheroSanciones.open(nFSanciones, std::ios::out | std::ios::in | std::ios::binary);
    }

    ficheroSancionesActivo = !ficheroSanciones.fail();

    std::strcpy(nomFicheroRadares, nFRadares);
    std::strcpy(nomFicheroVehiculos, nFVehiculos);
    std::strcpy(nomFicheroTipoSancion, nFTipoSancion);
};

bool GestorSanciones::getFicheroSancionesActivo() {
    return ficheroSancionesActivo;
};

void GestorSanciones::getNomFicheroVehiculos(cadena nF) {
    std::strcpy(nF, nomFicheroVehiculos);
};

void GestorSanciones::getNomFicheroTipoSancion(cadena nF) {
    std::strcpy(nF, nomFicheroTipoSancion);
};

void GestorSanciones::mostrarRadares() {

    // Abrimos el fichero en modo binario
    std::fstream ficheroRadares;

    ficheroRadares.open(nomFicheroRadares,std::ios::binary | std::ios::in);

    // Comprobamos que no falle la apertura del fichero
    if (ficheroRadares.fail()) {
        std::cout << "ERROR --  No hay radares registrados en el sistema" << std::endl;
    } else {
        radartramo radar{};
        ficheroRadares.read((char*)&radar, sizeof(radar));
        while (!ficheroRadares.eof()) {
            std::cout << "     ***** RADARES *****" << std::endl;
            std::cout << "=============================" << std::endl;
            std::cout << "   - Nombre: " << radar.nombre << std::endl;
            std::cout << "   - Código: " << radar.codigo << std::endl;
            std::cout << "   - Provincia: " << radar.provincia << std::endl;
            std::cout << "   - Localización: " << radar.localizacion << std::endl;
            std::cout << "   - Velocidad Máxima: " << radar.velocidadMediaMaxima << std::endl;
            ficheroRadares.read((char*)&radar, sizeof(radar));

            std::cout << std::endl;
            std::cout << std::endl;

        }
    }

    ficheroRadares.close();
};

bool GestorSanciones::mostrarRadar(int c) {
    // Abrimos el fichero en modo binario
    std::fstream mostrarRadar;

    mostrarRadar.open(nomFicheroRadares,std::ios::binary | std::ios::in);

    // Comprobamos que no falle la apertura del fichero
    if (mostrarRadar.fail()) {
        std::cout << "ERROR --  No hay radares registrados en el sistema" << std::endl;
        return false;
    } else {
        // Buscamos el radar en el fichero
        radartramo radar{};
        mostrarRadar.read((char*)&radar, sizeof(radar));
        while (!mostrarRadar.eof()) {
            if (radar.codigo == c) {
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "     ***** RADAR *****" << std::endl;
                std::cout << "=============================" << std::endl;
                std::cout << "   - Nombre: " << radar.nombre << std::endl;
                std::cout << "   - Código: " << radar.codigo << std::endl;
                std::cout << "   - Provincia: " << radar.provincia << std::endl;
                std::cout << "   - Localización: " << radar.localizacion << std::endl;
                std::cout << "   - Velocidad Máxima: " << radar.velocidadMediaMaxima << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                return true;
            } else {
                mostrarRadar.read((char*)&radar, sizeof(radar));
            }
        }

        if (mostrarRadar.eof()) {
            std::cout << std::endl;
            std::cout << " No se ha encontrado el radar solicitado" << std::endl;
        }
    }
    mostrarRadar.close();
    return false;
};

bool GestorSanciones::mostrarLecturasRadar(int c) {
    // Primero deberemos comprobar si nuestro radar existe
    if (comprobarRadar(c)) {
        
    }


};

bool GestorSanciones::procesarRadar(int c) {

};

bool GestorSanciones::mostrarVehiculo(cadena m) {
    // Creamos el flujo
    std::fstream mostrarVehiculo;

    // Abrimos el archivo en el que vamos a buscar
    mostrarVehiculo.open(nomFicheroVehiculos, std::ios::binary | std::ios::in);

    // Si falla, pues fuera
    if (mostrarVehiculo.fail()) {
        std::cout << "ERROR --  No hay vehículos registrados en el sistema" << std::endl;
        return false;
    } else {
        coche coche = {};
        // Calculamos la posición en la que debería estar el vehículo
        int pos = extraerMatricula(m) % 1000;

        mostrarVehiculo.seekg(pos * sizeof(coche), std::ios::beg);
        mostrarVehiculo.read((char*)&coche, sizeof(coche));

        if (std::strcmp(coche.matricula, m) != 0) {
            std::cout << "ERROR -- No se ha encontrado el vehiculo solicitado " << std::endl;
            mostrarVehiculo.close();
            return false;
        }

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "     ***** VEHÍCULO *****" << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << "   - Matrícula: " << coche.matricula << std::endl;
        std::cout << "   - Marca: " << coche.marca << std::endl;
        std::cout << "   - Modelo: " << coche.modelo << std::endl;
        // std::cout << "   - Fecha ITV: " << coche.fechaitv << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        mostrarVehiculo.close();
        return true;
    }
};

bool GestorSanciones::anyadirVehiculo(coche v) {
    // Creamos el objeto
    std::fstream annadirVehiculo;

    // Abrimos el fichero
    annadirVehiculo.open(nomFicheroVehiculos, std::ios::binary | std::ios::in | std::ios::out);

    // Comprobamos que se haya abierto correctamente
    if (annadirVehiculo.fail()) {
        std::cout << "ERROR --  No hay vehículos registrados en el sistema" << std::endl;
        return false;
    }

    // Comprobamos que el vehículo que queremos añadir no esté en el sistema
    if (mostrarVehiculo(v.matricula)) {
        std::cout << " ERROR -- Ya existe un vehículo en el sistema con la matrícula proporcionada" << std::endl;
        return false;
    }

    // Si el vehículo no existe y hemos hecho todo bien, lo metemos
    int pos = extraerMatricula(v.matricula) % 1000;

    annadirVehiculo.seekp(pos * sizeof(coche), std::ios::beg);
    annadirVehiculo.write((char*)&v, sizeof v);

    // Si todo va bien, cerradmos y terminamos
    annadirVehiculo.close();
    return true;
};

bool GestorSanciones::mostrarTipoSancion(int a) {
    // Creamos el flujo
    std::fstream tipoSancion;

    // Abrimos el archivo en el que vamos a buscar
    tipoSancion.open(nomFicheroTipoSancion, std::ios::binary | std::ios::in);

    // Si falla, pues fuera
    if (tipoSancion.fail()) {
        std::cout << "ERROR --  No hay sanciones registradas en el sistema (1)" << std::endl;
        return false;
    } else {
        tipossanciones sancion = {};
        // Calculamos la posición en la que debería estar el vehículo
        int posSan = a % 2000;

        tipoSancion.seekg(posSan * sizeof(sancion), std::ios::beg);
        tipoSancion.read((char*)&sancion, sizeof(sancion));

        if (tipoSancion.fail()) {
            std::cout << "ERROR --  No hay sanciones registradas en el sistema (2)" << std::endl;
            tipoSancion.close();
            return false;
        }

        if (sancion.anio != a) {
            std::cout << "ERROR -- No se ha encontrado la sancion solicitada (3)" << std::endl;
            tipoSancion.close();
            return false;
        }

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "     ***** SANCIÓN *****" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "   - Año: " << sancion.anio << std::endl;
        std::cout << "   - Euros: " << sancion.eurosv[0] << ", " << sancion.eurosv[1] << ", " << sancion.eurosv[2] << std::endl;
        std::cout << "   - Puntos velocidad: " << sancion.puntosv[0] << ", " << sancion.puntosv[1] << ", " << sancion.puntosv[2] << std::endl;
        std::cout << "   - Puntos ITV: " << sancion.puntositv << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        tipoSancion.close();
        return true;
    }
};

void GestorSanciones::mostrarSanciones() {
};

int GestorSanciones::extraerMatricula(cadena m) {
    cadena numerico;
    int contador = 0;

    for (int i = 0; i < 7; i++) {
        if (m[i] >= '0' && m[i] <= '9') {
            numerico[contador] = m[i];
            contador++;
        }
    }

    numerico[contador] = '\0';
    return atoi(numerico);
};

bool GestorSanciones::comprobarRadar(int codigo) {

    // creamos nuestro flujo
    std::fstream ficheroRadares;

    // Abrimos nuestro fichero de radares
    ficheroRadares.open(nomFicheroRadares, std::ios::binary | std::ios::in);

    // Comprobamos que no falle la apertura del archivo
    if (ficheroRadares.fail()) {
        std::cout << "\nERROR -- NO HAY RADARES REGISTRADOS EN EL SISTEMA" << std::endl;
        return false;
    } else {
        radartramo radar = {};
        ficheroRadares.read((char*)&radar, sizeof(radar));
        while (!ficheroRadares.eof()) {
            if (radar.codigo == codigo) {
                return true;
            } else {
                ficheroRadares.read((char*)&radar, sizeof(radar));
            }
        }
        return false;
    }
}
