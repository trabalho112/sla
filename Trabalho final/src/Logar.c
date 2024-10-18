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



int* RealocaInt(int tamanho, int* vetor){

    vetor = (int*)realloc(vetor, tamanho*sizeof(int));

    return vetor; 
}

char** RealocaChar(int tamanho, char** vetor) {
    
    vetor = (char**)realloc(vetor, tamanho * sizeof(char*));

    return vetor;
}

perfis_s* Reallocarperfis(int n_perfis, perfis_s* perfis){
    
    perfis = (perfis_s*)realloc(perfis, n_perfis*sizeof(perfis_s));

    return perfis;
}

void CadastrarPerfil(perfis_s* perfis, int n_perfis){
    int erro, arroba;

    perfis[n_perfis-1].tam_produtos_Vendidos = 0;
    perfis[n_perfis-1].id_produtos_Vendidos = NULL;
    perfis[n_perfis-1].tam_produtos_Favoritos = 0;
    perfis[n_perfis-1].id_produtos_Favoritos = NULL;


    perfis[n_perfis-1].indentificador = n_perfis;

    printf("Diga o nome: ");
    fgets(perfis[n_perfis-1].nome, TAM_NOME, stdin);  
    perfis[n_perfis-1].nome[strcspn(perfis[n_perfis-1].nome, "\n")] = '\0';

    do
    {
        erro = 0;
        arroba = 0;
        printf("Diga o email: ");
    
        fgets(perfis[n_perfis-1].email, TAM_MAX_EMAIL, stdin);  
        perfis[n_perfis-1].email[strcspn(perfis[n_perfis-1].email, "\n")] = '\0';

        for(int i=1; i<n_perfis; i++){

            if(strcmp(perfis[n_perfis-1].email, perfis[i-1].email) == 0){
                erro = 1;
                printf("Email ja utilizado por outro usario. Tente novamente!\n");
            }
       }

        for(int i=0; i<=TAM_MAX_EMAIL; i++){

            if(perfis[n_perfis-1].email[i] == '@'){
                    arroba = 1;   
                }
        }

        if (arroba != 1) printf("Email invalido, '@' nao encontrado. Tente novamente!\n");
        

    } while (erro == 1 || arroba != 1);
    
    

    do{
        erro = 1;

        printf("Diga o ID: ");

        fgets(perfis[n_perfis-1].id, TAM_ID, stdin);
        perfis[n_perfis-1].id[strcspn(perfis[n_perfis-1].id, "\n")] = '\0';

        for(int i=1; i<n_perfis; i++){

            if(strcmp(perfis[n_perfis-1].id, perfis[i-1].id) == 0){
                erro = 0;
                printf("ID ja utilizado por outro usario. Tente novamente!\n");
            }
        }
    }while (erro == 0);

    printf("Diga a senha: ");
    fgets(perfis[n_perfis-1].senha, TAM_MAX_SENHA, stdin);  
    perfis[n_perfis-1].senha[strcspn(perfis[n_perfis-1].senha, "\n")] = '\0';

    
}

void ImprimirDados(perfis_s* perfis, int n_perfis){


    printf("|%-*s|%-*s|%-*s|\n", TAM_NOME,"Nome_perfil",TAM_MAX_EMAIL, "email",TAM_ID, "Id");

    for (int i = 0; i < n_perfis; i++){

        printf("|%-50s|%-50s|%-20s|\n", perfis[i].nome, perfis[i].email, perfis[i].id);

    }

}

int LogarComId(perfis_s* perfis, int n_perfis){
    char ID[TAM_ID];
    char Senha[TAM_MAX_SENHA];
    while (1){
    
    printf("Diga o ID(0 para sair): ");
    fgets(ID, TAM_ID, stdin); 
    ID[strcspn(ID, "\n")] = '\0';

    for(int i=0; i < n_perfis; i++){
        if(strcmp(ID, perfis[i].id) == 0){
            printf("Diga a senha: ");
            fgets(Senha, TAM_MAX_SENHA, stdin); 
            Senha[strcspn(Senha, "\n")] = '\0';

            if (strcmp(Senha, perfis[i].senha) == 0)
            {
                return i;
            }else printf("senha incorreta\n");
            
            
        }
    }

    if (ID[0] == '0'){
            return -1;
    }
        
        
        printf("cadastro invalido, tente novamente\n");
    }
    

    
}

int LogarComEmail(perfis_s* perfis, int n_perfis){
    char Email[TAM_MAX_EMAIL], Senha[TAM_MAX_SENHA];
    while (1){
    
    printf("Diga o Email(0 para sair): ");
    fgets(Email, TAM_MAX_EMAIL, stdin); 
    Email[strcspn(Email, "\n")] = '\0';

    for(int i=0; i < n_perfis; i++){
        if(strcmp(Email, perfis[i].email) == 0){
            printf("Diga a senha: ");
            fgets(Senha, TAM_MAX_SENHA, stdin); 
            Senha[strcspn(Senha, "\n")] = '\0';

            if (strcmp(Senha, perfis[i].senha) == 0)
            {
                return i;
            }else printf("senha incorreta\n");
            
            
        }
    }

    if (Email[0] == '0'){
            return -1;
    }
        
        
        printf("Login invalido, tente novamente\n");
    }
    

    
}

void Logar(perfis_s * perfis, int n_perfis){
    
    int opcao;
    int cadastrado;
    int n_logado;

    

    do{
        printf("Qual opcao voce deseja?\n");
        printf("\t1 - Logar com ID\n");
        printf("\t2 - Logar com Email\n");
        printf("\t0 - Nao cadastrar\n");
        scanf("%d%*c", &opcao);

        switch (opcao){

            case 1:
                n_logado = LogarComId(perfis, n_perfis);
                if(n_logado == -1){
                    return;
                }
                opcao = MenuLogado(perfis, n_perfis, n_logado);
                break;

            case 2:
                n_logado = LogarComEmail(perfis, n_perfis);
                if(n_logado == -1){
                    return;
                }
                opcao = MenuLogado(perfis, n_perfis, n_logado);
                break;    

            case 0:

                printf("ate!\n");
                return;
                
            default:
                printf("opcao invalida\n");
                break;
        }

    }while(opcao!=0);
}

