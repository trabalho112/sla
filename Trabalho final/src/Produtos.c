#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../include/Logar.h"     // Inclui primeiro Logar.h, que define produto_s e perfis_s
#include "../include/Produtos.h"  // Depois Produtos.h, que depende de produto_s e perfis_s
#include "../include/Menu.h"
#include "../include/Imagens.h"


produto_s* RealocProd(int n_prod, produto_s* produtos){

    produtos = (produto_s*)realloc(produtos, n_prod*sizeof(produto_s));

    return produtos;
}

void CadastrarProduto(produto_s* produtos, int n_produtos, perfis_s* perfis, int n_perfis,int n_logado) {
    produtos[n_produtos - 1].id_produto = n_produtos;

    printf("Digite o nome do produto: \n");
    fgets(produtos[n_produtos - 1].nome, TAM_NOME, stdin);
    produtos[n_produtos - 1].nome[strcspn(produtos[n_produtos - 1].nome, "\n")] = '\0';

    printf("Digite uma breve descricao do produto:\n");
    fgets(produtos[n_produtos - 1].descricao, TAM_DESC, stdin);
    produtos[n_produtos - 1].descricao[strcspn(produtos[n_produtos - 1].descricao, "\n")] = '\0';

    printf("Digite a quantidade desse produto\n");
    scanf("%d", &produtos[n_produtos - 1].qntd);
    getchar();

    printf("Insira o ID do usuario a qual esse produto pertence: \n");
    fgets(produtos[n_produtos - 1].identificador_vendedor, TAM_ID, stdin);
    produtos[n_produtos - 1].identificador_vendedor[strcspn(produtos[n_produtos - 1].identificador_vendedor, "\n")] = '\0';


 //   strcpy(produtos[n_produtos-1].identificador_vendedor, perfis[n_logado].id);

    perfis_s* perfilEscolhido = NULL;

    for (int i = 0; i < n_perfis; i++) {
        if (strcmp(perfis[i].id, produtos[n_produtos - 1].identificador_vendedor) == 0) {

            perfilEscolhido = &perfis[i];
            break;
        }
    }
 }

void ListarProdutos(produto_s* produtos, int n_produtos) {

    printf("Lista de produtos cadastrados:\n");

    for (int i = 0; i < n_produtos; i++) {

        printf("ID: %d \n| Nome: %s \n| Descricao: %s \n| Quantidade: %d \n| ID Vendedor: %s\n", produtos[i].id_produto, produtos[i].nome, produtos[i].descricao, produtos[i].qntd, produtos[i].identificador_vendedor);
        printf("\nImagens:\n");
        for (int e = 0; e < produtos[i].quant_imagens; e++) {
            if (produtos[i].imagem[e] != NULL) {
                printf("\n--- Imagem %d ---\n", e + 1);
                insta_imprimeImagem(produtos[i].imagem[e]);
            }else printf("\n--- Imagem %d não foi carregada corretamente ---\n", e + 1);

        printf("\n------------------------------------------------------------------------------------------\n\n");
            
    }
    
    }
}

void ListarProdutosPorVendedor(produto_s* produtos, int n_produtos, const char* id_vendedor) {


    printf("Produtos do vendedor com ID %s:\n", id_vendedor);

    int encontrado = 0;

    for (int i = 0; i < n_produtos; i++) {
        if (strcmp(produtos[i].identificador_vendedor, id_vendedor) == 0) {

            printf("|ID: %d \n|Nome: %s \n|Descricao: %s \n|Quantidade: %d\n\v", produtos[i].id_produto, produtos[i].nome, produtos[i].descricao, produtos[i].qntd);

            encontrado = 1;
        }
    }

    if (!encontrado) {

        printf("Nenhum produto encontrado para este vendedor.\n");
    }
}

void AvaliarProduto(produto_s* produtos, int n_produtos){

    int Id;
    char Avaliacao[TAM_DESC];
    bool continuar;

    do
    {

        printf("qual produto voce deseja avaliar? Digite o Id do produto (-1 para listar os produtos)\n :");
        scanf("%d%*c", &Id);

        continuar = (Id == -1);

        if (continuar)
        {
            ListarProdutos(produtos, n_produtos);}

        for (int i = 0; i < n_produtos; i++)
        {
            if(Id == produtos[i].id_produto){
                produtos[i].quant_avaliacoes++;
                produtos[i].Avaliacao = RealocaChar(produtos[i].quant_avaliacoes, produtos[i].Avaliacao);
                printf("Escreva a avaliacao do %s\n :", produtos[i].nome);
                fgets(produtos[i].Avaliacao[produtos[i].quant_avaliacoes-1], TAM_DESC, stdin);
                produtos[i].Avaliacao[produtos[i].quant_avaliacoes-1][strcspn(produtos[i].Avaliacao[produtos[i].quant_avaliacoes-1], "\n")] = '\0';


            }
        }
    }while(continuar);


}

void ListarAvaliacoes(produto_s* produtos, int n_produtos){

    int id;
    bool continuar;
    
    do
    {
    
    

        printf("\tQual o id do produto voce gostaria de ver as avaliacoes? (-1 para listar os produtos)\n :");
        scanf("%d%*c", &id);

        continuar = (id == -1);

        if (continuar)
        {
            ListarProdutos(produtos, n_produtos);
        
        }else{
    

            for (int i = 0; i < n_produtos; i++)
            {
                if(id == produtos[i].id_produto){
                    for (int e = 0; e < produtos[i].quant_avaliacoes; i++)
                    {
                        if (produtos[i].quant_avaliacoes > 0)
                        {
                            printf("Avaliacao %d : %s\v\n", e+1, produtos[i].Avaliacao[e]);
                        }else{
                            printf("Esse produto nao tem avaliacoes\n");
                        }
                
                
                    }
            

                }else printf("Id nao encontrado\n");
            }   
        }

    } while (continuar);
}
