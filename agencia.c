#include "agencia.h"

int main()
{   
    /* Função da biblioteca 'locale.h' para permitir uso de caracteres especiais */
    setlocale(LC_ALL, "pt_BR");

    /* Criando listas de turistas e paises */
    Pais * listaPaises = NULL;
    Turista * listaTurista = NULL;

    /* Teste para verificar a funcionalidade da função inserirPais, listarPaises*/
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

    int opcao;
    exibirMenu();
    scanf("%d", &opcao);
    getchar();
    do
    {
        switch(opcao)
        {
            case 1:
            {
                /* Solicitando o nome do cliente */
                char * nomeCliente = solicitarNomeDoCliente();

                /* Cadastrando o cliente */
                //cadastrarTurista(&listaTurista, nomeCliente, NULL);
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            case 0:
            {
                //TODO: Desalocar toda a memória antes de finalizar o programa
                break;
            }
            default:
            {
                printf("\nOpção Inválida");
                pause();
            }
        }

    }while(opcao != 0);
    
    /*while(resposta != 1 || resposta != 2)
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

void cadastrarTurista(Turista ** listaTurista, const char * nome, Pais paisDestino)
{
    /* Criando novo turista */
    Turista * novoTurista = (Turista*)malloc(sizeof(Turista));

    /* Verificando se há espaço na memória */
    if(novoTurista == NULL)
    {
        printf("Sem espaço para alocar memória!");

        exit(1);   
    }

    /* Setando informações do Turista */
    strcpy(novoTurista->nome, nome);
    novoTurista->ProximoTurista = NULL;
    
    /* Inserindo o novo cliente na lista de clientes cadastrados.
    * Caso a lista esteja vazia, o cliente se torna o primeiro elemento dela, caso contrário
    * a lista é iterada até o final, onde o novo cliente é inserido.
    */
    if(*listaTurista == NULL)
    {
        *listaTurista = novoTurista;

        return;
    }
    else
    {
        Turista * turistaAtual = *listaTurista;
        while(turistaAtual->ProximoTurista != NULL)
        {
            turistaAtual = turistaAtual->ProximoTurista;
        }

        turistaAtual->ProximoTurista = novoTurista;
    }
}

char * solicitarNomeDoCliente()
{
    char nomeCliente[TAM_MAX];

    /* Solicitando o input do nome do cliente 
    * Primeiro, o buffer é limpo antes da leitura, com a função 'fflush',
    * depois é solicitado que o usuário digite o nome desejado, 
    * por fim, é retirado o caractere '\n' através da função 'strcspn'.
    */
    fflush(stdin);
    printf("\nDigite o nome do cliente: ");
    fgets(nomeCliente, TAM_MAX, stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

    return nomeCliente; 
}

void exibirMenu()
{
    limparTela();
    exibirAviao();
    printf("\n\n");
    printf("********************************************\n");
    printf("*  Bem-vindo à Agência de Viagens!!!       *\n");
    printf("********************************************");
    printf("\n1.Cadastrar cliente");
    printf("\n2.Exibir clientes cadastrados");
    printf("\n3.Exibir países de destino");
    printf("\n0.Sair");
    printf("\n\nDigite sua opção: ");
}

void pause() 
{
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
    getchar();
}

void exibirAviao() 
{

    printf("                                                            \n");
    printf("                                                            \n");
    printf("                                                            \n");
    printf("                                                            \n");
    printf("                ########                                    \n");
    printf("                  ##    ##                                  \n");
    printf("                  ##      ##                                \n");
    printf("                    ##      ##                              \n");
    printf("                    ##        ##                            \n");
    printf("                      ##      ####                          \n");
    printf("        ##            ##        ####                        \n");
    printf("        ####          ##          ##                        \n");
    printf("        ##  ##          ##          ##                      \n");
    printf("        ##    ############            ################      \n");
    printf("        ##                                          ##--    \n");
    printf("        ##                                            ##    \n");
    printf("        ##                                          ##--    \n");
    printf("        ##    ############            ################      \n");
    printf("        ##  ##          ##          ##                      \n");
    printf("        ####          ##          ##                        \n");
    printf("        ##            ##        ##@@                        \n");
    printf("                    ::##      ####                          \n");
    printf("                    ##      ..##                            \n");
    printf("                    ##      ##                              \n");
    printf("                  ##      ##                                \n");
    printf("                  ##  ++##                                  \n");
    printf("                ########                                    \n");
    printf("                                                            \n");
    printf("                                                            \n");
    printf("                                                            \n"); 
}



void limparTela()
{
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear");
    #endif
}