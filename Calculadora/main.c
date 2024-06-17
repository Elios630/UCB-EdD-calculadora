// main.c
#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"

// para compilar: gcc -o A main.c calculadora.c -lm         e  .\A.exe

int main() {
    char *testes[] = {
        "3 4 + 5 *",
        "7 2 * 4 +",
        "8 5 2 4 + * +",
        "6 2 / 3 + 4 *",
        "9 5 2 8 * 4 + * +",
        "2 3 + log 5 /",
        "10 log 3 ^ 2 +",
        "45 60 + 30 cos *",
        "0.5 45 sen 2 ^ +",
        "1 45 + sen 30 cos 60 tg + -"
    };
    int numTestes = sizeof(testes) / sizeof(testes[0]);

    printf("%-10s | %-30s | %-30s | %-20s\n", "Teste", "Notacao Pos-Fixada", "Notacao Pre-Fixada", "Valor final");
    printf("-----------------------------------------------------------------------------\n");

    for (int i = 0; i < numTestes; ++i) {
        double resultado = avaliarRPN(testes[i]);
        char* prefixa = converterParaPrefixa(testes[i]);
        printf("%-10d | %-30s | %-30s | %-20.2f\n", i + 1, testes[i], prefixa, resultado);
        free(prefixa);
    }
    return 0;
}