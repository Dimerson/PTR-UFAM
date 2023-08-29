#include <stdio.h>
#include <stdlib.h>
#include "dstring.h"


int main() {
    Dstring *texto = aloca_dstring("Hello, ");
    texto = append_dstring(texto, "world!");
    print_dstring(texto);
    printf("\n\n");
    texto = libera_dstring(texto);

    Dstring* texto2 = aloca_dstring(NULL);
    print_dstring(texto2);
    texto2 = append_dstring(texto2, "Apenas um teste!");
    print_dstring(texto2);
    texto2 = libera_dstring(texto2);

    return 0;
}