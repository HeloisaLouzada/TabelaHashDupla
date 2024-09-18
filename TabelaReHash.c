//Heloísa Louzada Borchadrt Gomes - V06

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tab_HashDuplo.h"
#define TAMANHO_NOME 100

//MANIPULAÇÃO DE ARQUIVO
/*void gravarArquivo(Aluno* tabela, char* nomeArquivo, char *modo){
    FILE* arq = fopen(nomeArquivo, modo);
    if (arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i = 0;
    for (i = 0; i < tabela->tamanho; i++){
        Aluno* atual = tabela->tabelaAluno[i];
        while (atual != NULL) {
            fprintf(arq, "%s\n", atual->nome);
            fprintf(arq, "%I64d\n", atual->matricula);
            atual = atual->prox;
        }
    }
    fclose(arq);
}*/


void carregarArquivo(Aluno* tabela, char* nomeArquivo, char *modo){
    FILE* arq = fopen(nomeArquivo, modo);
    if (arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char nome[TAMANHO_NOME];
    long long int matricula;

    while (fgets(nome, sizeof(nome), arq) != NULL){
        nome[strcspn(nome, "\n")] = '\0';  
        
        if (fscanf(arq, "%I64d\n", &matricula) == 1){  
            Aluno* aluno = pesquisar(tabela, matricula, metodoEscolhido);
            if (aluno == NULL) { 
                inserir(tabela, nome, matricula, metodoEscolhido);  
            }
        }    
    }

    fclose(arq);
}

long quantidadeElementos(char *nomeArq){
    FILE *arq = fopen(nomeArq, "rt"); 
    if (arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return -1;  
    }
        
    char nome[TAMANHO_NOME];
    long long int matricula;    
    long quantidade = 0;   

    
    while (fgets(nome, sizeof(nome), arq) != NULL){  
        if (fscanf(arq, "%I64d\n", &matricula) == 1){  
            quantidade++;  
        }
    }

    fclose(arq);  
    printf("\n\n\t\tA quantidade de alunos é:%ld\n", quantidade);

    return quantidade;
}


int escolherTamanho(){
    int opcao;
    printf("\nEscolha o tamanho do vetor Hash:\n");
    printf("1) 100%% do tamanho da base de dados\n");
    printf("2) 120%% do tamanho da base de dados\n");
    printf("3) 150%% do tamanho da base de dados\n");
    scanf("%d", &opcao);

    return opcao;
}


long calculoTamanho(int escolha, int baseDados){   
    int tamanho;
    switch (escolha){
        case 1:
            tamanho = baseDados;
            break;
        case 2:
            tamanho = (baseDados * 120) / 100;
            break;
        case 3:
            tamanho = (baseDados * 150) / 100;
            break;
        default:
            printf("Opção inválida, usando 100%% por padrão.\n");
            tamanho = baseDados;
    }
    
    int i = 0;
    for (i = tamanho;; i++){
        int primo = 1;
        int j = 0;
        for (j = 2; j * j <= i; j++){
            if (i % j == 0) {
                primo = 0;
                break;
            }
        }
        if (primo){
            return i;
        }
    }
}

void inicializarVetor(Aluno * tabela, long indice){
    while(indice > 0){
        tabela[indice]->flag = 0;
        indice --;
    }
}

//FUNÇÕES HASH
long calculoInicial(){
    long indice = 0;

    calculo;

    return indice;
}

long calculoConflito(){
    long indice = 0;

    calculo;

    return indice;
}

long hash(Aluno *tabela ,long long int matricula, long tamanho){
    //calculo inicial -> se a reposta for negativa -> segue para o próximo calculo
    long endereco = 0;
    endereco = calculoInicial(matricula, tamanho);

    if ((tabela[endereco] -> flag) == 0) {
        return calculoInicial(matricula, tamanho);//sai 
    } else {
        endereco = calculoConflito(matricula, tamanho);

        if(tabela[endereco]-> flag) == 0){
            long hash;
        }
    }
}


//FUNÇÕES DO MENU
Aluno* pesquisar(Aluno* tabela, long long int matricula){
    long index = hash(tabela, matricula, tabela->tamanho);
    Aluno* atual = tabela->tabelaAluno[index];
    //while (de calcular até achar)

    while (atual != NULL){
        if (atual->matricula == matricula) {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL;
}

//FUNÇÃO PRINCIPAL
int main(){
    SetConsoleOutputCP(65001);
    long baseDados = quantidadeElementos("nomes_matriculas.txt");
    long escolhaTamanho = escolherTamanho();
    long tamanhoVetor = calculoTamanho(escolhaTamanho, baseDados);

    Aluno tabela[tamanhoVetor];
    inicializarVetor(tabela, tamanhoVetor);

    carregarArquivos(tabela, "nomes_matriculas.txt", "rt");

    return 0;
}