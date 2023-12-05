#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define TAM_MAX 50

/* 
* Header destinado a conter todos os protótipos de funções e estruturas que serão utilizadas na aplicação, 
* juntamente com a respectiva documentação de cada uma.
*/


/* Lista simplesmente encadeada de sítios turísticos. 
* Possui os seguintes atributos: 
* nome do sítio turístico,
* um contador para turistas do tipo 1 e do tipo 2 que visitaram esse sitio turístico,
* ponteiro para o próximo sítio turístico
*/
typedef struct SitioTuristico
{
    char nome[TAM_MAX];
    int countTurista1;
    int countTurista2;
    struct SitioTuristico * proximoSitioTuristico;

}SitioTuristico;

/* Lista duplamente encadeada de países.
* Possui os segunites atributos:
* nome do país,
* um ponteiro para a lista de sítios turísticos daquele país,
* um ponteiro para o próximo país
*/
typedef struct Pais
{
    char nome[TAM_MAX];
    SitioTuristico * listaSitiosTuristico;
    struct Pais * proximoPais;

}Pais;

/* Lista simplesmente encadeada de turistas.
* Possui os seguintes atributos:
* nome do cliente,
* tipo do cliente, podendo ser tipo um ou tipo dois. O tipo um será aquele cliente que possui
* um país de destino confirmado, enquanto o tipo dois necessitará de ajuda do sistema para decidir
* seu destino.
* O penúltimo atributo é o país de destino e
* um ponteiro para o próximo cliente. 
*/
typedef struct Turista
{
    char * nome;
    int tipo;
    Pais *paisDestino;
    struct Turista * proximoTurista;

}Turista;


/* Árvore binária para representar as escolhas dos sítios turísticos.
* Possui os seguintes atributos:
* pergunta,
* ponteiro para o próximo nó caso a resposta seja sim,
* ponteiro para o próximo nó caso a resposta seja não. 
 */
typedef struct Arvore
{
    char pergunta[TAM_MAX];
    struct Arvore * sim;
    struct Arvore * nao;
    int valor;
}Arvore;


/*
    FUNÇÕES PARA PAÍSES
*/

/* Função destinada a inserir um país na lista de países da aplicação. */
void inserirPais(Pais ** listaPaises, const char * nomePais);

/* Função destinada a listar todos os países cadastrados */
void listarPaises(Pais * listaPaises);

/* Função destinada a iterar toda a lista de países para encontrar um país cujo nome é passado por
* parâmetro e retorná-lo 
*/
Pais * localizarPais(Pais * listaPaises, const char * nomePais);

/* Função para que o usuário selecione um país da lista de países, retornando a referência desse país */
Pais * selecionarPais(Pais * listaPaises, char *textoInicial);

/* 
    FUNÇÕES PARA SÍTIOS TURÍSTICOS
*/

/* Função destinada a inserir um novo sitio turístico na lista de sítios turísticos
* de determinado sítio.
*/
void inserirNovoSitioTuristico(Pais * pais, const char * nomeSitioTuristico);

/* Função destinada a listar todos os guias turísticos de um determinado sítio passado
* por parâmetro
*/
void listarSitiosTuristicos(Pais * pais);

/* Função destinada a listar todos os sítios turísticos de um país passado
* por parâmetro
*/
void listarTuristasPorSitiosTuristicos(Pais * pais);

/* Função destinada a listar todos os sítios turísticos  país passado por parâmetro e a contagem dos tipos de turistas de 
*  cada um desses sítios
*/
SitioTuristico * localizarSitioTuristico(SitioTuristico * listaSitioTuristico, const char * nomeSitio);

/* Função para que o usuário selecione um sítio da lista de sítios, retornando a referência desse sítio */
SitioTuristico * selecionarSitioTuristico(Pais *pais, char* textoInicial);

/*
    FUNÇÕES PARA TURISTAS/CLIENTES/USUÁRIOS
*/

/* Função responsável por cadastrar o turista */
void cadastrarTurista(Turista ** listaTurista, const char * nome, Pais *paisDestino);

/* Função responsável por solicitar o nome do cliente cadastrado*/
void solicitarNomeDoCliente(char *nome);

/* Função para verificar se o cliente já existe na lista de clientes, se sim retorna 1, senão retorna 0 */
int verificarExistenciaCliente(Turista *listaTurista, char *nomeDoCliente);

/* Função para exibir os turistas cadastrados */
void listarTuristas(Turista *listaTuristas);

/* Função destinada a iterar toda a lista de clientes para encontrar um cliente cujo nome é passado por
* parâmetro e retorná-lo 
*/
Turista * localizarCliente(Turista * listaTurista, char *nome);

//TODO: criar função para solicitar nome e pais de destino do turista. Caso não tenha, chama a funçao para decidir o pais de destino

/* Função destinada a printar o menu de escolhas do usuário*/
void exibirMenu();


/* 
    FUNÇÕES UTILITÁRIAS
*/

/* Retorna 1 para aceitar a viagem e 0 se não */
int confirmarViagem(char *nome, Pais *pais, SitioTuristico *sitioTuristico);

/* Função destinada a limpar tela.
* Pode ser utilizada tanto em sistemas windows como unix.
*/
void limparTela();

/* Função destinada a dar um pause na tela do usuário e esperar ele apertar enter para continuar */
void pause();

/* Função destinada a exibir um avião para enfeitar o menu */
void exibirAviao();

Arvore * inserirPergunta(Arvore* raiz, const char pergunta[TAM_MAX], int valor) ;

/* Função destinada a exibir a árvore em 2D */
void imprimeArvorePorValor(Arvore *raiz, int valor);

void consultaUsuario(Arvore *arvore);

void imprimeArvorePreOrdem(Arvore *raiz);

void exibirArvore(Arvore *raiz, char op);



