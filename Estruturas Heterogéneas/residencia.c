/**
Crie um algoritmo que leia os dados de 5000 residências. Os dados incluem o número
de eletrodomésticos, o consumo médio mensal de energia, o consumo de energia do mês
atual, o mês e ano atual, o endereço da residência (rua e número) e o número de
moradores. Os dados deverão ser representados utilizando um registro por residência. 
O algoritmo deverá:

Número de eletrodomesticos:
Ano:
Mês:
Consumo medio mensal:
Consumo do mês atual:
Nome da rua:
Número:
Número de moradores da residência:

ler os dados das 5000 residências;
- listar todos os endereços das residências que apresentam um consumo médio
acima de 100 kWh;
- listar todas o número de moradores das residências que tiveram no mês atual um
consumo superior a 150 kWh.
**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define ANO 2023
#define MES 7
#define QUANT_RESIDENCIAS 5000
#define MAX_CONSUMO_MED 200



typedef struct {
    int num_eletro;
    int ano;
    int mes;
    float consumo_med_mensal;
    float consumo_mes_atual;
    char nome_rua[150];
    int numero;
    int num_moradores;
} Residencia;

Residencia* aloca_residencias() {
        Residencia* residencias;
        residencias = (Residencia *)malloc(sizeof(Residencia));
        if(residencias == NULL) {
            fprintf(stdout, "Erro ao alocar memoria para residencia\n");
            fflush(stdin);
            getchar();
            exit(-1);
        }
    return residencias;
}

void realoca_residencias(Residencia** residencias, int** count) {
    int novo_tamanho = **count + 1;
    printf("entrou em realoca memória\n");
    *residencias = (Residencia*)realloc(*residencias, novo_tamanho * sizeof(Residencia));
    if(*residencias == NULL) {
        printf("Erro ao alocar memoria para residencias\n");
        fflush(stdin);
        free(*residencias);
        *residencias = NULL;
        free(residencias);
        residencias = NULL;
        free(*count);
        *count = NULL;
        getchar();
        exit(-1);
    }
    printf("Alocou memoria, count = %d\n", novo_tamanho);
}

void gera_residencia_aleatoria(Residencia* residencias, int* count) {
    
        residencias[*count - 1].ano = ANO;
        residencias[*count - 1].mes = MES;
        residencias[*count - 1].num_eletro = 10 + rand()%10;
        residencias[*count - 1].num_moradores = 1 + rand()%4;
        residencias[*count - 1].consumo_med_mensal = 30 + rand()%MAX_CONSUMO_MED;
        residencias[*count - 1].consumo_mes_atual = residencias[*count - 1].consumo_med_mensal + rand()%40;
        strcpy(residencias[*count - 1].nome_rua, "Rua algum nome importante");
        residencias[*count - 1].numero = 1 + rand()%2500;
}

void adiciona_residencias(Residencia** residencias, int** count) {
    
        if(**count == 0){
            *residencias = aloca_residencias();
            (**count)++;
        } else if(**count > 0){
            realoca_residencias(residencias, count);
            (**count)++;
        }
        
        printf("count: %d\n", **count);
        gera_residencia_aleatoria(*residencias, *count);

}




void exibe_residencias(Residencia* residencias, int* count) {
    int i;
    printf("Lista de residenciass inseridos:\n");
    for(i = 0; i < *count; i++) {
        printf("\n\nResidencia de índice: %d\n", i);
        printf("Ano: %d\n", residencias[i].ano );
        printf("Mês: %d\n", residencias[i].mes );
        printf("Número de eletrodomesticos: %d\n", residencias[i].num_eletro);
        printf("Número de moradores da residência: %d\n", residencias[i].num_moradores);
        printf("Consumo medio mensal: %.2f\n", residencias[i].consumo_med_mensal);
        printf("Consumo do mês atual: %.2f\n", residencias[i].consumo_mes_atual);
        printf("Nome da rua: %s\n", residencias[i].nome_rua);
        printf("Número Residência: %d\n", residencias[i].numero);
    }
    printf("\n\n");
}

void exibe_residencias_consumo_med_maior_100(Residencia* residencias, int* count) {
    int i;
    printf("Lista de residencias com consumo médio mensal maior que 100KWh:\n");
    for(i = 0; i < *count; i++) {
        if(residencias[i].consumo_med_mensal>100){
            printf("\n\nResidencia de índice: %d\n", i);
            printf("Ano: %d\n", residencias[i].ano );
            printf("Mês: %d\n", residencias[i].mes );
            printf("Número de eletrodomesticos: %d\n", residencias[i].num_eletro);
            printf("Número de moradores da residência: %d\n", residencias[i].num_moradores);
            printf("Consumo medio mensal: %.2f\n", residencias[i].consumo_med_mensal);
            printf("Consumo do mês atual: %.2f\n", residencias[i].consumo_mes_atual);
            printf("Nome da rua: %s\n", residencias[i].nome_rua);
            printf("Número Residência: %d\n", residencias[i].numero);
        }
    }
    printf("\n\n");
}

void exibe_residencias_consumo_atual_maior_150(Residencia* residencias, int* count) {
    int i;
    printf("Lista de residencias com consumo maior que 150KWh:\n");
    for(i = 0; i < *count; i++) {
        if(residencias[i].consumo_mes_atual>150){
            printf("\n\nResidencia de índice: %d\n", i);
            printf("Ano: %d\n", residencias[i].ano );
            printf("Mês: %d\n", residencias[i].mes );
            printf("Número de eletrodomesticos: %d\n", residencias[i].num_eletro);
            printf("Número de moradores da residência: %d\n", residencias[i].num_moradores);
            printf("Consumo medio mensal: %.2f\n", residencias[i].consumo_med_mensal);
            printf("Consumo do mês atual: %.2f\n", residencias[i].consumo_mes_atual);
            printf("Nome da rua: %s\n", residencias[i].nome_rua);
            printf("Número Residência: %d\n", residencias[i].numero);
        }
    }
    printf("\n\n");
}

void libera_residenciass(Residencia* residencias) {
    fflush(stdin);
    // free(*residencias);
    // *residencias = NULL;
    free(residencias);
    residencias = NULL;
}

int main() {
    Residencia* residencias;
    int* count;
    count = (int *)malloc(sizeof(int));
    *count = 0;

    printf("Início\n");
    
    for(int i = 0; i < QUANT_RESIDENCIAS; i++) {
        adiciona_residencias(&residencias, &count);
    }
    printf("adicionou\n");
    
    exibe_residencias(residencias, count);

    exibe_residencias_consumo_med_maior_100(residencias, count);
    exibe_residencias_consumo_atual_maior_150(residencias, count);

    libera_residenciass(residencias);

}