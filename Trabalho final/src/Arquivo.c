#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#include "../include/Logar.h"     // Inclui primeiro Logar.h, que define produto_s e perfis_s
#include "../include/Produtos.h"  // Depois Produtos.h, que depende de produto_s e perfis_s
#include "../include/Menu.h"
#include "../include/Imagens.h"

/*
    char nome[TAM_NOME];
    char id[TAM_ID];
    char email[TAM_MAX_EMAIL];
    char senha[TAM_MAX_SENHA];
    int indentificador;
    int* id_produtos_Vendidos;
    int tam_produtos_Vendidos;
    int* id_produtos_Favoritos;
    int tam_produtos_Favoritos;
*/ 


/*
    int id_produto;
    char nome[TAM_NOME];
    char descricao[TAM_DESC];
    int qntd;
    char identificador_vendedor[TAM_ID];
    char ** Avaliacao;
    int quant_avaliacoes;
    asciiImg_t **imagem;
    int quant_imagens;
*/

void EscreverArquivo(perfis_s * perfis, produto_s * produtos, int n_perfis, int n_produtos) {
    FILE *perfis_a = fopen("perfis.txt", "w");
    FILE *produtos_a = fopen("produtos.txt", "w");

    if (perfis_a == NULL || produtos_a == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    // Escreve perfis
    fprintf(perfis_a, "%d\n", n_perfis);
    for (int i = 0; i < n_perfis; i++) {
        fprintf(perfis_a, "%s %s %s %d %d %d\n", perfis[i].nome, perfis[i].email, perfis[i].id, 
            perfis[i].indentificador, perfis[i].tam_produtos_Vendidos, perfis[i].tam_produtos_Favoritos);
    }

    // Escreve produtos
    fprintf(produtos_a, "%d\n", n_produtos);
    for (int i = 0; i < n_produtos; i++) {
        fprintf(produtos_a, "%s %s %d %d %s %d %d ", produtos[i].nome, produtos[i].descricao, 
            produtos[i].id_produto, produtos[i].qntd, produtos[i].identificador_vendedor, 
            produtos[i].quant_avaliacoes, produtos[i].quant_imagens);

        for (int e = 0; e < produtos[i].quant_imagens; e++) {
            if (produtos[i].imagem[e] == NULL) {
                fprintf(stderr, "Erro: Imagem do produto %d é nula\n", produtos[i].id_produto);
                continue;  // pula essa imagem
            }

            fprintf(produtos_a, "%d ", produtos[i].imagem[e]->nBytes);

            for (int j = 0; j < produtos[i].imagem[e]->nBytes; j++) {
                fprintf(produtos_a, "%02x ", produtos[i].imagem[e]->bytes[j]);
            }
        }

        fprintf(produtos_a, "\n");
    }

    fclose(perfis_a);
    fclose(produtos_a);
}


