#ifndef CALCULADORA_H
#define CALCULADORA_H

#define MAXPILHA 100
#define MAXEXPRESSAO 100
#define PI 3.14

typedef struct {
    double dados[MAXPILHA]; // Expressão na forma pos fixa, como 3 12 4 + *
    int topo;
} Pilha;

typedef struct {
    char dados[MAXPILHA][MAXEXPRESSAO]; // Expressão na forma in fixa, como 3 * (12 + 4)
    int topo;
} PilhaDeStrings;

void inicializarPilha(Pilha *p);
void inicializarPilhaDeStrings(PilhaDeStrings *p);
int pilhaVazia(Pilha *p);
int pilhaDeStringsVazia(PilhaDeStrings *p);
int pilhaCheia(Pilha *p);
int pilhaDeStringsCheia(PilhaDeStrings *p);
void empilhar(Pilha *p, double valor);
void empilharString(PilhaDeStrings *p, char *valor);
double desempilhar(Pilha *p);
char* desempilharString(PilhaDeStrings *p);

char* converterParaPrefixa(const char *expr); // Retorna a forma inFixa de Str (posFixa)
double avaliarRPN(const char *expr); // Calcula o valor de Str (na forma posFixa)


#endif
