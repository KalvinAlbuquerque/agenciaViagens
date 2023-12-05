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

    // Testes -----------------------------------------------------------------------

    /* Teste para verificar a funcionalidade da função inserirPais, listarPaises*/
    inserirPais(&listaPaises, "Brasil");
    inserirPais(&listaPaises, "Japão");
    inserirPais(&listaPaises, "Rússia");
    inserirPais(&listaPaises, "México");

    /* Testando a função localizarPais */
    Pais * russia = localizarPais(listaPaises, "Rússia");
    Pais * brasil = localizarPais(listaPaises, "Brasil");

    /* Testando a função inserirSítio e listarSítio */
    inserirNovoSitioTuristico(russia, "Museu Hermitage");
    inserirNovoSitioTuristico(russia, "Kremlin");
    inserirNovoSitioTuristico(russia, "Catedral de São Basilísco");

    inserirNovoSitioTuristico(brasil, "Salvador");
    inserirNovoSitioTuristico(brasil, "Rio de Janeiro");
    inserirNovoSitioTuristico(brasil, "Lençóis");

    Arvore *raiz = NULL;

    raiz = inserirPergunta(raiz, "Você Prefe viagem internacional?",1);

    inserirPergunta(raiz, "Você gosta de praia?",2);

    inserirPergunta(raiz, "Você gosta de montanhas?",3);

    inserirPergunta(raiz, "Seu destino ideal é Canadá",4);

    inserirPergunta(raiz, "Seu destino ideal é Salvador",5);
/*     inserirPergunta(raiz, "Você gosta de florestas?", 4); */
    /* inserirPergunta(raiz, "Você gosta de museus?", 5);
    inserirPergunta(raiz, "Você gosta de frio?", 6);
    inserirPergunta(raiz, "Você gosta de esportes aquáticos?", 7);
    inserirPergunta(raiz, "Você prefere destinos rurais?", 8);
    inserirPergunta(raiz, "Você gosta de atividades ao ar livre?", 9);
    inserirPergunta(raiz, "Você prefere destinos históricos?", 10);
    inserirPergunta(raiz, "Você gosta de aventuras?", 11);
    inserirPergunta(raiz, "Você prefere destinos com muita agitação?", 12);
    inserirPergunta(raiz, "Você gosta de gastronomia local?", 13);
    inserirPergunta(raiz, "Você prefere destinos exóticos?", 14);
    inserirPergunta(raiz, "Você gosta de festivais e eventos culturais?",15);
    inserirPergunta(raiz, "Seu destino ideal foi: Salvador", 16);
    inserirPergunta(raiz, "Seu destino ideal foi: Rio de Janeiro", 17); */

    printPerguntas(raiz);
    // --------------------------------------------------------------------------------

    do
    {
        //limparTela();
        //exibirMenu();
        scanf(" %d", &opcao);
        getchar();

        //limparTela();

        switch(opcao)
        {
            case 1:
            {
                /* Solicitando o nome do cliente */
                solicitarNomeDoCliente(nomeCliente);
                int clienteExiste = verificarExistenciaCliente(listaTuristas, nomeCliente);

                limparTela();

                /* Cadastrando o cliente */
                if (!clienteExiste)
                {
                    /* Selecionando o país de destino e criando o cliente/turista */
                    printf("Bem vindo %s!", nomeCliente);
                    Pais *paisSelecionado = selecionarPais(listaPaises, "Para qual país deseja viajar?");

                    limparTela();

                    printf("Certo %s, ", nomeCliente);
                    SitioTuristico *sitioSelecionado = selecionarSitioTuristico(paisSelecionado, "qual dos sítios turísticos abaixo você tem interesse em visitar?");

                    limparTela();

                    /* Confirmando o cadastro do cliente */
                    int confirmacao = confirmarViagem(nomeCliente, paisSelecionado, sitioSelecionado);
                    
                    limparTela();

                    if (confirmacao)
                    {
                        /* Cadastrando cliente */
                        cadastrarTurista(&listaTuristas, nomeCliente, paisSelecionado);
                        sitioSelecionado->countTurista1++;
                        printf("Cadastramos você no nosso sistema %s, boa viagem!\n", nomeCliente);
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

}

int confirmarViagem(char *nome, Pais *pais, SitioTuristico *sitioTuristico) {

    while (1)
    {
        printf("Então %s, você deseja viajar para a(o) %s e visitar o sítio turístico %s? (S/N)\nConfirme: ", nome, pais->nome, sitioTuristico->nome);
        int confirmacao = getchar();
        getchar();

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

void cadastrarTurista(Turista ** listaTurista, const char * nome, Pais *paisDestino)
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
    novoTurista->proximoTurista = NULL;
    novoTurista->paisDestino = paisDestino;
    
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
    printf("\n4.Exibir sítios turísticos de um país");
    printf("\n5.Exibir número de turístas por sítio turístico");
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



/* Arvore * inserirPergunta(Arvore* raiz, const char pergunta[TAM_MAX], int valor) 
{
    if(raiz == NULL)
    {
        Arvore* novo = (Arvore*) malloc(sizeof(Arvore));
        strcpy(novo->pergunta, pergunta);
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
} */

Arvore* inserirPergunta(Arvore* raiz, const char * info, int valor) {
    
   if (raiz == NULL) {
        Arvore* newNode = (Arvore*)malloc(sizeof(Arvore));
        if (newNode == NULL) {
            // Tratamento de erro, se a alocação falhar
            exit(EXIT_FAILURE);
        }

        // Usar strncpy para copiar a string, evitando leituras excessivas
        strncpy(newNode->info, info, TAM_MAX - 1);
        newNode->info[TAM_MAX - 1] = '\0';  // Garantir terminação nula
        newNode->nao = NULL;
        newNode->sim = NULL;

        return newNode;
    }

    // Comparar valores e decidir qual ramo seguir
    if (valor < raiz->valor) {
        raiz->sim = inserirPergunta(raiz->sim, info, valor);
    } else if (valor > raiz->valor) {
        raiz->nao = inserirPergunta(raiz->nao, info, valor);
    } else {
        // Chaves duplicadas não são permitidas
        return raiz;
    }

 
    int balance = (raiz->sim ? 1 + altura(raiz->sim) : 0) - (raiz->nao ? 1 + altura(raiz->nao) : 0);

    // Realizar rotações, se necessário
    if (balance > 1) {
        // Desbalanceamento à esquerda
        if (valor < raiz->sim->valor) {
            // Rotação simples à direita
            return rotateRight(raiz);
        } else {
            // Rotação dupla: rotação simples à esquerda no filho esquerdo
            // seguida de rotação simples à direita no nó atual
            raiz->sim = rotateLeft(raiz->sim);
            return rotateRight(raiz);
        }
    } else if (balance < -1) {
        // Desbalanceamento à direita
        if (valor > raiz->nao->valor) {
            // Rotação simples à esquerda
            return rotateLeft(raiz);
        } else {
            // Rotação dupla: rotação simples à direita no filho direito
            // seguida de rotação simples à esquerda no nó atual
            raiz->nao = rotateRight(raiz->nao);
            return rotateLeft(raiz);
        }
    }
    return raiz;
} 

void printPerguntas(Arvore *raiz) 
{
    if(raiz == NULL)
    {
        return;
    }

    printf("\nPergunta: %s", raiz->info);

    if(raiz->nao == NULL && raiz->sim == NULL)
    {
        printf("\nSeu destino é: %s\n", raiz->info);
        return;
    }

    char opcao;
    printf(" (S/N): ");
    scanf(" %c", &opcao);
    
    if(opcao == 's' || opcao == 'S')
    {
        if(raiz->sim != NULL)
        {
            printPerguntas(raiz->sim);
        }
        else
        {
            printf("\nSeu destino é: %s\n", raiz->info);
        }
    }
    else
    {
        if(raiz->nao != NULL)
        {
            printPerguntas(raiz->nao);
        }
        else
        {
            printf("\nSeu destino é: %s\n", raiz->info);
        }
    }
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

Arvore * rotateLeft(struct Arvore* x) {
    Arvore* y = x->nao;
    x->nao = y->sim;
    y->sim = x;
    return y;
}

// Função auxiliar para realizar uma rotação simples à direita
Arvore* rotateRight(struct Arvore* y) {
    struct Arvore* x = y->sim;
    y->sim = x->nao;
    x->nao = y;
    return x;
}

int altura(Arvore* no) {
    if (no == NULL) {
        return 0;
    }

    int alturaSim = altura(no->sim);
    int alturaNao = altura(no->nao);

    return (alturaSim > alturaNao) ? alturaSim + 1 : alturaNao + 1;
}