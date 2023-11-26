#include "agencia.h"

int main()
{   
    /* Função da biblioteca 'locale.h' para permitir uso de caracteres especiais */
    setlocale(LC_ALL, "pt_BR");

/*     Pais **inicio;
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
    } */

    /* Teste para verificar a funcionalidade da função inserirPais, listarPaises*/
    Pais * listaPaises = NULL;
    inserirPais(&listaPaises, "Brasil");
    inserirPais(&listaPaises, "Japão");
    inserirPais(&listaPaises, "Rússia");
    inserirPais(&listaPaises, "México");
    listarPaises(&listaPaises);

    /* Testando a função localizarPais */
    Pais * russia = localizarPais(&listaPaises, "Rússia");
    Pais * brasil = localizarPais(&listaPaises, "Brasil");

    /* Testando a função inserirSítio e listarSítio */
    inserirNovoSitioTuristico(russia, "Museu Hermitage");
    inserirNovoSitioTuristico(russia, "Kremlin");
    inserirNovoSitioTuristico(russia, "Catedral de São Basilísco");
    listarSitiosTuristicos(russia);

    inserirNovoSitioTuristico(brasil, "Salvador");
    inserirNovoSitioTuristico(brasil, "Rio de Janeiro");
    inserirNovoSitioTuristico(brasil, "Lençóis");
    listarSitiosTuristicos(brasil);





}


void inserirPais(Pais ** listaPaises, const char * nomePais)
{
    /* Alocando espaço para novo país */
    Pais *novoPais = (Pais*)malloc(sizeof(Pais));

    /* Verificando se há espaço livre na memória */
    if(!novoPais)
    {
        printf("Sem espaço para alocar memória!");

        exit(1);
    }

    /* Setando informações do país */
    novoPais->proximoPais = NULL;
    novoPais->listaSitiosTuristico = NULL;
    strcpy(novoPais->nome, nomePais);

    /* Inserindo o novo país na lista.
    * O if abaixo verifica se a lista de países está vazia. Caso esteja, o novo país criado
    * se torna o primeiro elemento da lista. Caso contrário, a lista é iterada até  o fim,
    * para que o novo país possa ser inserido ao final da lista.
     */
    if(*listaPaises == NULL)
    {
        *listaPaises = novoPais;

        return;
    }
    else
    {
        Pais * atual = *listaPaises;
        while(atual->proximoPais != NULL)
        {
            atual = atual->proximoPais;
        }

        atual->proximoPais = novoPais;
    }
}

void listarPaises(Pais ** listaPaises)
{
    /* Verificando se a lista de países está vazia */
    if(*listarPaises == NULL)
    {
        printf("\nNão há nenhum país cadastrado!");

        return;
    }

    /* Printando os nomes de todos os países da lista */
    Pais * paisAtual = *listaPaises;
    while(paisAtual != NULL)
    {
        printf("\n%s", paisAtual->nome);
        paisAtual = paisAtual->proximoPais;
    }
}

Pais * localizarPais(Pais ** listaPaises, const char * nomePais)
{
    /* Verificando se a lista de países está vazia */
    if(*listaPaises == NULL)
    {
        printf("\nA lista de países está vazia!");

        return NULL;
    } 

    /* Iterando toda a lista de países e comparando os nomes dos países com o nome do país passado por parâmetro.
    * caso o país seja encontrado, ele é retornado. Caso contrário, é printado que o país não consta na lista.
    */
    Pais * paisAtual = *listaPaises;
    while(paisAtual != NULL)
    {
        if(strcmp(paisAtual->nome, nomePais) == 0)
        {
            break;
        }

        paisAtual = paisAtual->proximoPais;
    }

    /* Caso tenha chegado ao fim da lista, o país procurado não está cadastrado */
    if(paisAtual == NULL)
    {
        printf("\nO país não está na lista!");
    }

    return paisAtual;

}

void inserirNovoSitioTuristico(Pais * pais, const char * nomeSitioTuristico)
{
    /* Criando novo sítio turístico */
    SitioTuristico * novoSitioTuristico = (SitioTuristico*)malloc(sizeof(SitioTuristico));

    /* Verificando se há espaço livre na memória */
    if(!novoSitioTuristico)
    {
        printf("Sem espaço para alocar memória!");

        exit(1);
    }

    /* Setando informações do sitioTurístico */
    novoSitioTuristico->proximoSitioTuristico = NULL;
    strcpy(novoSitioTuristico->nome,nomeSitioTuristico); 

    /* Inserindo o sitio turístico na lista de sítios do país passado por parâmetro.
    * Caso a lista esteja vazia, o sítio se torna o primeiro elemento dela, caso contrário
    * a lista é iterada até o final, onde o novo sítio é inserido.
    */
    if(pais->listaSitiosTuristico == NULL)
    {
        pais->listaSitiosTuristico = novoSitioTuristico;
        return;
    }
    else
    {
        SitioTuristico * sitioAtual = pais->listaSitiosTuristico;
        while(sitioAtual->proximoSitioTuristico != NULL)
        {
            sitioAtual = sitioAtual->proximoSitioTuristico;
        }

        sitioAtual->proximoSitioTuristico = novoSitioTuristico;
    }
}

void listarSitiosTuristicos(Pais * pais)
{
    /* Verificando se o país é nulo ou se a lista de sítios turísticos está vazia */
    if(pais == NULL)
    {
        printf("\nO pais está nulo!");

        return;
    }
    else if(pais->listaSitiosTuristico == NULL)
    {
        printf("\nNão há nenhum sitio turístico cadastrado para o país %s", pais->nome);

        return;
    }
    
    /* Printando os nomes de todos os sítios turísticos do país */
    SitioTuristico * sitioTuristicoAtual = pais->listaSitiosTuristico;
    printf("\n\nSítios turísticos do(a) %s:", pais->nome);
    while(sitioTuristicoAtual != NULL)
    {
        printf("\n%s", sitioTuristicoAtual->nome);
        sitioTuristicoAtual = sitioTuristicoAtual->proximoSitioTuristico;
    }
}

void limparTela()
{
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear");
    #endif
}