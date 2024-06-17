// calculadora.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "calculadora.h"

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

void inicializarPilhaDeStrings(PilhaDeStrings *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaDeStringsVazia(PilhaDeStrings *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAXPILHA - 1;
}

int pilhaDeStringsCheia(PilhaDeStrings *p) {
    return p->topo == MAXPILHA - 1;
}

void empilhar(Pilha *p, double valor) {
    if (!pilhaCheia(p)) {
        p->dados[++(p->topo)] = valor;
    } else {
        printf("Pilha cheia!\n");
    }
}

void empilharString(PilhaDeStrings *p, char *valor) {
    if (!pilhaDeStringsCheia(p)) {
        strcpy(p->dados[++(p->topo)], valor);
    } else {
        printf("Pilha cheia!\n");
    }
}

double desempilhar(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->dados[(p->topo)--];
    } else {
        printf("Pilha vazia!\n");
        return 0.0;
    }
}

char* desempilharString(PilhaDeStrings *p) {
    if (!pilhaDeStringsVazia(p)) {
        return p->dados[(p->topo)--];
    } else {
        printf("Pilha vazia!\n");
        return NULL;
    }
}

double avaliarRPN(const char *expr) {
    Pilha pilha;
    inicializarPilha(&pilha);

    char exprCopia[MAXEXPRESSAO];
    strcpy(exprCopia, expr);

    char *token = strtok(exprCopia, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&pilha, atof(token));
        } else if (strlen(token) == 1 && strchr("+-*/^", token[0]) != NULL) {
            double b = desempilhar(&pilha);
            double a = desempilhar(&pilha);
            double resultado = 0.0;
            switch (token[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': resultado = a / b; break;
                case '^': resultado = pow(a, b); break;
                default: break;
            }
            empilhar(&pilha, resultado);
        } else if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 ||
                   strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 || strcmp(token, "log") == 0) {
            double a = desempilhar(&pilha);
            double resultado = 0.0;
            if (strcmp(token, "raiz") == 0) resultado = sqrt(a);
            else if (strcmp(token, "sen") == 0) resultado = sin(a * PI / 180);
            else if (strcmp(token, "cos") == 0) resultado = cos(a * PI / 180);
            else if (strcmp(token, "tg") == 0) resultado = tan(a * PI / 180);
            else if (strcmp(token, "log") == 0) resultado = log10(a);
            empilhar(&pilha, resultado);
        }
        token = strtok(NULL, " ");
    }

    return desempilhar(&pilha);
}

char* converterParaPrefixa(const char *expr) {
    PilhaDeStrings pilha;
    inicializarPilhaDeStrings(&pilha);

    char exprCopia[MAXEXPRESSAO];
    strcpy(exprCopia, expr);

    char *token = strtok(exprCopia, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilharString(&pilha, token);
        } else if (strlen(token) == 1 && strchr("+-*/^", token[0]) != NULL) {
            char *b = desempilharString(&pilha);
            char *a = desempilharString(&pilha);

            char resultado[MAXEXPRESSAO];
            snprintf(resultado, sizeof(resultado), "%s %s %s", token, a, b);

            empilharString(&pilha, resultado);

            free(a);
            free(b);
        } else {
            printf("Operador invalido: %s\n", token);
        }
        token = strtok(NULL, " ");
    }

    char *prefixa = desempilharString(&pilha);
    return prefixa;
}
