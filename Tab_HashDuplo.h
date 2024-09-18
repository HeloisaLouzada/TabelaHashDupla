#define TAMANHO 100
//typedef char string[TAMANHO];

typedef struct Aluno{
    char nome[TAMANHO];
    long long int matricula;
    int flag;
} Aluno;


void gravarArquivo(Aluno* tabela, char* nomeArquivo, char *modo);

void carregarArquivo(Aluno* tabela, char* nomeArquivo, char *modo, long tamanhoVetor);

long quantidadeElementos(char *nomeArq);

inserir(Aluno* tabela, long long int matriculaAluno, char* nomeAluno, long tamanho);

Aluno* pesquisar(Aluno** tabela, long long int matricula, long tamanho);