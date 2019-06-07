#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ppm.h"
#define CREATOR "RPFELGUEIRAS"

/**********************IMAGE**********************/

/*CREER UN NOUVELLE IMAGE
INSPIRÉ DE http://www.ai.univ-paris8.fr/~jj/Cours/Algo/Images/ppm.c*/
image imageVierge(int l, int h){
	/* allocation memoire */
	image img = (image) malloc(sizeof(image_t));
	assert(img);
	img->pix = (pixel *) malloc(sizeof(pixel)*l*h);
	assert(img->pix);
	img->hauteur = h;
    img->largeur = l;
    return img;
}

/*CHARGE L'IMAGE, GROSSE PARTIE DU CODE PRISE SUR http://www.ai.univ-paris8.fr/~jj/Cours/Algo/Images/ppm.c*/
image charger(const char* filename){
    char buff[16];
    image img;
    FILE *fp;
    int c,rgb_comp_color, size ,i , j;
    pixel a;
    //open PPM file for reading
    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Impossible d'ouvrir le fichier: '%s'\n", filename);
        exit(1);
    }

    //read image format
    if (!fgets(buff, sizeof(buff), fp)) {
        perror(filename);
        exit(1);
    }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Format invalide (uniquement 'P6')\n");
         exit(1);
    }

    //alloc memory form image
    img = (image)malloc(sizeof(image_t));
    if (!img) {
         fprintf(stderr, "Erreur mémoire\n");
         exit(1);
    }

    //check for comments
    c = getc(fp);


    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->largeur, &img->hauteur) != 2) {
         fprintf(stderr, "Erreur du chargement de la taille de l'image\n");
         exit(1);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    //check rgb component depth
    if (rgb_comp_color!= 255) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->pix = (pixel*)malloc(img->largeur * img->hauteur * sizeof(pixel));

    if (!img) {
         fprintf(stderr, "Erreur mémoire\n");
         exit(1);
    }

    if (fread(img->pix, 3 * img->largeur, img->hauteur, fp) != (unsigned int)img->hauteur) {
         fprintf(stderr, "Erreur la du chargement de l'image '%s'\n", filename);
         exit(1);
    }

   	/*RETOURNE L'IMAGE*/
    for (i = 0;i <img->largeur; ++i) {
        for(size = img ->hauteur -1,j=0;j<size;j++,--size){
         a = img->pix[img->largeur*j+i];
         img->pix[img->largeur*j+i]= img->pix[img->largeur*size+i];
         img->pix[img->largeur *size+i]=a;
         
        }
    }


    fclose(fp);
    return img;
}   

/*LIBÈRE LA MÉMOIRE DE L'IMAGE*/
void supprimer(image img){
    if(img){
        free(img->pix);
        free(img);
    }
    else
        return;
}

/*RETOURNE L'IMAGE IDENTIQUE A ELLE EN ARGUMENT*/
image CopieImage(image I){
    image res;
    if (!I)
        return NULL;
    res = imageVierge(I->largeur,I->hauteur);
    memcpy(res->pix,I->pix,I->largeur*I->hauteur*sizeof(pixel));
    return res;
}

/*RETOURNE L'IMAGE AVEC SEULEMENT LES PIXELS CONTENUE DANS LE VECTEUR DE PIXEL*/
image afficheimagemodifier(image I , vectorPixel v){
    int i,j;
    image src;
    src =CopieImage(I);
    for(i=0;i<I->largeur;++i){
        for(j=0;j<I->hauteur;++j){
            pixel p;
            p.r = 255;
            p.g = 255;
            p.b = 255;
            SetPixel(src,i,j,p);
        }
    }
    for(i=0;i<v->n;++i){
        pixel p;
        p.r = getPixel(I,v->tab[i].x,v->tab[i].y).r;
        p.g = getPixel(I,v->tab[i].x,v->tab[i].y).g;
        p.b = getPixel(I,v->tab[i].x,v->tab[i].y).b;
        SetPixel(src,v->tab[i].x,v->tab[i].y,p);
    }
    return src;
}

/*RETOURNE L'IMAGE AVEC SEULEMENT LES PIXELS CONTENUE DANS LE VECTEUR D'ALIGNEMENT*/
image afficheImageAlignement(image I, vectorAlignement v){
	int i,j;
    image src;
    src =CopieImage(I);
    for(i=0;i<I->largeur;++i){
        for(j=0;j<I->hauteur;++j){
            pixel p;
            p.r = 255;
            p.g = 255;
            p.b = 255;
            SetPixel(src,i,j,p);
        }
    }
    for(i = 0; i<v->n; i++){
		for(j = 0; j<v->tab[i]->n; j++){
        	pixel p;
        	p.r = getPixel(I,v->tab[i]->tab[j].x,v->tab[i]->tab[j].y).r;
        	p.g = getPixel(I,v->tab[i]->tab[j].x,v->tab[i]->tab[j].y).g;
        	p.b = getPixel(I,v->tab[i]->tab[j].x,v->tab[i]->tab[j].y).b;
        	SetPixel(src,v->tab[i]->tab[j].x,v->tab[i]->tab[j].y,p);
    	}
    }
    return src;
}
