#include "Grafos.h"

int main()
{
    int campi, dispositivos, aux, aux2 = 1;
    DISPOSITIVO *dispositivo, *auxDispositivo;
    CAMPUS *campus, *auxCampus;
    MATRIZ *matriz;

    campus = NULL;
    dispositivo = NULL;
    matriz = NULL;


    printf("Insira numero de Campi: ");
    //scanf("%d", &campi);
    campi = 1;

    aux = 1; //fazer um for depois aqui pra loopear pra fazer todos os campi

    printf("\nQuantos dispositivos tem no campus %d? ", aux);
    scanf("%d", &dispositivos);
    //dispositivos = 3;

    campus = CriaCampus(campus, aux, dispositivos);

    campus->dispositivos = CriaDispositivo(dispositivo, 1, dispositivos);
    auxDispositivo = campus->dispositivos; //debug

    while (auxDispositivo != NULL) //debug
    {
        printf("\n%d %d %d %d %d", auxDispositivo, auxDispositivo->adj, auxDispositivo->defeituoso, auxDispositivo->distancia_adjacente, auxDispositivo->num);
        auxDispositivo = auxDispositivo->adj;
        printf("\n");
    }

    matriz = EstruturaMatriz(matriz, dispositivos);
    matriz = Preenche(matriz, dispositivos);

    aux2 = 1;
    while (aux2)
    {
        printf("\nQuantos dispositivos sao limitados? ");
        scanf("%d", &aux);
        if (aux >= dispositivos)
            printf("\nErro: Limite de %d dispositivos limitados", dispositivos - 1);
        else
            aux2 = 0;
    }
    while (aux)
    {
        printf("Quais dispositivos sao limitados? %d restantes ", aux);
        scanf("%d", &aux2);
        auxDispositivo = EncontraDispositivo(campus->dispositivos, aux2);
        if (auxDispositivo == NULL)
            printf("\nDispositivo invalido, deve ser numero entre 1 e %d\n", dispositivos);
        else
        {
            auxDispositivo->defeituoso = 1;
            aux--;
        }
    }

    auxDispositivo = campus->dispositivos; //debug

    while (auxDispositivo != NULL) //debug
    {
        printf("\n%d %d %d %d %d", auxDispositivo, auxDispositivo->adj, auxDispositivo->defeituoso, auxDispositivo->distancia_adjacente, auxDispositivo->num);
        auxDispositivo = auxDispositivo->adj;
        printf("\n");
    }

    return 0;
}
