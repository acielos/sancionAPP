#ifndef SANCIONAPP_GESTORSANCIONES_H
#define SANCIONAPP_GESTORSANCIONES_H

#include <iosfwd>
#include <fstream>
#include "tipos.h"

class GestorSanciones {
    std::fstream ficheroSanciones;//flujo de acceso al fichero de sanciones.
    cadena nomFicheroRadares;//nombre del fichero de radares.
    cadena nomFicheroVehiculos;//nombre del fichero de vehículos.
    cadena nomFicheroTipoSancion;//nombre del fichero de cuantías de sanción por año.
    bool ficheroSancionesActivo;//estado del flujo; true indica que el fichero de sanciones
    //ha sido abierto con éxito en el flujo ficheroSanciones.
public:
    ~GestorSanciones();
    GestorSanciones(cadena nFSanciones, cadena nFRadares, cadena nFVehiculos, cadena
    nFTipoSancion);
    bool getFicheroSancionesActivo();
    void getNomFicheroVehiculos(cadena nF);
    void getNomFicheroTipoSancion(cadena nF);
    void mostrarRadares();
    bool mostrarRadar(int c);
    bool mostrarLecturasRadar(int c);
    bool procesarRadar(int c);
    bool mostrarVehiculo(cadena m);
    bool anyadirVehiculo(coche v);
    bool mostrarTipoSancion(int a);
    void mostrarSanciones();

    // Métodos propios
    void extraerMatricula(cadena m);
};




#endif //SANCIONAPP_GESTORSANCIONES_H
