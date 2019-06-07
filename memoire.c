#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

/* alloue de la memoire avec malloc et teste si malloc a bien fonctionner */
void *my_malloc(unsigned int size) {
    void *p;
    p = malloc(size);
    if(p == NULL) {
       fprintf(stderr , "Erreur : impossible d’allouer la memoire\n");
       exit(-1);
    }
    return p;
}
/* alloue de la memoire avec realloc et teste si realloc s'est bien passé */
void *my_realloc(void *p, unsigned int size) {
     p = realloc(p, size);
     if(p == NULL) {
         fprintf(stderr , "Erreur : impossible de reallouer la memoire\n");
         exit(-1);
     }
     return p;
}