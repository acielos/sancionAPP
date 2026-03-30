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
    std::fstream ficheroRadares;

    ficheroRadares.open(nomFicheroRadares,std::ios::binary | std::ios::in);

    // Comprobamos que no falle la apertura del fichero
    if (ficheroRadares.fail()) {
        std::cout << "ERROR --  No hay radares registrados en el sistema" << std::endl;
    } else {
        bool encontrado = false;
        // Buscamos el radar en el fichero
        radartramo radar{};
        ficheroRadares.read((char*)&radar, sizeof(radar));
        while (!ficheroRadares.eof()) {
            if (radar.codigo == c) {
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "     ***** RADARES *****" << std::endl;
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
                ficheroRadares.read((char*)&radar, sizeof(radar));
            }
        }

        if (ficheroRadares.eof()) {
            std::cout << std::endl;
            std::cout << " No se ha encontrado el radar solicitado" << std::endl;
        }
    }
    ficheroRadares.close();
    return false;
};

bool GestorSanciones::mostrarLecturasRadar(int c) {
    std::fstream ficheroRadares;



};

bool GestorSanciones::procesarRadar(int c) {

};

bool GestorSanciones::mostrarVehiculo(cadena m) {

};

bool GestorSanciones::anyadirVehiculo(coche v) {

};

bool GestorSanciones::mostrarTipoSancion(int a) {

};

void GestorSanciones::mostrarSanciones() {
};

void GestorSanciones::extraerMatricula(cadena m) {

};
