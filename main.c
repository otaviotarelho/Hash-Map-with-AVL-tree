//
//  main.c
//  maps_homework_II
//
//  Created by Otavio Tarelho | Mariana Bispo | Guilherme Furtado  on 13/11/17.
//  Copyright © 2017 Otavio Tarelho. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"

#define CPF_LENGTH 15
#define NOME_LENGTH 51
#define FILENAME "/Users/otaviortbarros/Documents/RemakeTree/maps_homework_II/maps_homework_II/Remuneracao_201708.dat"
#define STRUCT_LENGTH sizeof(remuneracao)

typedef struct {
    int id;
    char cpf[CPF_LENGTH];
    char nome[NOME_LENGTH];
    float salario_bruto;
} remuneracao;

void inicializaHashMapComCodigosServidores(FILE * arquivo, hash_map mapa);
int verificaSeServidorEstaNoHashMap(hash_map mapa, int key);
void imprimeInformacoesFuncionarioPeloId(FILE * arquivo, int idServidor, int currentPostion);

int main() {
    FILE * arquivo;
    int idServidor = -1;
    hash_map mapaServidores;
    
    if ((arquivo = fopen(FILENAME, "r")) == NULL) {
        fprintf(stderr, "Erro de abertura do arquivo %s!\n", FILENAME);
        return 1;
    }
    
    map_init(mapaServidores); //Inicializa mapa
    
    inicializaHashMapComCodigosServidores(arquivo, mapaServidores); //Atribui servidores ao mapa
    
    int posicaoServidor = -1;
    while(idServidor != 0) {
        printf("Código servidor: ");
        scanf("%d", &idServidor); //pede o código do servidor a ser procurado

        if(idServidor == 0){ break; }

        posicaoServidor = verificaSeServidorEstaNoHashMap(mapaServidores, idServidor); //procura codigo no mapa
        if(posicaoServidor != -1){ //se encontrou
            imprimeInformacoesFuncionarioPeloId(arquivo, idServidor, posicaoServidor); //imprime informações servidor
        }
        idServidor = -1;
        posicaoServidor = -1;
    }
    
    fclose(arquivo); //fecha o arquivo
    
    return 0;
}

/* Função que grava os codigos dos servidores e sua posição no arquivo em uma mapa */
void inicializaHashMapComCodigosServidores(FILE * arquivo, hash_map mapa){
    remuneracao r;
    printf("Carregando arquivo de servidores..\n");
    map_value i = 0;
    while (fread(&r, STRUCT_LENGTH , 1, arquivo) == 1) {
        map_put(mapa, r.id, i);
        i++;
    }
    printf("Arquivo de servidores carregado com sucesso..\n");
}

/* Função que verifica se o servidor está contido no mapa */
int verificaSeServidorEstaNoHashMap(hash_map mapa, int key){
    map_value * conteudoEncontrado = map_get(mapa, key);
    
    if(conteudoEncontrado != NULL){
        return (*conteudoEncontrado);
    }
    
    printf("Código do servidor digitado não encontrado no arquivo de dados.\n");
    return -1;
}

/* imprime as informações do servidor contidas no arquivo */
void imprimeInformacoesFuncionarioPeloId(FILE * arquivo, int idServidor,int currentPostion){
    remuneracao r;
    
    fseek(arquivo, currentPostion * STRUCT_LENGTH, SEEK_SET);
    if (fread(&r, STRUCT_LENGTH , 1, arquivo) == 1) {
        if(r.id == idServidor){
            printf("%d %s %s %.2f\n", r.id, r.cpf, r.nome, r.salario_bruto);
        }
    }
}
