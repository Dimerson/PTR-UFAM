#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dstring.h"

Dstring* aloca_dstring(char *texto) {
    Dstring *dstring = (Dstring *)malloc(sizeof(Dstring));
    
    if (texto != NULL)
    {
        dstring->l = strlen(texto);
        dstring->data = (char *)malloc((dstring->l + 1) * sizeof(char));
        strcpy(dstring->data, texto);
    }
    else
    {
        dstring->l = 0;
        dstring->data = NULL;
    }

    return dstring;
}

Dstring* aloca_data(Dstring* dstring, char* texto)
{
    if(texto == NULL)
        return dstring;

    dstring->l = strlen(texto);
    dstring->data = (char*)malloc((dstring->l + 1)*sizeof(char));
    strcpy(dstring->data,texto);

    return dstring;
}

Dstring* append_dstring(Dstring *dstring, const char *str)
{
    if (str != NULL)
    {
        int novo_l = dstring->l + strlen(str);

        if(dstring->data == NULL)
            dstring = aloca_data(dstring, "");

        dstring->data = (char *)realloc(dstring->data, (novo_l + 1) * sizeof(char));
        strcat(dstring->data, str);
        dstring->l= novo_l;
    }

    return dstring;
}

void print_dstring(Dstring *dstring)
{
    if (dstring != NULL)
        if(dstring->data != NULL)
            printf("%s\n", dstring->data);
}

Dstring* libera_dstring(Dstring *dstring)
{
    if (dstring != NULL)
    {
        free(dstring->data);
        free(dstring);
    }

    return NULL;
}