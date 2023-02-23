#include <stdlib.h>
#include <stdio.h>

typedef struct no
{
    int conteudo;
    struct no *esquerda, *direita;

} No;

No *inserir(No *raiz, int valor)
{
    if (raiz == NULL)
    { // raiz nula
        No *novo = (No *)malloc(sizeof(No));

        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }
    else
    {                               // raiz não nula
        if (raiz->conteudo > valor) // raiz = 10, valor = 9, 9 será inserido a esquerda do 10
        {
            raiz->esquerda = inserir(raiz->esquerda, valor); // recursão
        }
        if (raiz->conteudo < valor) // raiz = 9, valor = 10, 10 será inserido a direita do 9
        {
            raiz->direita = inserir(raiz->direita, valor);
        }
        return raiz; // retorna o ultimo valor adicionado a arvore
    }
}

No *remover(No *raiz, int chave)
{
    if (raiz == NULL)
    {
        printf("\n ------ Valor nao encontrado ------ \n\n");
        return NULL;
    }
    else
    {
        if (raiz->conteudo == chave) // se a chave for igual ao conteudo da raiz
        {
            // verificamos se a esquerda "E" a direita são nulos, sendo assim uma folha
            if (raiz->esquerda == NULL && raiz->direita == NULL) // para nós que não possuem filhos
            {
                printf("\n ------ Valor removido ------ \n\n");
                free(raiz);
                return NULL;
            }
            else // caso possua um filho a direita "OU" a esquerda
            {
                // verificamos se a esquerda é nula "OU" a direita é nula, pois o que entrar no if, vai passar
                if (raiz->esquerda == NULL || raiz->direita == NULL) // para nós que possuem apenas um filho
                {
                    No *aux;
                    if (raiz->esquerda != NULL)
                    {
                        aux = raiz->esquerda; // aux receberá a referencia da raiz->esquerda, para liberar a memoria da raiz
                    }
                    else
                    {
                        aux = raiz->direita;
                    }
                    printf("\n ------ Valor removido ------ \n\n");
                    free(raiz);
                    return aux; // retornando o valor que a variavel pegou como referencia, seja da direita ou da esquerda
                }
                else // para nós que possuem dois filhos, seria raiz->esquerda && raiz->direita != NULL
                {
                    No *aux = raiz->esquerda;    // indo para subarvore a esquerda
                    while (aux->direita != NULL) // e pegando o valor mais a direita
                    {
                        aux = aux->direita; // para percorrer a raiz->direita
                    }
                    raiz->conteudo = aux->conteudo; // trocando a posição do nò que vai remover. para o ultimo a direita
                    aux->conteudo = chave;          // aux vai receber o valor da chave que deseja remover
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }
            }
        }
        else
        {
            if (chave < raiz->esquerda)
            {
                raiz->esquerda = remover(raiz->esquerda, chave); // raiz->esquerda irá receber o retorno da recursão
            }
            else
            {
                raiz->direita = remover(raiz->direita, chave);
            }
            return raiz;
        }
    }
}

void inOrder(No *raiz)
{

    if (raiz != NULL)
    {
        inOrder(raiz->esquerda);
        printf("[%d] ", raiz->conteudo);
        inOrder(raiz->direita);
    }
}

int tamanho(No *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita); // recursão para pegar a quantidade de nós na esquerda e direita
    }
}

int buscarValor(No *raiz, int chave)
{
    if (raiz == NULL)
    {
        return 0; // retorno binario
    }
    else
    {
        if (raiz->conteudo == chave)
        {
            return 1;
        }
        else
        {
            if (chave < raiz->conteudo)
            {
                return buscarValor(raiz->esquerda, chave);
            }
            if (chave > raiz->conteudo)
            {
                return buscarValor(raiz->direita, chave);
            }
        }
    }
}

int altura(No *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        int esquerda = altura(raiz->esquerda);
        int direita = altura(raiz->direita);
        if (esquerda > direita)
        {
            return esquerda + 1;
        }
        else
        {
            return direita + 1;
        }
    }
}

int somatorio(No *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    else
    {
        int soma = raiz->conteudo + somatorio(raiz->esquerda) + somatorio(raiz->direita);
        return soma;
    }
}

void primos(No *raiz)
{
    if (raiz == NULL)
    { // Se a raiz for nula, não há nada para ser mostrado, então retorna
        return NULL;
    }
    else if (ePrimo(raiz->conteudo))
    {                                    // Verifica se o número é primo chamando a função ePrimo
        printf("[%d] ", raiz->conteudo); // Se for primo, imprime o número
    }
    primos(raiz->esquerda); // Chama a função recursivamente para a subarvore esquerda
    primos(raiz->direita);  // Chama a função recursivamente para a subarvore direita
}

int ePrimo(int num)
{
    if (num < 2)
    { // Se o número for menor que 2, não é primo
        return 0;
    }
    for (int i = 2; i <= num / 2; i++)
    { // Verifica se o número é divisível por algum número entre 2 e num/2
        if (num % i == 0)
        { // Se for divisível, não é primo
            return 0;
        }
    }
    return 1; // Se não for divisível por nenhum número, é primo
}

void pares(No *raiz)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    else if (raiz->conteudo % 2 == 0)
    {
        printf("[%d] ", raiz->conteudo);
    }
    pares(raiz->esquerda);
    pares(raiz->direita);
}

void impares(No *raiz)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    else if (raiz->conteudo % 2 != 0)
    {
        printf("[%d] ", raiz->conteudo);
    }
    impares(raiz->esquerda);
    impares(raiz->direita);
}

int main()
{
    int op, valor;
    No *raiz = NULL; // criando a árvore nula
    do
    {
        printf("1 - Inserir\n2 - inOrder\n3 - Buscar Valor\n4 - Remover\n5 - Altura\n6 - Somatorio\n7 - Primos\n8 - Pares\n9 - Impares\n10 - Sair\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("Informe um valor: ");
            scanf("\n%d", &valor);
            raiz = inserir(raiz, valor);
            break;
        case 2:
            printf(" ------ Arvore Binaria ------\n\n");
            inOrder(raiz);
            printf("\n\nTamanho da Arvore: %d\n\n", tamanho(raiz));
            break;
        case 3:
            printf("Informe o valor que deseja buscar: ");
            scanf("%d", &valor);

            if (buscarValor(raiz, valor) == 0)
            {
                printf("\nO valor nao foi encontrado na arvore!\n\n");
            }
            else
            {
                printf("\nO valor foi encontrado na arvore!\n\n");
            }
            break;
        case 4:
            printf(" ------ Arvore Binaria ------\n\n");
            inOrder(raiz);
            printf("\n\nInforme o valor que deseja remover: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 5:
            printf("\nA Altura da Arvore e: %d\n\n", altura(raiz));
            break;
        case 6:
            printf("\nO resultado da soma de todos os valores e: [%d]\n\n", somatorio(raiz));
            break;
        case 7:
            printf("\nOs numeros primos sao: ");
            primos(raiz);
            printf("\n\n");
            break;
        case 8:
            printf("\nOs numeros pares sao: ");
            pares(raiz);
            printf("\n\n");
            break;
        case 9:
            printf("\nOs numeros impares sao: ");
            impares(raiz);
            printf("\n\n");
            break;
        default:
            break;
        }
    } while (op != 10);
    printf("Saindo .....");
}