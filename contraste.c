#include<stdio.h>
#include <math.h> //On ajoute -lm à la compilation.
#include "ppm.h"

#define SEUIL_CONTRASTE 7 //10

/*****************CONTRASTE********************/

/*PREDICAT QUI TEST SI LE PIXEL EST CONTRASTÉ*/
int testContraste(double x){
	return x > SEUIL_CONTRASTE; //SEUIL_CONTRASTE à déclarer dans le define en début de fichier.
}

/*CALCUL LE CONTRASTE ENTRE DEUX PIXELS*/
double calculContraste(pixel x, pixel y){
	return sqrt(((y.r - x.r)*(y.r - x.r)) + ((y.g - x.g)*(y.g - x.g)) + ((y.b - x.b)*(y.b - x.b)));
}