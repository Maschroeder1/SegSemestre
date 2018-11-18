#include "Grafos.h"

//obj.: cria um campus identificavel pelo int numCampus com numDispositivos dispositivos
CAMPUS* CriaCampus(CAMPUS *campus, int numCampus, int numDispositivos)
{
    campus =(CAMPUS* ) malloc(sizeof(CAMPUS));
    campus->num = numCampus;
    campus->numDispositivos = numDispositivos;
    campus->dispositivos = NULL;
    campus->prox = NULL;
    return campus;
}

//obj.: cria (maxi - num) dispositivos numerados de num a maxi
DISPOSITIVO* CriaDispositivo(DISPOSITIVO *dispositivo, int num, int maxi)
{
    if(dispositivo == NULL)
    {
        dispositivo = (DISPOSITIVO* ) malloc(sizeof(DISPOSITIVO));

        dispositivo->defeituoso = 0;
        dispositivo->distancia_adjacente = -1;
        dispositivo->num = num;
        dispositivo->adj = NULL;

        if (num < maxi)
            dispositivo->adj = CriaDispositivo(dispositivo->adj, ++num, maxi);
    }
    return dispositivo;
}

DISPOSITIVO* EncontraDispositivo(DISPOSITIVO *disp, int num)
{
    if (disp != NULL)
    {
        if (disp->num != num)
            disp = EncontraDispositivo(disp->adj, num);
    }
    return disp;
}

//obj.: cria um nodo novo e coloca coordenadas nele
MATRIZ* CriaMatriz(MATRIZ *matriz, int tamanho, COORDENADA posicao)
{
    matriz = AlocaMatriz(matriz);

    matriz->coord.x = posicao.x;
    matriz->coord.y = posicao.y;

    return matriz;
}

//obj.: aloca um nodo novo da matriz com todos ponteiros apontando para NULL
MATRIZ* AlocaMatriz(MATRIZ *matriz)
{
    matriz = (MATRIZ* ) malloc(sizeof(MATRIZ));

    matriz->leste = NULL;
    matriz->oeste = NULL;
    matriz->norte = NULL;
    matriz->sul = NULL;

    return matriz;
}

//obj.: recebe uma matriz e cria uma nova linha, dando a ela a coordenada (1,y), onde y eh o numero passado como parametro
MATRIZ* desce(MATRIZ* matriz, int y)
{
    if (matriz->sul != NULL)
        matriz = desce(matriz->sul, y);
    else
    {
        matriz->sul = AlocaMatriz(matriz);
        matriz = matriz->sul;
        matriz->coord.x = 1;
        matriz->coord.y = y;
    }
    return matriz;
}

//obj.: amarra 2 nodos de uma matriz de maneira que a fonte seja o oeste do leste e o leste seja o leste da fonte
void amarraLeste(MATRIZ *fonte, MATRIZ *leste)
{
    fonte->leste = leste;
    leste->oeste = fonte;
}

//obj.: amarra 2 nodos de uma matriz de maneira que a fonte seja o norte do sul e o sul seja o sul da fonte
void amarraSul(MATRIZ *fonte, MATRIZ *sul)
{
    fonte->sul = sul;
    sul->norte = fonte;
}

//obj.: printa as coordenadas de uma linha de uma matriz
void printa(MATRIZ *matriz)
{
    if (matriz != NULL)
    {
        printf("\nPrinta: %d %d", matriz->coord.x, matriz->coord.y);
        printa(matriz->leste);
    }
}

//objetivo: recebe uma matriz e uma coordenada, e dai procura e retorna o nodo com as coordenadas, OU NULL caso as coordenadas nao pertencam a matriz
MATRIZ* Procura(MATRIZ *matriz, COORDENADA coord)
{
    if(matriz != NULL)
    {
        if(matriz->coord.x < coord.x)
            matriz = Procura(matriz->leste, coord);
        else
        {
            if (matriz->coord.x > coord.x)
                matriz = Procura(matriz->oeste, coord);
            else
            {
                if (matriz->coord.y < coord.y)
                    matriz = Procura(matriz->sul, coord);
                else
                {
                    if (matriz->coord.y > coord.y)
                        matriz = Procura(matriz->norte, coord);
                }
            }
        }
    }
    return matriz;
}

//obj.: preencher uma matriz
MATRIZ* Preenche(MATRIZ *matriz, int limite)
{
    int linhas, colunas, distancia, aux;
    COORDENADA coord;
    for (linhas = 1; linhas <= limite; linhas++)
    {
        for(colunas = linhas; colunas <= limite; colunas++)
        {
            if (colunas == linhas)
                matriz->num = 0;
            else
            {
                printf("\n\nQual a distancia entre os dispostivos %d e %d? ", linhas, colunas);
                scanf("%d", &distancia);
                coord.x = colunas;
                coord.y = linhas;
                matriz = Procura(matriz, coord);
                matriz->num = distancia;

                aux = coord.y;
                coord.y = coord.x;
                coord.x = aux;
                matriz = Procura(matriz, coord);
                matriz->num = distancia;
            }
        }
    }
    return matriz;
}

//obj.: recebe uma matriz NULL e um tamanho, e retorna uma matrix (tamanho)x(tamanho)
MATRIZ* EstruturaMatriz(MATRIZ *matriz, int tamanho)
{
    MATRIZ *auxMatriz, *coluna, *linha;
    COORDENADA posicao;
    int cont;

    matriz =  AlocaMatriz(matriz);
    matriz->coord.x = 1;
    matriz->coord.y = 1;
    auxMatriz = matriz;

    for(posicao.y = 1; posicao.y <= tamanho; posicao.y++)
    {
        for(posicao.x = 1; posicao.x <= tamanho; posicao.x++)
        {
            if(!(posicao.x == 1 ))
            {
                auxMatriz->leste = CriaMatriz(auxMatriz, tamanho, posicao);
                auxMatriz = auxMatriz->leste;
            }
        }
        cont = posicao.y + 1;
        if(posicao.y < tamanho)
            auxMatriz = desce(matriz, cont);
    }
    auxMatriz = matriz;
    linha = matriz;

    for(cont = 1; cont <= tamanho; cont++)
    {
        linha = linha->sul;
        auxMatriz = linha;
    }

    auxMatriz = matriz; //fonte
    coluna = matriz; //sul
    linha = matriz; //leste

    while(linha != NULL)
    {
        auxMatriz = linha;
        while(auxMatriz->leste != NULL)
        {
            coluna = auxMatriz->leste;
            amarraLeste(auxMatriz, coluna);
            auxMatriz = auxMatriz->leste;
        }
        auxMatriz = linha;
        coluna = auxMatriz->sul;
        while(auxMatriz != NULL && coluna != NULL)
        {
            amarraSul(auxMatriz, coluna);
            auxMatriz = auxMatriz->leste;
            coluna = coluna->leste;
        }
        linha = linha->sul;
    }
    return matriz;
}
