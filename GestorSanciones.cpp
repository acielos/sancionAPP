#include "GestorSanciones.h"
#include "tipos.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

GestorSanciones::~GestorSanciones(){};

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
        ficheroSanciones.open(nFRadares, std::ios::out | std::ios::binary);
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

};

void GestorSanciones::getNomFicheroTipoSancion(cadena nF) {

};

void GestorSanciones::mostrarRadares() {

};

bool GestorSanciones::mostrarRadar(int c) {

};

bool GestorSanciones::mostrarLecturasRadar(int c) {

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
