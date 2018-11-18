#ifndef GRAFOS_H_INCLUDED
#define GRAFOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#define CAMPUSMAX 1000
#define DISPOSITIVOSMAX 10000
#define INTMAX 2147483647

typedef struct
{
    int x;
    int y;
} COORDENADA;

typedef struct dispositivo
{
    struct dispositivo *adj;
    int num;
    int defeituoso;
    int distancia_adjacente;
} DISPOSITIVO;

typedef struct campus
{
    int num, numDispositivos;
    struct campus *prox;
    DISPOSITIVO *dispositivos;
} CAMPUS;

typedef struct matriz
{
    int num;
    COORDENADA coord;
    struct matriz *norte;
    struct matriz *sul;
    struct matriz *leste;
    struct matriz *oeste;
} MATRIZ;

typedef struct lde
{
    int num;
    struct lde *ant;
    struct lde *prox;
} LDE;

CAMPUS* CriaCampus(CAMPUS *campus, int numCampus, int numDispositivos);

DISPOSITIVO* CriaDispositivo(DISPOSITIVO *dispositivo, int num, int maxi);

DISPOSITIVO* EncontraDispositivo(DISPOSITIVO *disp, int num);

MATRIZ* CriaMatriz(MATRIZ *matriz, int tamanho, COORDENADA posicao);

MATRIZ* desce(MATRIZ * matriz, int y);

MATRIZ* AlocaMatriz(MATRIZ *matriz);

MATRIZ* Procura(MATRIZ *matriz, COORDENADA coord);

MATRIZ* Preenche(MATRIZ *matriz, int num);

MATRIZ* EstruturaMatriz(MATRIZ *matriz, int dispositivos);

void amarraLeste(MATRIZ *fonte, MATRIZ *leste);

void amarraSul(MATRIZ *fonte, MATRIZ *sul);

void printa(MATRIZ *matriz);

#endif // GRAFOS_H_INCLUDED
