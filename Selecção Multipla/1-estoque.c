/** 
1 - Escreva um programa que informe se existe estoque para atender um pedido feito a uma fábrica. 
O programa deverá receber como entradas o número de itens em estoque e o número de itens a serem fornecidos, 
e dará como saída o estoque atualizado ou uma mensagem indicando não haver itens suficientes em estoque para atender o pedido.

Escreva um programa que 
informe se existe estoque para atender um pedido
receber como entradas o número de itens em estoque 
número de itens a serem vendidos, 

saída o estoque atualizado
ou uma mensagem indicando não haver itens suficientes em estoque para atender o pedido.
*/

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


 typedef struct {
    char nome[101];
    int quantidade;
 } Produtos;

bool le_resposta(char escolha[2]) {
    return strncmp(escolha, "s", 1) == 0;
}

Produtos* aloca_produto() {
        Produtos* produtos;
        produtos = (Produtos *)malloc(sizeof(Produtos));
        if(produtos == NULL) {
            fprintf(stdout, "Erro ao alocar memoria para produtos\n");
            fflush(stdin);
            getchar();
            exit(-1);
        }
    return produtos;
}

void realoca_produtos(Produtos** produtos, int** count) {
    int novo_tamanho = **count + 1;
    printf("entrou em realoca memória\n");
    *produtos = (Produtos *)realloc(*produtos, novo_tamanho * sizeof(Produtos));
    if(*produtos == NULL) {
        printf("Erro ao alocar memoria para produtos\n");
        fflush(stdin);
        free(*produtos);
        *produtos = NULL;
        free(produtos);
        produtos = NULL;
        free(*count);
        *count = NULL;
        getchar();
        exit(-1);
    }
    printf("Alocou memoria, count = %d\n", novo_tamanho);
}

int encontra_produto(Produtos* produtos, int* count, char nome_produto[101]) {
    for(int i = 0 ; i < *count ; i++) {
        if(strcmp(produtos[i].nome, nome_produto)==0) {
            return i;
        }
    }
    return -1;
}

//Função ainda não reconhece produtos já existentes
void adiciona_produto(Produtos** produtos, int** count, int quantidade_produto, char nome_produto[101]) {
    int index_produto = -1;
    index_produto = encontra_produto(*produtos, *count, nome_produto);
    
    if(index_produto == -1){
        if(**count > 0){
            realoca_produtos(produtos, count);
        }
        strcpy((*produtos)[**count].nome, nome_produto);
        (*produtos)[**count].quantidade = quantidade_produto;
        (**count)++;
    } else {
        (*produtos)[index_produto].quantidade += quantidade_produto;
    }
}

void exibe_produtos(Produtos *produtos, int* count) {
    int i;
    printf("Lista de produtos inseridos:\n");
    for(i = 0; i < *count; i++) {
        printf("Índice: %d: %s, quant.: %d\n", i+1, produtos[i].nome, produtos[i].quantidade);
    }
    printf("\n");
}

void libera_produtos(Produtos** produtos) {
    fflush(stdin);
    free(*produtos);
    *produtos = NULL;
    free(produtos);
    produtos = NULL;
}

void inserir_produtos_no_estoque(Produtos** produtos, int** count) {
    bool resposta = true;
    while(resposta) { 
        char nome_produto[101];
        int quantidade_produto;
        char opcao_add[2];

        printf("Digite um nome para o produto:\n");
        scanf(" %100[^\n]", nome_produto);

        printf("Digite a quantidade a ser inserida deste produto:\n");
        scanf("%i", &quantidade_produto);

        adiciona_produto(produtos, count, quantidade_produto, nome_produto);

        printf("Deseja inserir mais um produto: s (Sim) / n (Não)\n");
        scanf("%1s", &opcao_add);

        resposta = le_resposta(opcao_add);
    }
}

void subtrair_produto(Produtos** produtos, int** count, int index, int quantidade) {
    index--;
    if((index)<=**count) {
        if(quantidade <= (*produtos)[index].quantidade){
            (*produtos)[index].quantidade-=quantidade;
            printf("Produto %s: Atualizado, quantidade atual: %d\n", (*produtos)[index].nome, (*produtos)[index].quantidade);
        } else {
            printf("Quantidade inválida.\n");
        }
    } else {
        printf("Índice inválido.\n");
    }
}

void fornecer_produto(Produtos** produtos, int** count) {
    bool resposta = true;
    int index = 0;
    char opcao[2];;
    int quantidade = 0;
    while(resposta) { 
        exibe_produtos(*produtos, *count);

        printf("Diga o código do produto que deseja fornecer:\n");
        scanf("%d", &index);
        printf("Digite a quantidade do produto que deseja fornecer:\n");
        scanf("%d", &quantidade);

        if(index>0){
            subtrair_produto(produtos, count, index, quantidade);
        } else {
            printf("Produto inválido\n");
        }

        printf("Deseja fornecer mais um produto: s (Sim) / n (Não)\n");
        scanf("%1s", &opcao);

        resposta = le_resposta(opcao);
    }

}

int main() {
    int* count;
    bool resposta = true;
    Produtos* produtos;
    produtos = aloca_produto();  
    count = (int *)malloc(sizeof(int));
    *count = 0;

    while(true){
        char opcao[2];
        int index = 0;
        printf("Digite o índice do que deseja fazer\n...\n");
        printf("1 - Inserir produtos no estoque\n");
        printf("2 - Fornecer produtos do estoque\n");
        printf("3 - Exibir produtos do estoque\n");
        printf("0 - Sair\n");
        scanf("%d", &index);

        switch(index){
            case 0:
                printf("Até mais!\n");
                exit(0);
            case 1:
                inserir_produtos_no_estoque(&produtos, &count);
                break;
            case 2:
                fornecer_produto(&produtos, &count);
                break;
            case 3:
                exibe_produtos(produtos, count);
                break;
            default:
                printf("Entrada Inválida.\n");
        }
    }

    libera_produtos(&produtos);

    fflush(stdin);

}