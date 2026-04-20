#include "GestorSanciones.h"
#include "tipos.h"
#include <fstream>
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
                    std::fstream lectura1, lectura2;

                    std::string fi1 = "Utils/" + (std::string)radar.ficheropunto1;
                    std::string fi2 = "Utils/" + (std::string)radar.ficheropunto2;

                    lectura1.open(fi1,std::ios::binary | std::ios::in);
                    lectura2.open(fi2,std::ios::binary | std::ios::in);

                    if (lectura1.fail()) {
                        std::cout << "ERROR -- ERROR EN LAS LECTURAS DEL RADAR (1)" << std::endl;
                    }

                    if (lectura2.fail()) {
                        std::cout << "ERROR -- ERROR EN LAS LECTURAS DEL RADAR (2)" << std::endl;
                    }

                    std::cout << "***********************************************************" << std::endl;
                    std::cout << "Código:  " << radar.codigo << "\t\t" << "Provincia: " << radar.provincia << "\t" << "Localizacion: " << radar.localizacion << std::endl;
                    std::cout << "Nombre:  " << radar.nombre << "\t" << "Distancia (km): " << radar.distancia << "\t" << "Vel. Maxima (km/h): " << radar.velocidadMediaMaxima << std::endl;
                    std::cout << std::endl;
                    std::cout << "Fichero de Lecturas (1): " << radar.ficheropunto1 << std::endl;
                    std::cout << "Fichero de Lecturas (2): " << radar.ficheropunto2 << std::endl;

                    std::cout << std::endl;
                    std::cout << "----- CONTENIDO FICHERO LECTURAS -----" << std::endl;
                    std::cout << std::endl;

                    lecturavehiculo lec1{};
                    lecturavehiculo lec2{};

                    lectura1.read((char*)&lec1, sizeof(lec1));
                    lectura2.read((char*)&lec2, sizeof(lec2));
                    std::cout << "Fecha de las lecturas del fichero: " << lec1.lec.fecha.dia << "/" << lec1.lec.fecha.mes << "/" << lec1.lec.fecha.anio << std::endl << std::endl;
                    std::cout << "                        Lectura (1)     Lectura (2)" << std::endl;

                    while (!lectura1.eof() && !lectura2.eof()) {
                        std::cout << "Matricula:  " << lec1.matricula << "\t\t" << lec1.lec.hora.hora << ":" << lec1.lec.hora.min << ":" << lec1.lec.hora.sec << "\t\t\t" << lec2.lec.hora.hora << ":" << lec2.lec.hora.min << ":" << lec2.lec.hora.sec << std::endl;

                        lectura1.read((char*)&lec1, sizeof(lec1));
                        lectura2.read((char*)&lec2, sizeof(lec2));

                    }

                    lectura1.close();
                    lectura2.close();
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


    } else {
        std::cout << "ERROR -- NO EXISTE EL RADAR SOLICITADO" << std::endl;
        return false;
    }


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
    int anio;

    std::cout << " Por favor, introduzca el año a consultar: ";
    std::cin >> anio;

    // Colocamos al prinipio
    ficheroSanciones.clear();
    ficheroSanciones.seekg(0, std::ios::beg);

    sanciones sancion{};
    ficheroSanciones.read((char*)&sancion, sizeof(sancion));

    if (ficheroSanciones.eof()) {
        std::cout << std::endl;
        std::cout << " No hay sanciones registradas en el sistema." << std::endl;
        std::cout << std::endl;
        return;
    }

    int contador = 0;
    while (!ficheroSanciones.eof()) {

        // Solo mostramos las sanciones cuya fecha coincide con el año solicitado
        if (sancion.fh.fecha.anio == anio) {
            contador++;
            std::cout << std::endl;
            std::cout << " ***** SANCIÓN #" << contador << " *****" << std::endl;
            std::cout << "================================" << std::endl;
            std::cout << " - Matrícula:    " << sancion.matricula << std::endl;
            std::cout << " - Cód. Radar:   " << sancion.codRadar << std::endl;
            std::cout << " - Cuantía (€):  " << sancion.euros << std::endl;
            std::cout << " - Puntos:       " << sancion.puntos << std::endl;
            std::cout << " - Fecha/Hora:   " << sancion.fh.fecha.dia  << "/" << sancion.fh.fecha.mes  << "/" << sancion.fh.fecha.anio << "  " << sancion.fh.hora.hora  << ":" << sancion.fh.hora.min   << ":" << sancion.fh.hora.sec   << std::endl;
            std::cout << std::endl;
        }

        ficheroSanciones.read((char*)&sancion, sizeof(sancion));
    }

    if (contador == 0) {
        std::cout << std::endl;
        std::cout << " No hay sanciones registradas para el año " << anio << "." << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << " Total sanciones año " << anio << ": " << contador << std::endl;
        std::cout << std::endl;
    }
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

bool GestorSanciones::procesarRadar(int c) {

    // Buscamos si existe el rada
    std::fstream fichRadares;
    fichRadares.open(nomFicheroRadares, std::ios::binary | std::ios::in);

    if (fichRadares.fail()) {
        std::cout << "ERROR -- No hay radares registrados en el sistema" << std::endl;
        return false;
    }

    radartramo radar{};
    bool radarEncontrado = false;

    fichRadares.read((char*)&radar, sizeof(radar));
    while (!fichRadares.eof()) {
        if (radar.codigo == c) {
            radarEncontrado = true;
            break;
        }
        fichRadares.read((char*)&radar, sizeof(radar));
    }
    fichRadares.close();

    if (!radarEncontrado) {
        std::cout << "ERROR -- No se ha encontrado el radar con código " << c << std::endl;
        return false;
    }

    // Abrimos los ficheros de las lecturas
    std::fstream fLectura1, fLectura2;

    std::string ruta1 = "Utils/" + std::string(radar.ficheropunto1);
    std::string ruta2 = "Utils/" + std::string(radar.ficheropunto2);

    fLectura1.open(ruta1, std::ios::binary | std::ios::in);
    if (fLectura1.fail()) {
        std::cout << "ERROR -- No se puede abrir el fichero de lecturas (punto 1)" << std::endl;
        return false;
    }

    fLectura2.open(ruta2, std::ios::binary | std::ios::in);
    if (fLectura2.fail()) {
        std::cout << "ERROR -- No se puede abrir el fichero de lecturas (punto 2)" << std::endl;
        fLectura1.close();
        return false;
    }

    // Guardamos las lecturas
    int capacidad     = 2;
    int numLecturas2  = 0;
    lecturavehiculo* vectorSalida = new lecturavehiculo[capacidad];

    lecturavehiculo lecAux{};
    fLectura2.read((char*)&lecAux, sizeof(lecAux));
    while (!fLectura2.eof()) {
        // Ampliamos
        if (numLecturas2 == capacidad) {
            capacidad += 2;
            lecturavehiculo* vectorNuevo = new lecturavehiculo[capacidad];
            for (int i = 0; i < numLecturas2; i++) {
                vectorNuevo[i] = vectorSalida[i];
            }
            delete[] vectorSalida;
            vectorSalida = vectorNuevo;
        }
        vectorSalida[numLecturas2] = lecAux;
        numLecturas2++;
        fLectura2.read((char*)&lecAux, sizeof(lecAux));
    }
    fLectura2.close();

    // PRocesamos los vehículos
    lecturavehiculo lecEntrada{};
    fLectura1.read((char*)&lecEntrada, sizeof(lecEntrada));

    while (!fLectura1.eof()) {

        // Buscamos lectura
        int idxSalida = -1;
        for (int i = 0; i < numLecturas2; i++) {
            if (std::strcmp(vectorSalida[i].matricula, lecEntrada.matricula) == 0) {

                tlectura& lS = vectorSalida[i].lec;
                tlectura& lE = lecEntrada.lec;
                bool posterior = false;

                if (lS.fecha.anio > lE.fecha.anio) {
                    posterior = true;
                } else if (lS.fecha.anio == lE.fecha.anio) {
                    if (lS.fecha.mes > lE.fecha.mes) {
                        posterior = true;
                    } else if (lS.fecha.mes == lE.fecha.mes) {
                        if (lS.fecha.dia > lE.fecha.dia) {
                            posterior = true;
                        } else if (lS.fecha.dia == lE.fecha.dia) {
                            int segsE = lE.hora.hora * 3600 + lE.hora.min * 60 + lE.hora.sec;
                            int segsS = lS.hora.hora * 3600 + lS.hora.min * 60 + lS.hora.sec;
                            if (segsS > segsE) posterior = true;
                        }
                    }
                }

                if (posterior) {
                    idxSalida = i;
                    break;
                }
            }
        }

        // Vemos si hay infraccion
        bool infraccionVelocidad = false;
        int  franjaVelocidad     = -1;   // 0=leve  1=estándar  2=grave

        if (idxSalida != -1) {
            tlectura& lE = lecEntrada.lec;
            tlectura& lS = vectorSalida[idxSalida].lec;

            int segsE    = lE.hora.hora * 3600 + lE.hora.min * 60 + lE.hora.sec;
            int segsS    = lS.hora.hora * 3600 + lS.hora.min * 60 + lS.hora.sec;
            int tiempoSeg = segsS - segsE;

            if (tiempoSeg > 0) {
                float tiempoHoras  = tiempoSeg / 3600.0f;
                float velocidadMedia = radar.distancia / tiempoHoras;
                float vMax           = (float)radar.velocidadMediaMaxima;
                float exceso         = velocidadMedia - vMax;

                if (exceso > 0.0f) {
                    float porcentaje = (exceso / vMax) * 100.0f;
                    if      (porcentaje <= 10.0f) franjaVelocidad = 0;   // leve
                    else if (porcentaje <= 20.0f) franjaVelocidad = 1;   // estándar
                    else                          franjaVelocidad = 2;   // grave
                    infraccionVelocidad = true;
                }
            }
        }

        // Miramos si cumole ITV
        bool itvCaducada = false;
        std::fstream fichVehiculos;
        fichVehiculos.open(nomFicheroVehiculos, std::ios::binary | std::ios::in);

        if (!fichVehiculos.fail()) {
            coche vehiculo{};
            int pos = extraerMatricula(lecEntrada.matricula) % 1000;
            fichVehiculos.seekg(pos * (int)sizeof(coche), std::ios::beg);
            fichVehiculos.read((char*)&vehiculo, sizeof(vehiculo));

            if (!fichVehiculos.fail() && std::strcmp(vehiculo.matricula, lecEntrada.matricula) == 0) {
                int anioRef, mesRef, diaRef;
                if (idxSalida != -1) {
                    anioRef = vectorSalida[idxSalida].lec.fecha.anio;
                    mesRef  = vectorSalida[idxSalida].lec.fecha.mes;
                    diaRef  = vectorSalida[idxSalida].lec.fecha.dia;
                } else {
                    anioRef = lecEntrada.lec.fecha.anio;
                    mesRef  = lecEntrada.lec.fecha.mes;
                    diaRef  = lecEntrada.lec.fecha.dia;
                }

                //C omprobamos ITV
                if (vehiculo.fechaitv.anio < anioRef) {
                    itvCaducada = true;
                } else if (vehiculo.fechaitv.anio == anioRef) {
                    if (vehiculo.fechaitv.mes < mesRef) {
                        itvCaducada = true;
                    } else if (vehiculo.fechaitv.mes == mesRef && vehiculo.fechaitv.dia < diaRef) {
                        itvCaducada = true;
                    }
                }
            }
            fichVehiculos.close();
        }

        // Escribimos en el fichero la sancion
        if (infraccionVelocidad || itvCaducada) {

            int anioCaptura;
            if (idxSalida != -1) {
                anioCaptura = vectorSalida[idxSalida].lec.fecha.anio;
            } else {
                anioCaptura = lecEntrada.lec.fecha.anio;
            }

            std::fstream fichTipos;
            fichTipos.open(nomFicheroTipoSancion, std::ios::binary | std::ios::in);

            if (!fichTipos.fail()) {
                tipossanciones tipoSancion{};
                int posTipo = anioCaptura % 2000;
                fichTipos.seekg(posTipo * (int)sizeof(tipossanciones), std::ios::beg);
                fichTipos.read((char*)&tipoSancion, sizeof(tipoSancion));
                fichTipos.close();

                // Comprobamos el resgisto
                if (!fichTipos.fail() && tipoSancion.anio == anioCaptura) {

                    sanciones nuevaSancion{};
                    std::strcpy(nuevaSancion.matricula, lecEntrada.matricula);
                    nuevaSancion.codRadar = radar.codigo;
                    nuevaSancion.euros    = 0.0f;
                    nuevaSancion.puntos   = 0;

                    // Fecha de la multa
                    if (idxSalida != -1) {
                        nuevaSancion.fh = vectorSalida[idxSalida].lec;
                    } else {
                        nuevaSancion.fh = lecEntrada.lec;
                    }

                    if (infraccionVelocidad && franjaVelocidad >= 0) {
                        nuevaSancion.euros  += tipoSancion.eurosv[franjaVelocidad];
                        nuevaSancion.puntos += tipoSancion.puntosv[franjaVelocidad];
                    }
                    if (itvCaducada) {
                        // Guardamos la multa por la itv
                        nuevaSancion.puntos += tipoSancion.puntositv;
                    }

                    // Escribimos en el ficheor de sanciones si hace falta
                    ficheroSanciones.clear();
                    ficheroSanciones.seekp(0, std::ios::end);
                    ficheroSanciones.write((char*)&nuevaSancion, sizeof(nuevaSancion));
                    ficheroSanciones.flush();
                }
            }
        }

        fLectura1.read((char*)&lecEntrada, sizeof(lecEntrada));
    }

    fLectura1.close();
    delete[] vectorSalida;

    std::cout << std::endl;
    std::cout << " Radar " << c << " procesado correctamente." << std::endl;
    std::cout << std::endl;

    return true;
};