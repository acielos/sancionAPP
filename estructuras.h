#ifndef SANCIONAPP_ESTRUCTURAS_H
#define SANCIONAPP_ESTRUCTURAS_H

typedef char cadena[50];

struct radartramo {
    int codigo;
    cadena nombre;
    cadena provincia;
    cadena localizacion;
    float distancia;
    int velocidadMediaMaxima;
    cadena ficheropunto1;
    cadena ficheropunto2;
};

struct lecturavehiculo {
    cadena matricula;
    tlectura lec;
};

// Para la lectura de tiempo
struct tfecha{int dia; int mes; int anio;};
struct thora{int hora; int min; int sec;};
struct tlectura{tfecha fecha; thora hora;};

struct coche {
    cadena matricula;
    tfecha fechaitv;
    cadena marca;
    cadena modelo;
};

struct sanciones {
    cadena matricula;
    float euros;
    int puntos;
    int codRadar;
    tlectura fh;
};

struct tipossanciones {
    int anio;
    float eurosv[3];
    int puntosv[3];
    int puntositv;
};

#endif //SANCIONAPP_ESTRUCTURAS_H