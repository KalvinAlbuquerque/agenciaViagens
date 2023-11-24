#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 40

typedef struct Sitio
{
    char texto[TAM_MAX];
    struct Sitio *prox;
} Sitio;

typedef struct Pais
{
    char texto[TAM_MAX];
    struct Pais *prox;
    struct Sitio *prox;
    int turista1;
    int turista2;
} Pais;

void inserirPais(Pais**, char*);
void inserirSitio_turistico(Pais**, Sitio**, char*);

int main()
{
    Pais **inicio;
    int resposta;
    while(resposta != 1 || resposta != 2)
    {
        system("clear||cls");
        printf("Você já sabe onde quer visitar ou não tem certeza?\n");
        printf("[1] Já sei para onde quero viajar.\n[2] Não sei ainda para onde quero viajar.\n");
        scanf("%d", &resposta); 
    }

    switch (resposta)
    {
    case 1:
        
        break;
    case 2:

        break;
    default:
        printf("Resposta incorreta, digite novamente");
        break;
    }
}


void inserirPais(Pais **inicio, char *pais)
{
    Pais *novo = (Pais*)malloc(sizeof(Pais));

    if(!novo)
    {
        printf("Sem espaço para alocar memória!");
        exit(1);
    }

    novo->prox = NULL;
    strcpy(novo->texto, pais);

    if(*inicio == NULL)
    {
        *inicio = novo;
        return;
    }

    Pais *atual = *inicio;
    while(atual->prox != NULL)
    {
        atual = atual->prox;
    }

    atual->prox = novo;
}

void inserirSitio_turistico(Pais** atual, Sitio **inicio, char *sitio_turistico)
{

}