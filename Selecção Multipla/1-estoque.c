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

void adiciona_produto(Produtos** produtos, int** count, int quantidade_produto, char nome_produto[101]) {
    if(**count > 0){
        realoca_produtos(produtos, count);
    }
    strcpy((*produtos)[**count].nome, nome_produto);
    (*produtos)[**count].quantidade = quantidade_produto;
    (**count)++;
    printf("count adiciona_produto: %d\n", **count);
    //return produtos;
}

void exibe_produtos(Produtos *produtos, int* count) {
    int i;
    printf("Lista de produtos inseridos:\n");
    for(i = 0; i < *count; i++) {
        printf("%s, quant.: %d\n", produtos[i].nome, produtos[i].quantidade);
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
        printf("var nome %s\n", nome_produto);

        printf("Digite a quantidade a ser inserida deste produto:\n");
        scanf("%i", &quantidade_produto);
        printf("var quant: %d\n", quantidade_produto);

        adiciona_produto(produtos, count, quantidade_produto, nome_produto);

        printf("Deseja inserir mais um produto: s (Sim) / n (Não)\n");
        scanf("%1s", &opcao_add);

        resposta = le_resposta(opcao_add);
    }
}

int main() {

    int* count;
    Produtos* produtos;
    produtos = aloca_produto();  
    count = (int *)malloc(sizeof(int));
    *count = 0;

    inserir_produtos_no_estoque(&produtos, &count);

    exibe_produtos(produtos, count);

    libera_produtos(&produtos);

    fflush(stdin);

}