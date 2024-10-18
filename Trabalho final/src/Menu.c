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
#include "../include/Favoritos.h"
#include "../include/Arquivo.h"

int MenuLogado(perfis_s* perfis, int n_perfis, int n_logado){

    int opcao;

    
    produto_s* produtos = NULL;
    int n_produtos = 0;
    char id_vendedor[TAM_ID];
    

    do{
        printf("Qual opcao voce deseja?\n");
        printf("\t1 - Favoritar Produto\n");
        printf("\t2 - Lista os produtos favoritos\n");
        printf("\t3 - Avaliar produto\n");
        printf("\t4 - Cadastrar produto\n");
        printf("\t5 - Listar produtos\n");
        printf("\t6 - Listar produtos de um vendedor\n");
        printf("\t7 - Listar Avaliacoes de um produto\n");
        printf("\t8 - Adicionar imagem a um produto\n");
        printf("\t9 - Desfavoritar Produto\n");
        printf("\t0 - Sair\n");
        scanf("%d%*c", &opcao);

        switch (opcao){

            case 1:
                FavoritaProd(produtos, n_produtos, perfis, n_perfis);
                break;

             case 9:
                DeletaProd(produtos, n_produtos, perfis, n_perfis);
                break;

            case 2:
                ImprimeFavoritos(perfis);
                break;   

            case 3:

                AvaliarProduto(produtos, n_produtos);
                break; 
            
            case 4:
                n_produtos++;
                produtos = RealocProd(n_produtos,produtos);
                CadastrarProduto(produtos,n_produtos,perfis,n_perfis, n_logado);
            break;

            case 5:
                if(n_produtos == 0){

                    printf("Nenhum produto cadastrado!\n");
                    continue;
                }

                ListarProdutos(produtos, n_produtos);
            break;

            case 6: 
            
                if(n_produtos == 0){

                    printf("Nenhum produto cadastrado!\n");
                    continue;
                }

                printf("Digite o ID do vendedor: ");
                fgets(id_vendedor, TAM_ID, stdin);
                id_vendedor[strcspn(id_vendedor, "\n")] = '\0';

                ListarProdutosPorVendedor(produtos, n_produtos, id_vendedor);

            break;

            case 7: 
            
                ListarAvaliacoes(produtos, n_produtos);

            break;

             case 8: {
                int Id;
                char url[256];
                bool continuar = false;
                bool colorido;
                int largura; 
                char escolha;

                do {
                    printf("qual produto voce deseja adicionar imagem? Digite o Id do produto (0 para listar os produtos)\n :");
                    scanf("%d%*c", &Id);

                     continuar = (Id == 0);

                    if (continuar) {
                        ListarProdutos(produtos, n_produtos);
                    }else{

                    for (int i = 0; i < n_produtos; i++) {
                        if (Id == produtos[i].id_produto) {
                            produtos[i].quant_imagens++;
                            produtos[i].imagem = ReallocarImagem(produtos[i].imagem, produtos[i].quant_imagens);
                            printf("Escreva o url da imagem\n :");
                            fgets(url, sizeof(url), stdin);
                            url[strcspn(url, "\n")] = '\0'; // Remove o '\n'

                            printf("Imagem Colorida?(s ou n)\n :");
                            scanf(" %c ", &escolha); // O espaço antes de %c ignora espaços em branco

                            colorido = (escolha == 's');

                            printf("Qual a largura da imagem?\n :");
                            scanf("%d%*c", &largura);

                            produtos[i].imagem[produtos[i].quant_imagens - 1] = insta_carregaImagem(url, colorido, largura);

                            if (produtos[i].imagem[produtos[i].quant_imagens - 1] == NULL) {
                                printf("Falha ao carregar a imagem!\n");
                            } else {
                                printf("Imagem carregada com sucesso!\n");
                            }
                        }
                    }}   
                } while (continuar);

                break;
            }
            
            case 0:

                printf("ate!\n");
                EscreverArquivo(perfis, produtos, n_perfis, n_produtos);
                return 0;
                
            default:
                printf("opcao invalida\n");
            break;
        }

    }while(opcao!=0);


    return 0;

}

void MenuCadastro(){

    
    perfis_s* perfis= NULL;
    char id_vendedor[TAM_ID];
    int n_perfis = 0, n_produtos = 0;
    int opcao;

////    FILE * perfil_a;

  //  perfil_a = fopen ("perfils.txt","a");

   // perfis = LerNumperfis(perfis);
   // n_perfis = LerArquivo(perfis);
    

    do{
        printf("Qual opcao voce deseja?\n");
        printf("\t1 - Cadastrar perfil\n");
        printf("\t2 - Imprimir Perfis\n");
        printf("\t3 - Logar\n");
        printf("\t0 - Sair\n");
        scanf("%d%*c", &opcao);

        switch (opcao)
        {
        case 1:
            n_perfis++;
            perfis = Reallocarperfis(n_perfis, perfis);
            CadastrarPerfil(perfis, n_perfis);
            
            break;

        case 2:
            if (n_perfis>0)
            {
            ImprimirDados(perfis, n_perfis);
            }else
            {
                printf("nenhum perfil cadastrado!\n");
            }
            
            break;
        case 3:

            Logar(perfis, n_perfis);

            break;
       
        case 0:
            printf("Tchau!\n");
            break;
        default:
            break;
        }
    }while(opcao != 0);
  //  fclose(perfil_a);

    
    free(perfis);
}

