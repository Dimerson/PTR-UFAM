#ifndef DSTRING_H
#define DSTRING_H

typedef struct {
    char *data;
    int l;
} Dstring;

Dstring* aloca_dstring(char *initial);
Dstring* append_dstring(Dstring *dstring, const char *str);
void print_dstring(Dstring *dstring);
Dstring* libera_dstring(Dstring *dstring);


#endif