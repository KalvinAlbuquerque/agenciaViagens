#include "agencia.h"

int main()
{   
    /* Função da biblioteca 'locale.h' para permitir uso de caracteres especiais */
    setlocale(LC_ALL, "pt_BR");

    /* Criando listas de turistas e paises */
    Pais * listaPaises = NULL;
    Turista * listaTuristas = NULL;

    /* Variáveis */

    char nomeCliente[TAM_MAX];
    int opcao;

    /* Criando árvore e inserindo perguntas */
    Arvore *raiz = NULL;

    carregarPerguntas(&raiz);

    carregarPaisesESitios(&listaPaises);
    

    /* Carregando os turistas do txt */
    popularTuristas(listaPaises, &listaTuristas, "turistas.txt");

    /* Menu principal  */
    do
    {
        limparTela();
        exibirMenu();
        scanf(" %d", &opcao);
        getchar();

        limparTela();

        switch(opcao)
        {
            case 1:
            {
                /* Solicitando o nome do cliente */
                solicitarNomeDoCliente(nomeCliente);
                int clienteExiste = verificarExistenciaCliente(listaTuristas, nomeCliente);

                limparTela();

                Pais *paisSelecionado = NULL;
                SitioTuristico *sitioSelecionado = NULL;
                int tipo = 0;

                /* Cadastrando o cliente */
                if (!clienteExiste)
                {
                    char respostaCliente;
                    /* Selecionando o país de destino e criando o cliente/turista */
                    printf("Bem vindo %s! Você já sabe para qual destino deseja viajar? (S/N)\n", nomeCliente);
                    scanf(" %c", &respostaCliente);
                    getchar();

                    limparTela();
                    printf("Certo %s, ", nomeCliente);

                    if (respostaCliente == 's' || respostaCliente == 'S')
                    {
                        tipo = 1;

                        paisSelecionado = selecionarPais(listaPaises, "Para qual país deseja viajar?");

                        limparTela();
                        
                        sitioSelecionado = selecionarSitioTuristico(paisSelecionado, "Qual dos sítios turísticos abaixo você tem interesse em visitar?\n");
                    }
                    else
                    {
                        Arvore * arvore = printPerguntas(raiz);

                        tipo = 2;
                        
                        char nomeSitio[TAM_MAX];
                        strcpy(nomeSitio, arvore->info);

                        paisSelecionado = localizarPaisPeloNomeDoSitio(listaPaises, nomeSitio);
                        sitioSelecionado = localizarSitioTuristico(paisSelecionado->listaSitiosTuristico, nomeSitio);
                    }
                    

                    limparTela();

                    /* Confirmando o cadastro do cliente */
                    int confirmacao = confirmarViagem(nomeCliente, paisSelecionado, sitioSelecionado);
                    
                    limparTela();

                    if (confirmacao)
                    {
                        /* Cadastrando cliente */
                        cadastrarTurista(&listaTuristas, nomeCliente, tipo, paisSelecionado, sitioSelecionado);
                        printf("Cadastramos você no nosso sistema %s para o país %s, na cidade de %s! Boa viagem!\n", nomeCliente, paisSelecionado->nome, sitioSelecionado->nome);
                        pause();
                    }
                    else
                    {
                        printf("Ok, você não foi cadastrado no sistema, até a próxima!\n");
                        pause();
                    }
                }
                else
                {
                    printf("\nCliente já cadastrado.");
                    pause();
                    break;
                }

                break;
            }
            case 2:
            {
                
                listarTuristas(listaTuristas);
                printf("\n");
                pause();

                break;
            }
            case 3:
            {
                printf("Lista dos países cadastrados:\n");
                listarPaises(listaPaises);
                printf("\n");
                pause();

                break;
            }
            case 4:
            {
                Pais *paisSelecionado = selecionarPais(listaPaises, "Deseja ver os sítios turísticos de qual país?");
                listarSitiosTuristicos(paisSelecionado);
                printf("\n");
                pause();

                break;
            }
            case 5:
            {
                Pais *paisSelecionado = selecionarPais(listaPaises, "Deseja ver o número de turistas por sítios turísticos de qual país?");
                listarTuristasPorSitiosTuristicos(paisSelecionado);
                printf("\n");
                pause();

                break;
            }
            case 6:
            {
                listarPaisesClientesDecididos(listaPaises);
                printf("\n");
                pause();
                break;
            }
            case 7:
            {
                listarPaisesSistemaAuxilio(listaPaises);
                printf("\n");
                pause();
                break;
            }
            case 8:
            {
                listarPaisesVisitados(listaPaises);
                printf("\n");
                pause();
                break;
            }
            case 9:
            {
                listarPaisesNaoVisitados(listaPaises);
                printf("\n");
                pause();
                break;
            }
            case 10:
            {
                listarPaisMaisVisitado(listaPaises);
                printf("\n");
                pause();
                break;
            }
            case 11:
            {
                listarSitioMaisVisitado(listaPaises);
                printf("\n");
                pause();
                break;
            }
            case 0:
            {
                salvarTuristas("turistas.txt", listaTuristas);
                freeAll(&listaTuristas, &listaPaises, raiz);
                exit(1);
            }
            default:
            {
                printf("\nOpção Inválida");
                pause();
            }
        }

    }while(opcao != 0);

}

int numeroVisitasDoPais(Pais * pais)
{
    if (pais == NULL)
    {
        return 0;
    }

    int result = 0;

    SitioTuristico * auxSitio = pais->listaSitiosTuristico;

    while(auxSitio != NULL)
    {
        result += auxSitio->countTurista1;
        result += auxSitio->countTurista2;

        auxSitio = auxSitio->proximoSitioTuristico;
    }

    return result;
}

int numeroVisitasDoPaisTipo1(Pais *pais)
{
    if (pais == NULL)
    {
        return 0;
    }

    int result = 0;

    SitioTuristico * auxSitio = pais->listaSitiosTuristico;

    while(auxSitio != NULL)
    {
        result += auxSitio->countTurista1;

        auxSitio = auxSitio->proximoSitioTuristico;
    }

    return result;
}

int numeroVisitasDoPaisTipo2(Pais *pais)
{
    if (pais == NULL)
    {
        return 0;
    }

    int result = 0;

    SitioTuristico * auxSitio = pais->listaSitiosTuristico;

    while(auxSitio != NULL)
    {
        result += auxSitio->countTurista2;

        auxSitio = auxSitio->proximoSitioTuristico;
    }

    return result;
}

int verificarSePaisFoiVisitado(Pais *pais)
{
    SitioTuristico * auxSitio = pais->listaSitiosTuristico;

    while (auxSitio != NULL)
    {
        if (auxSitio->countTurista1 > 0 || auxSitio->countTurista2 > 0)
        {
            return 1;
        }

        auxSitio = auxSitio->proximoSitioTuristico;
    }

    return 0;
}

int confirmarViagem(char *nome, Pais *pais, SitioTuristico *sitioTuristico)
{

    while (1)
    {
        char confirmacao;

        printf("Então %s, você deseja viajar para a(o) %s e visitar o sítio turístico %s? (S/N)\nConfirme: ", nome, pais->nome, sitioTuristico->nome);
        scanf(" %c", &confirmacao);

        if (confirmacao == 'S' || confirmacao == 's') 
        {
            return 1; 
        } 
        else if (confirmacao == 'N' || confirmacao == 'n')
        {
            return 0; 
        }
        else
        {
            printf("Resposta inválida, digite novamente.\n");
            pause();
        }

        limparTela();
    }
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

void listarPaises(Pais * listaPaises)
{
    /* Verificando se a lista de países está vazia */
    if(*listarPaises == NULL)
    {
        printf("\nNão há nenhum país cadastrado.");

        return;
    }

    /* Printando os nomes de todos os países da lista */
    Pais * paisAtual = listaPaises;
    int contador = 0;
    while(paisAtual != NULL)
    {
        contador++;
        printf("\n%d. %s", contador, paisAtual->nome);
        paisAtual = paisAtual->proximoPais;
    }
}

Pais * localizarPais(Pais * listaPaises, const char * nomePais)
{
    /* Verificando se a lista de países está vazia */
    if(listaPaises == NULL)
    {
        printf("\nA lista de países está vazia!");

        return NULL;
    } 

    /* Iterando toda a lista de países e comparando os nomes dos países com o nome do país passado por parâmetro.
    * caso o país seja encontrado, ele é retornado. Caso contrário, é printado que o país não consta na lista.
    */
    Pais * paisAtual = listaPaises;
    while(paisAtual != NULL)
    {
        if(strcmp(paisAtual->nome, nomePais) == 0)
        {
            break;
        }

        paisAtual = paisAtual->proximoPais;
    }

    /* Caso tenha chegado ao fim da lista, o país procurado não está cadastrado */

    return paisAtual;

}

SitioTuristico * localizarSitioTuristico(SitioTuristico * listaSitioTuristico, const char * nomeSitio)
{
    /* Verificando se a lista de sítios está vazia */
    if(listaSitioTuristico == NULL)
    {
        printf("\nA lista de países está vazia!");

        return NULL;
    } 

    /* Iterando toda a lista de sítios e comparando os nomes dos sítios com o nome do sítio passado por parâmetro.
    * caso o sítio seja encontrado, ele é retornado. Caso contrário, é printado que o sítio não consta na lista.
    */
    SitioTuristico * sitioAtual = listaSitioTuristico;
    while(sitioAtual != NULL)
    {
        if(strcmp(sitioAtual->nome, nomeSitio) == 0)
        {
            break;
        }

        sitioAtual = sitioAtual->proximoSitioTuristico;
    }

    /* Caso tenha chegado ao fim da lista, o sítio procurado não está cadastrado */

    return sitioAtual;

}

Pais * selecionarPais(Pais *listaPaises, char* textoInicial)
{
    char nomePais[TAM_MAX];

    while(1)
    {
        printf("%s\n", textoInicial);
        listarPaises(listaPaises);
        fflush(stdin);
        printf("\n\nDigite o nome do país: ");
        fgets(nomePais, TAM_MAX, stdin);
        nomePais[strcspn(nomePais, "\n")] = '\0';

        limparTela();

        Pais *paisRetornado = localizarPais(listaPaises, nomePais);
        if (paisRetornado == NULL)
        {
            printf("\nO país '%s' não está na lista de países da nossa agência, digite novamente.", nomePais);
            pause();
            limparTela();
        }
        else
        {
            return paisRetornado;
        }
    }

}

SitioTuristico * selecionarSitioTuristico(Pais *pais, char* textoInicial)
{
    char nomeSitio[TAM_MAX];

    while(1)
    {
        printf("%s\n", textoInicial);
        listarSitiosTuristicos(pais);
        fflush(stdin);
        printf("\n\nDigite o nome do sítio turístico: ");
        fgets(nomeSitio, TAM_MAX, stdin);
        nomeSitio[strcspn(nomeSitio, "\n")] = '\0';

        limparTela();

        SitioTuristico *sitioRetornado = localizarSitioTuristico(pais->listaSitiosTuristico, nomeSitio);
        if (sitioRetornado == NULL)
        {
            printf("\nO sítio '%s' não está na lista de países da nossa agência, digite novamente.", nomeSitio);
            pause();
            limparTela();
        }
        else
        {
            return sitioRetornado;
        }
    }

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
    novoSitioTuristico->countTurista1 = 0;
    novoSitioTuristico->countTurista2 = 0;
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
    int contador = 0;
    SitioTuristico * sitioTuristicoAtual = pais->listaSitiosTuristico;
    printf("Sítios turísticos do(a) %s:\n", pais->nome);
    while(sitioTuristicoAtual != NULL)
    {
        contador++;
        printf("\n%d. %s", contador, sitioTuristicoAtual->nome);
        sitioTuristicoAtual = sitioTuristicoAtual->proximoSitioTuristico;
    }
}

void listarTuristasPorSitiosTuristicos(Pais * pais)
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
    int contador = 0;
    SitioTuristico * sitioTuristicoAtual = pais->listaSitiosTuristico;
    printf("Sítios turísticos do(a) %s:\n", pais->nome);
    while(sitioTuristicoAtual != NULL)
    {
        contador++;
        printf("\n%d. %s", contador, sitioTuristicoAtual->nome);
        printf("\nTotal de turistas do tipo 1: %d", sitioTuristicoAtual->countTurista1);
        printf("\nTotal de turistas do tipo 2: %d\n", sitioTuristicoAtual->countTurista2);
        sitioTuristicoAtual = sitioTuristicoAtual->proximoSitioTuristico;
    }
}

void cadastrarTurista(Turista ** listaTurista, const char * nome, int tipo, Pais *paisDestino, SitioTuristico *sitioDestino)
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
    novoTurista->tipo = tipo;
    novoTurista->proximoTurista = NULL;
    novoTurista->paisDestino = paisDestino;
    novoTurista->sitioDestino = sitioDestino;

    if (novoTurista->tipo == 1)
    {
        novoTurista->sitioDestino->countTurista1++;
    }
    else
    {
        novoTurista->sitioDestino->countTurista2++;
    }
    
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
        while(turistaAtual->proximoTurista != NULL)
        {
            turistaAtual = turistaAtual->proximoTurista;
        }

        turistaAtual->proximoTurista = novoTurista;
    }
}

void solicitarNomeDoCliente(char *nome)
{
    fflush(stdin);
    printf("\nDigite o nome do cliente: ");
    fgets(nome, TAM_MAX, stdin);
    nome[strcspn(nome, "\n")] = '\0';
}

int verificarExistenciaCliente(Turista *listaTurista, char *nomeDoCliente)
{
    if(listaTurista == NULL)
    {
        return 0;
    } 

    /* Iterando toda a lista de turistas e comparando os nomes dos turistas com o nome do cliente passado por parâmetro.
    * caso o cliente seja encontrado, ele é retornado. Caso contrário, é printado que o turista não consta na lista.
    */
    Turista * turistaAtual = listaTurista;
    while(turistaAtual != NULL)
    {
        if(strcmp(turistaAtual->nome, nomeDoCliente) == 0)
        {
            break;
        }

        turistaAtual = turistaAtual->proximoTurista;
    }

    if (turistaAtual) return 1;
    else return 0;
}

void listarTuristas(Turista *listaTuristas)
{
    if(listaTuristas == NULL)
    {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    int contador = 0;
    Turista * turistaAtual = listaTuristas;

    printf("Lista dos clientes cadastrados:\n");
    while(turistaAtual != NULL)
    {
        contador++;
        printf("\n%d. %s", contador, turistaAtual->nome);

        turistaAtual = turistaAtual->proximoTurista;
    }
}

Pais * localizarPaisPeloNomeDoSitio(Pais *listaDePaises, const char *nomeDoSitio)
{
    /* Verificando se a lista de países está vazia */
    if(listaDePaises == NULL)
    {
        printf("\nA lista de países está vazia!");

        return NULL;
    } 

    /* Iterando toda a lista de países e comparando os nomes dos países com o nome do país passado por parâmetro.
    * caso o país seja encontrado, ele é retornado. Caso contrário, é printado que o país não consta na lista.
    */
    Pais * paisAtual = listaDePaises;
    while(paisAtual != NULL)
    {
        SitioTuristico * aux = paisAtual->listaSitiosTuristico;
        
        while(aux != NULL)
        {
            if(strcmp(aux->nome, nomeDoSitio) == 0)
            {
                return paisAtual;
            }

            aux = aux->proximoSitioTuristico;
        }

        paisAtual = paisAtual->proximoPais;
    }

    /* Caso tenha chegado ao fim da lista, o país procurado não está cadastrado */

    return NULL;
}

void exibirMenu()
{
    limparTela();
    exibirAviao();
    printf("\n\n");
    printf("********************************************\n");
    printf("*  Bem-vindo à Agência de Viagens!!!       *\n");
    printf("********************************************");
    printf("\n\n1 -> Cadastrar cliente");
    printf("\n2 -> Exibir clientes cadastrados");
    printf("\n3 -> Exibir países de destino");
    printf("\n4 -> Exibir sítios turísticos de um país");
    printf("\n5 -> Exibir número de turístas por sítio turístico");
    printf("\n6 -> Listar todos os países que foram visitados por clientes decididos");
    printf("\n7 -> Listar todos os países que foram visitados por clientes que usaram o sistema de auxílio");
    printf("\n8 -> Lista de países visitados em geral");
    printf("\n9 -> Lista de países não visitados");
    printf("\n10 -> País mais visitado");
    printf("\n11 -> Sítio mais visitado");
    printf("\n0 -> Sair");
    printf("\n\nDigite sua opção: ");
}

void listarPaisesClientesDecididos(Pais *listaPaises)
{
    if (listaPaises == NULL)
    {
        return;
    }

    printf("*** Lista de países escolhidos por clientes decididos ***");

    Pais * auxPais = listaPaises;

    int counter = 0;

    printf("\n");

    while (auxPais != NULL)
    {
        SitioTuristico * auxSitio = auxPais->listaSitiosTuristico;

        while(auxSitio != NULL)
        {
            if (auxSitio->countTurista1 > 0)
            {
                counter++;
                
                printf("\n%d. %s", counter, auxPais->nome);
                
                break;
            }

            auxSitio = auxSitio->proximoSitioTuristico;
        }

        auxPais = auxPais->proximoPais;
    }

    if (counter == 0)
    {
        printf("\nAinda não temos um ranking para esta categoria... Que tal você nos ajudar adquirindo uma passagem?");
    }
}

void listarPaisesSistemaAuxilio(Pais *listaPaises)
{
    if (listaPaises == NULL)
    {
        return;
    }

    printf("*** Lista de países escolhidos por clientes que utilizaram o sistema de auxilio ***");
    printf("\n");

    Pais * auxPais = listaPaises;

    int counter = 0;

    while (auxPais != NULL)
    {
        SitioTuristico * auxSitio = auxPais->listaSitiosTuristico;

        while(auxSitio != NULL)
        {
            if (auxSitio->countTurista2 > 0)
            {
                counter++;
                
                printf("\n%d. %s", counter, auxPais->nome);
                
                break;
            }

            auxSitio = auxSitio->proximoSitioTuristico;
        }

        auxPais = auxPais->proximoPais;
    }

    if (counter == 0)
    {
        printf("\nAinda não temos um ranking para esta categoria... Que tal você nos ajudar adquirindo uma passagem?");
    }
}

void listarPaisesVisitados(Pais *listaPaises)
{
    if (listaPaises == NULL)
    {
        return;
    }

    printf("*** Lista de países visitados ***");
    printf("\n");

    Pais * auxPais = listaPaises;

    int counter = 0;

    while (auxPais != NULL)
    {
        int result = verificarSePaisFoiVisitado(auxPais);

        if (result == 1)
        {
            counter++;
            
            printf("\n%d. %s", counter, auxPais->nome);
        }

        auxPais = auxPais->proximoPais;
    }

    if (counter == 0)
    {
        printf("\nInfelizmente, nenhum país ainda foi visitado no nosso sistema :(");
    }
}

void listarPaisesNaoVisitados(Pais *listaPaises)
{
    if (listaPaises == NULL)
    {
        return;
    }

    printf("*** Lista de países não visitados ***");
    printf("\n");

    Pais * auxPais = listaPaises;

    int counter = 0;

    while (auxPais != NULL)
    {
        int result = verificarSePaisFoiVisitado(auxPais);

        if (result == 0)
        {
            counter++;
            
            printf("\n%d. %s", counter, auxPais->nome);            
        }

        auxPais = auxPais->proximoPais;
    }

    if (counter == 0)
    {
        printf("\nOba! Não há nenhum país no nosso sistema que ainda não foi visitado!");
    }
}

void listarPaisMaisVisitado(Pais *listaPaises)
{
    if (listaPaises == NULL)
    {
        return;
    }

    printf("*** Pais mais visitado ***");
    printf("\n");

    Pais * auxPais = listaPaises;

    Pais * paisMaisVisitado = auxPais;
    int numeroDeVisitas = numeroVisitasDoPais(auxPais);

    int counter = 1;

    int empate = 0;

    while (auxPais->proximoPais != NULL)
    {
        auxPais = auxPais->proximoPais;

        int numeroVisitasPaisAtual = numeroVisitasDoPais(auxPais);

        if (numeroVisitasPaisAtual > numeroDeVisitas)
        {
            paisMaisVisitado = auxPais;
            numeroDeVisitas = numeroVisitasPaisAtual;
        }
    }

    /*
        Verificando se há um outro país com o mesmo número de visitas 
     */
    while (auxPais->proximoPais != NULL)
    {
        auxPais = auxPais->proximoPais;

        int numeroVisitasPaisAtual = numeroVisitasDoPais(auxPais);

        if (numeroVisitasPaisAtual == numeroDeVisitas && auxPais != paisMaisVisitado)
        {
            empate = 1;

            break;
        }
    }

    if (empate)
    {
        printf("\nNão há um país mais visitado no nosso sistema! Porém, há países que estão entre os mais visitados, como por exemplo o %s com %d visitas!", paisMaisVisitado->nome, numeroDeVisitas);
        listarPaisMaisVisitadoTipo1(listaPaises);
        listarPaisMaisVisitadoTipo2(listaPaises);
    }
    else if (numeroDeVisitas)
    {
        printf("\nVocê sabia? *0* \nO país mais visitado do nosso sistema é o %s com o total de %d visitas!", paisMaisVisitado->nome, numeroDeVisitas);
        listarPaisMaisVisitadoTipo1(listaPaises);
        listarPaisMaisVisitadoTipo2(listaPaises);
    }
    else
    {
        printf("\nNão temos um ranking ainda :(! Que tal você nos ajudar adquirindo uma passagem?");
    }
}

void listarPaisMaisVisitadoTipo1(Pais *listaPaises)
{
    if (listaPaises == NULL)
    {
        return;
    }

    Pais * auxPais = listaPaises;

    Pais * paisMaisVisitado = auxPais;
    int numeroDeVisitas = numeroVisitasDoPaisTipo1(auxPais);

    int counter = 1;

    int empate = 0;

    while (auxPais->proximoPais != NULL)
    {
        auxPais = auxPais->proximoPais;

        int numeroVisitasPaisAtual = numeroVisitasDoPaisTipo1(auxPais);

        if (numeroVisitasPaisAtual > numeroDeVisitas)
        {
            paisMaisVisitado = auxPais;
            numeroDeVisitas = numeroVisitasPaisAtual;
        }
    }

    /*
        Verificando se há um outro país com o mesmo número de visitas 
     */
    if (numeroDeVisitas)
    {
        auxPais = listaPaises;

        while (auxPais->proximoPais != NULL && !empate)
        {
            auxPais = auxPais->proximoPais;

            int numeroVisitasPaisAtual = numeroVisitasDoPais(auxPais);

            if (numeroVisitasPaisAtual == numeroDeVisitas && auxPais != paisMaisVisitado)
            {
                empate = 1;
            }
        }
    }

    if (empate)
    {
        printf("\nNão há um país mais visitado no nosso sistema para o tipo de cliente decidido! Porém, há países que estão entre os mais visitados, como por exemplo o %s com %d visitas!", paisMaisVisitado->nome, numeroDeVisitas);
    }    
    else if (numeroDeVisitas)
    {
        printf("\nPara o tipo de cliente decidido, o país %s é o destino mais escolhido, totalizando %d visitas!", paisMaisVisitado->nome, numeroDeVisitas);
    }
}

void listarPaisMaisVisitadoTipo2(Pais *listaPaises)
{
    if (listaPaises == NULL)
    {
        return;
    }

    Pais * auxPais = listaPaises;

    Pais * paisMaisVisitado = auxPais;
    int numeroDeVisitas = numeroVisitasDoPaisTipo2(auxPais);

    int counter = 1;

    int empate = 0;

    while (auxPais->proximoPais != NULL)
    {
        auxPais = auxPais->proximoPais;

        int numeroVisitasPaisAtual = numeroVisitasDoPaisTipo2(auxPais);

        if (numeroVisitasPaisAtual > numeroDeVisitas)
        {
            paisMaisVisitado = auxPais;
            numeroDeVisitas = numeroVisitasPaisAtual;
        }
    }

    /*
        Verificando se há um outro país com o mesmo número de visitas 
     */
    if (numeroDeVisitas)
    {
        auxPais = listaPaises;

        while (auxPais->proximoPais != NULL && empate)
        {
            auxPais = auxPais->proximoPais;

            int numeroVisitasPaisAtual = numeroVisitasDoPais(auxPais);

            if (numeroVisitasPaisAtual == numeroDeVisitas && auxPais != paisMaisVisitado)
            {
                empate = 1;
            }
        }
    }

    if (empate)
    {
        printf("\nNão há um país mais visitado no nosso sistema para o tipo de cliente que utilizou o auxilio do sistema! Porém, há países que estão entre os mais visitados, como por exemplo o %s com %d visitas!", paisMaisVisitado->nome, numeroDeVisitas);
    } 
    else if (numeroDeVisitas)
    {
        printf("\nPara o tipo de cliente que utilizou o auxilio do sistema, o país %s é o destino mais escolhido, totalizando %d visitas!", paisMaisVisitado->nome, numeroDeVisitas);
    }
}

void listarSitioMaisVisitado(Pais *listaPaises)
{
    printf("*** Sítio mais visitado ***");
    printf("\n");

    Pais * auxPais = listaPaises;

    SitioTuristico * sitioMaisVisitado = NULL;
    int numeroDeVisitas = 0;

    int empate = 0;

    while(auxPais != NULL)
    {
        SitioTuristico * auxSitio = auxPais->listaSitiosTuristico;

        while (auxSitio != NULL)
        {
            if (sitioMaisVisitado == NULL)
            {
                sitioMaisVisitado = auxSitio;
                numeroDeVisitas = auxSitio->countTurista1 + auxSitio->countTurista2;
            }
            else
            {
                int totalVisitasSitioAtual = auxSitio->countTurista1 + auxSitio->countTurista2;

                if (totalVisitasSitioAtual > numeroDeVisitas)
                {
                    sitioMaisVisitado = auxSitio;
                    numeroDeVisitas = totalVisitasSitioAtual;
                }
            }

            auxSitio = auxSitio->proximoSitioTuristico;
        }

        auxPais = auxPais->proximoPais;
    }

    /* 
        Verificando se há outro sitio com o mesmo número de visitas
     */
    if (numeroDeVisitas)
    {
        auxPais = listaPaises;

        while(auxPais != NULL && !empate)
        {
            SitioTuristico * auxSitio = auxPais->listaSitiosTuristico;

            while(auxSitio != NULL)
            {
                int totalVisitasSitioAtual = auxSitio->countTurista1 + auxSitio->countTurista2;

                if (totalVisitasSitioAtual == numeroDeVisitas && auxSitio != sitioMaisVisitado)
                {
                    empate = 1;

                    break;
                }

                auxSitio = auxSitio->proximoSitioTuristico;
            }

            auxPais = auxPais->proximoPais;
        }
    }


    Pais * paisDoSitio = localizarPaisPeloNomeDoSitio(listaPaises, sitioMaisVisitado->nome);

    if (empate)
    {
        printf("\nNão há um sítio mais visitado no nosso sistema! Porém, há sitios que estão entre os mais visitados, como por exemplo %s/%s com %d visitas!", sitioMaisVisitado->nome, paisDoSitio->nome, numeroDeVisitas);
        listarSitioMaisVisitadoTipo1(listaPaises);
        listarSitioMaisVisitadoTipo2(listaPaises);
    }
    else if (numeroDeVisitas)
    {
        printf("\nVocê sabia? *0* \nO sítio mais visitado do nosso sistema é o %s com o total de %d visitas!", sitioMaisVisitado->nome, numeroDeVisitas);
        listarSitioMaisVisitadoTipo1(listaPaises);
        listarSitioMaisVisitadoTipo2(listaPaises);
    }
    else
    {
        printf("\nNão temos um ranking ainda :(! Que tal você nos ajudar adquirindo uma passagem?");
    }
}

void listarSitioMaisVisitadoTipo1(Pais *listaPaises)
{    
    Pais * auxPais = listaPaises;

    SitioTuristico * sitioMaisVisitado = NULL;
    int numeroDeVisitas = 0;

    int empate = 0;

    while(auxPais != NULL)
    {
        SitioTuristico * auxSitio = auxPais->listaSitiosTuristico;

        while (auxSitio != NULL)
        {
            if (sitioMaisVisitado == NULL)
            {
                sitioMaisVisitado = auxSitio;
                numeroDeVisitas = auxSitio->countTurista1;
            }
            else
            {
                int totalVisitasSitioAtual = auxSitio->countTurista1;

                if (totalVisitasSitioAtual > numeroDeVisitas)
                {
                    sitioMaisVisitado = auxSitio;
                    numeroDeVisitas = totalVisitasSitioAtual;
                }
            }

            auxSitio = auxSitio->proximoSitioTuristico;
        }

        auxPais = auxPais->proximoPais;
    }

    /* 
        Verificando se há outro sitio com o mesmo número de visitas
     */
    if (numeroDeVisitas)
    {
        auxPais = listaPaises;

        while(auxPais != NULL && !empate)
        {
            SitioTuristico * auxSitio = auxPais->listaSitiosTuristico;

            while(auxSitio != NULL)
            {
                int totalVisitasSitioAtual = auxSitio->countTurista1;

                if (totalVisitasSitioAtual == numeroDeVisitas && auxSitio != sitioMaisVisitado)
                {
                    empate = 1;

                    break;
                }

                auxSitio = auxSitio->proximoSitioTuristico;
            }

            auxPais = auxPais->proximoPais;
        }
    }

    Pais * paisDoSitio = localizarPaisPeloNomeDoSitio(listaPaises, sitioMaisVisitado->nome);

    if (empate)
    {
        printf("\nNão há um sitio mais visitado no nosso sistema para o tipo de cliente decidido! Porém, há sitios que estão entre os mais visitados, como por exemplo %s/%s com %d visitas!", sitioMaisVisitado->nome, paisDoSitio->nome, numeroDeVisitas);
    } 
    else if (numeroDeVisitas)
    {
        printf("\nPara o tipo de cliente decidido, o sítio %s é o destino mais escolhido, totalizando %d visitas!", sitioMaisVisitado->nome, numeroDeVisitas);
    }
}

void listarSitioMaisVisitadoTipo2(Pais *listaPaises)
{    
    Pais * auxPais = listaPaises;

    SitioTuristico * sitioMaisVisitado = NULL;
    int numeroDeVisitas = 0;

    int empate = 0;

    while(auxPais != NULL)
    {
        SitioTuristico * auxSitio = auxPais->listaSitiosTuristico;

        while (auxSitio != NULL)
        {
            if (sitioMaisVisitado == NULL)
            {
                sitioMaisVisitado = auxSitio;
                numeroDeVisitas = auxSitio->countTurista2;
            }
            else
            {
                int totalVisitasSitioAtual = auxSitio->countTurista2;

                if (totalVisitasSitioAtual > numeroDeVisitas)
                {
                    sitioMaisVisitado = auxSitio;
                    numeroDeVisitas = totalVisitasSitioAtual;
                }
            }

            auxSitio = auxSitio->proximoSitioTuristico;
        }

        auxPais = auxPais->proximoPais;
    }

    /* 
        Verificando se há outro sitio com o mesmo número de visitas
     */
    if (numeroDeVisitas)
    {
        auxPais = listaPaises;

        while(auxPais != NULL && !empate)
        {
            SitioTuristico * auxSitio = auxPais->listaSitiosTuristico;

            while(auxSitio != NULL)
            {
                int totalVisitasSitioAtual = auxSitio->countTurista2;

                if (totalVisitasSitioAtual == numeroDeVisitas && auxSitio != sitioMaisVisitado)
                {
                    empate = 1;

                    break;
                }

                auxSitio = auxSitio->proximoSitioTuristico;
            }

            auxPais = auxPais->proximoPais;
        }
    }

    Pais * paisDoSitio = localizarPaisPeloNomeDoSitio(listaPaises, sitioMaisVisitado->nome);

    if (empate)
    {
        printf("\nNão há um sitio mais visitado no nosso sistema para o tipo de cliente que utilizou o auxilio do sistema! Porém, há sitios que estão entre os mais visitados, como por exemplo %s/%s com %d visitas!", sitioMaisVisitado->nome, paisDoSitio->nome, numeroDeVisitas);
    } 
    else if (numeroDeVisitas > 0)
    {
        printf("\nPara o tipo de cliente que utilizou o sistema de auxílio, o sítio %s é o destino mais escolhido, totalizando %d visitas!", sitioMaisVisitado->nome, numeroDeVisitas);
    }
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



Arvore * inserirPergunta(Arvore* raiz, const char pergunta[TAM_MAX], int valor) 
{
    if(raiz == NULL)
    {
        Arvore* novo = (Arvore*) malloc(sizeof(Arvore));
        strcpy(novo->info, pergunta);
        novo->valor = valor;
        novo->nao = NULL;
        novo->sim = NULL;

        return novo;
    }

    if(valor < raiz->valor)
    {
        raiz->sim = inserirPergunta(raiz->sim, pergunta, valor);
    }
    else if(valor > raiz->valor)
    {
        raiz->nao = inserirPergunta(raiz->nao, pergunta, valor);   
    }
    else if(valor == raiz->valor)
    {
        return raiz;
    }

    return raiz;
}

Arvore * printPerguntas(Arvore *raiz) 
{
    if(raiz == NULL)
    {
        return NULL;
    }

    if(raiz->nao == NULL && raiz->sim == NULL)
    {
        printf("\nSeu destino é: %s\n", raiz->info);

        return raiz;
    }

    printf("\nPergunta: %s", raiz->info);

    char opcao;
    printf(" (S/N): ");
    scanf(" %c", &opcao);
    
    if(opcao == 's' || opcao == 'S')
    {
        if(raiz->sim != NULL)
        {
            raiz = printPerguntas(raiz->sim);
        }
        else
        {
            printf("\nSeu destino é: %s\n", raiz->info);
        }
    }
    else if (opcao == 'n' || opcao == 'N')
    {
        if(raiz->nao != NULL)
        {
            raiz = printPerguntas(raiz->nao);
        }
        else
        {
            printf("\nSeu destino é: %s\n", raiz->info);
        }
    }
    else
    {
        printf("Opção inválida! Tente novamente");
        
        raiz = printPerguntas(raiz);
    }


    return raiz;
}


Arvore * criarNodo(const char * info, int valor)
{
    Arvore * newNode = (Arvore*)malloc(sizeof(Arvore));

    if (newNode == NULL) 
    {
        printf("\nNão há memória disponível");

        exit(EXIT_FAILURE);
    }

    newNode->sim = NULL;
    newNode->nao = NULL;
    newNode->valor = valor;
    strcpy(newNode->info, info);

    return newNode;
}

void inorderTraversal(Arvore * root)
{
    if (root != NULL) 
    {
        inorderTraversal(root->sim);
        printf("\n%s", root->info);
        inorderTraversal(root->nao);
    }
}

void popularTuristas(Pais *listaPaises, Turista **listaTuristas, char *nomeArquivo) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[100];
    char nome[TAM_MAX], pais[TAM_MAX], sitio[TAM_MAX];
    int tipo;

    // Verifica se o arquivo está vazio
    if (fscanf(arquivo, "%[^\n]\n", linha) == EOF) {
        printf("O arquivo está vazio.\n");
        fclose(arquivo);
        return;
    }

    // Volta ao início do arquivo para começar a leitura
    fseek(arquivo, 0, SEEK_SET);

    while (fscanf(arquivo, "%[^;];%d;%[^;];%[^\n]\n", nome, &tipo, pais, sitio) == 4) {
        Pais *paisDestino = localizarPais(listaPaises, pais);
        SitioTuristico *sitioDestino = localizarSitioTuristico(paisDestino->listaSitiosTuristico, sitio);
        cadastrarTurista(listaTuristas, nome, tipo, paisDestino, sitioDestino);
    }

    fclose(arquivo);
}


void salvarTuristas(const char *nomeArquivo, Turista *listaTuristas) 
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    
    if (arquivo == NULL) 
    {
        fclose(arquivo);
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    while (listaTuristas != NULL) 
    {
        fprintf(arquivo, "%s;%d;%s;%s\n", listaTuristas->nome, listaTuristas->tipo, listaTuristas->paisDestino->nome, listaTuristas->sitioDestino->nome);
        listaTuristas = listaTuristas->proximoTurista;
    }

    fclose(arquivo);
}

void freeAll(Turista **listaTuristas, Pais **listaPaises, Arvore *raiz)
{
    Turista *turistaAnt = NULL;
    
    while((*listaTuristas) != NULL)
    {
        turistaAnt = *listaTuristas;
        *listaTuristas = (*listaTuristas)->proximoTurista;
        free(turistaAnt);
    }

    Pais *paisAnt = NULL;
    
    while((*listaPaises) != NULL)
    {
        paisAnt = *listaPaises;

        SitioTuristico *sitioInicial = paisAnt->listaSitiosTuristico;
        SitioTuristico *sitioAtual = NULL;
    
        while((sitioInicial) != NULL)
        {
            sitioAtual = sitioInicial;
            sitioInicial = (sitioInicial)->proximoSitioTuristico;
            free(sitioAtual);
        }

        *listaPaises = (*listaPaises)->proximoPais;
        free(paisAnt);
    }

    freeArvore(raiz);
}

void freeArvore(Arvore *raiz)
{
    if(raiz == NULL) return;
    freeArvore(raiz->sim);
    freeArvore(raiz->nao);
    free(raiz);
}

void carregarPerguntas(Arvore ** raiz)
{
    /* 
        Viagem Nacional
     */
    *raiz = inserirPergunta(*raiz, "Você prefere viagem nacional?", 16);

    inserirPergunta(*raiz, "Você gosta de praia?", 8);
    inserirPergunta(*raiz, "Você gosta de culinária africana/indígena?", 4);
    
    inserirPergunta(*raiz, "Você gosta de culinária indígena?", 2);
    inserirPergunta(*raiz, "Salvador", 3);
    inserirPergunta(*raiz, "Fortaleza", 1);
    
    inserirPergunta(*raiz, "Você gosta de trilhas?", 6);
    inserirPergunta(*raiz, "Florianópolis", 5);
    inserirPergunta(*raiz, "Porto Alegre", 7);

    inserirPergunta(*raiz, "Você gosta de museus?", 12);

    inserirPergunta(*raiz, "Você gosta de shows de rock?", 10);
    inserirPergunta(*raiz, "Distrito Federal", 9);
    inserirPergunta(*raiz, "Belo Horizonte", 11);

    inserirPergunta(*raiz, "Você gosta de cultura sertaneja?", 14);
    inserirPergunta(*raiz, "Goiânia", 13);
    inserirPergunta(*raiz, "Manaus", 15);

    /*
        Viagem Internacional 
     */

    inserirPergunta(*raiz, "Você gosta de frio?", 24);
    inserirPergunta(*raiz, "Você gosta da cultura oriental?", 20);

    inserirPergunta(*raiz, "Você gosta de cultura geek?", 18);
    inserirPergunta(*raiz, "Tokyo", 17);
    inserirPergunta(*raiz, "Seul", 19);

    inserirPergunta(*raiz, "Você gosta de culinária com massas?", 22);
    inserirPergunta(*raiz, "Roma", 21);
    inserirPergunta(*raiz, "Berlim", 23);

    inserirPergunta(*raiz, "Você gosta de praia?", 28);
    
    inserirPergunta(*raiz, "Você gosta de luxo?", 26);
    inserirPergunta(*raiz, "Dubai", 25);
    inserirPergunta(*raiz, "Bangkok", 27);

    inserirPergunta(*raiz, "Você gosta de Parques Florestais?", 30);
    inserirPergunta(*raiz, "Safari Africano", 29);
    inserirPergunta(*raiz, "Cairo", 31);
}

void carregarPaisesESitios(Pais ** listaPaises)
{

    /* Inserindo países e sítios turísticos */

    inserirPais(listaPaises, "Brasil");
    inserirPais(listaPaises, "Japão");
    inserirPais(listaPaises, "Coréia do Sul");
    inserirPais(listaPaises, "Itália");
    inserirPais(listaPaises, "Alemanha");
    inserirPais(listaPaises, "Emirados Árabes Unidos");
    inserirPais(listaPaises, "Tailândia");
    inserirPais(listaPaises, "Quênia");
    inserirPais(listaPaises, "Egito");



    Pais * brasil = localizarPais(*listaPaises, "Brasil");
    Pais * japao = localizarPais(*listaPaises, "Japão");
    Pais * coreiaDoSul = localizarPais(*listaPaises, "Coréia do Sul");
    Pais * italia = localizarPais(*listaPaises, "Itália");
    Pais * alemanha = localizarPais(*listaPaises, "Alemanha");
    Pais * eam = localizarPais(*listaPaises, "Emirados Árabes Unidos");
    Pais * tailandia = localizarPais(*listaPaises, "Tailândia");
    Pais * quenia = localizarPais(*listaPaises, "Quênia");
    Pais * egito = localizarPais(*listaPaises, "Egito");

    inserirNovoSitioTuristico(brasil, "Salvador");
    inserirNovoSitioTuristico(brasil, "Fortaleza");
    inserirNovoSitioTuristico(brasil, "Florianópolis");
    inserirNovoSitioTuristico(brasil, "Porto Alegre");
    inserirNovoSitioTuristico(brasil, "Brasilia");
    inserirNovoSitioTuristico(brasil, "Belo Horizonte");
    inserirNovoSitioTuristico(brasil, "Goiânia");
    inserirNovoSitioTuristico(brasil, "Manaus");

    inserirNovoSitioTuristico(japao, "Tokyo");
    inserirNovoSitioTuristico(coreiaDoSul, "Seul");
    inserirNovoSitioTuristico(italia, "Roma");
    inserirNovoSitioTuristico(alemanha, "Berlim");
    inserirNovoSitioTuristico(eam, "Dubai");
    inserirNovoSitioTuristico(tailandia, "Bangkok");
    inserirNovoSitioTuristico(quenia, "Safari Africano");
    inserirNovoSitioTuristico(egito, "Cairo");

}