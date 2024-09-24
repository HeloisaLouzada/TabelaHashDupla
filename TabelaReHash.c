//Heloísa Louzada Borchadrt Gomes - V06

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "Tab_HashDuplo.h"

#define TAMANHO_NOME 100
#define A 0.6180339887 


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


void carregarArquivo(Aluno* tabela, char* nomeArquivo, char *modo, long tamanho){
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
            Aluno* aluno = pesquisar(tabela, matricula, tamanho);
            if (aluno == NULL) { 
                inserir(tabela, matricula, nome, tamanho);  
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
    printf("1) 120%% do tamanho da base de dados\n");
    printf("2) 150%% do tamanho da base de dados\n");
    printf("3) 180%% do tamanho da base de dados\n");
    scanf("%d", &opcao);

    return opcao;
}


long calculoTamanho(int escolha, int baseDados){   
    int tamanho;
    switch (escolha){
        case 1:
            tamanho = (baseDados * 120)/100;
            break;
        case 2:
            tamanho = (baseDados * 150) / 100;
            break;
        case 3:
            tamanho = (baseDados * 180) / 100;
            break;
        default:
            printf("Opção inválida, usando 120%% por padrão.\n");
            tamanho = (baseDados * 120)/100;
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
        tabela[indice].flag = 0;
        indice --;
    }
}

//FUNÇÕES HASH
long calculoInicial(long long int matricula, long tamanho){
    double val = matricula * A;  
    val = val - (long long int)val;      
    return (long)(tamanho * val); 
}

long calculoConflito(long long int matricula, long tamanho){
    long indice = 0;

    indice = 1 + calculoInicial(matricula, (tamanho-1));

    return indice;
}

long hash(Aluno *tabela ,long long int matricula, long tamanho){
    //calculo inicial -> se a reposta for negativa -> segue para o próximo calculo
    long endereco = 0;
    endereco = calculoInicial(matricula, tamanho);

    if ((tabela[endereco].flag) == 0) {
        return calculoInicial(matricula, tamanho);//sai 
    } else {
        while((tabela[endereco].flag) != 0){
            calculoConflito(matricula, tamanho);
        }
    }
}


//FUNÇÕES DO MENU

inserir(Aluno* tabela, long long int matriculaAluno, char * nomeAluno, long tamanho){
    long posicao = hash(tabela, matriculaAluno, tamanho);

    tabela[posicao].flag = 0;
    tabela[posicao].nome = nomeAluno;
    tabela[posicao].matricula = matriculaAluno;

}


Aluno* pesquisar(Aluno** tabela, long long int matricula, long tamanho){
    long index = hash(tabela, matricula, tamanho);
    Aluno* atual = tabela[index];
    
    if (atual != NULL){
        if (atual->matricula == matricula) {
            return atual;
        }
        else
        printf("O valor não existe");
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

    carregarArquivo(tabela, "nomes_matriculas.txt", "rt", tamanhoVetor);

    return 0;
}