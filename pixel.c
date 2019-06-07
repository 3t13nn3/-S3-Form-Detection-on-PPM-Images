#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "ppm.h"


/************VECTEUR DE pixel*************/

//Qui permet de déclarer un vectorPixel vide de taille 0 et capacite 0.
vectorPixel newVectorPixel(){ 
	vectorPixel v = my_malloc(sizeof(*v));
    v->tab = my_malloc(sizeof(coord));
    v->n = 0;
    v->cap = 0;
    return v;
}

//Permet de réserver de la mémoire pour accueillir un nouveau élément du vectorPixel
void reservePixel(vectorPixel v , int newcap){ 
	v->tab = my_realloc(v->tab, newcap * sizeof(coord));
        v->cap = newcap;
    	if(v->n > v->cap)
              v->n = v->cap;
}

//Qui permet de rajouter un élément en dernière position du vectoPixel.
void pushBackPixel(vectorPixel v, coord data){  
	
	reservePixel(v, v->cap + 1);
	v->tab[v->n] = data;
	v->n++;
}

//retire le dernier element du vectorPixel.
void pop_back(vectorPixel v) { 
    if(v->n == 0) {
    fprintf(stderr , "Erreur : suppression du dernier element d’unvector vide\n");
    exit(-1);
    }
    v->n--;
}

//fais une copie du vectorPixel
vectorPixel copy(vectorPixel v) { 
     vectorPixel vcop = my_malloc(sizeof(*vcop));
     vcop->tab = my_malloc(v->n * sizeof(coord));
     memcpy(vcop->tab, v->tab, v->n * sizeof(coord));
     vcop->n = v->n;
     vcop->cap = v->n;
     return vcop;
}

//teste si le vector Pixel est vide
int empty(vectorPixel v) { 
    return v->n == 0;
}

//renvoie la taille du vectorPixel
int size(vectorPixel v) { 
     return v->n;
}

//vide le vectorPixel
void clear(vectorPixel v) { 
  v->tab = realloc(v->tab,sizeof(coord));
  v->n = 0;
  v->cap = 2;
}

//supprime le vectorPixel de la mémoire
void deleteVectorPixel(vectorPixel v){ 
	free(v->tab);
    free(v);
}

//affiche le vectorPixel
void afficheVectorPixel(vectorPixel v){ 
	int n = 0;
	for(int i = 0; i<v->n; i++){
		printf("\t v[%d] = x: %d\ty: %d\n", i,v->tab[i].x, v->tab[i].y);
		n++;
	}
	printf("Il y a %d élement dans le tableau\n", n);
}

/*Dans cette fonction on parcours l'image grâce a deux boucles "for" on la parcours de gauche a 
 droite de haut en bas on récupère les pixels grâce a getPixel.
On calcule la distance avec tout ses voisins et on regarde si cette distance avec chacun de ses voisins et supérieur a notre seuil, 
si c'est le cas on récupère les coordonnées de ce pixels et les mets dans notre vectorPixel 
qu'on a declarer vide et qu'on remplie de tout les pixels de fort contraste */
void remplirVectorPixel(image I, vectorPixel v){
	for(int i=0;i<I->largeur;i++){
     	for(int j=0;j<I->hauteur;j++){
       
         	pixel p  = getPixel(I,i,j);
         	pixel p1;
         	pixel p2;
         	pixel p3;
         	pixel p5;
         	pixel p4;
         	pixel p6;
         	pixel p7;
         	pixel p8;
         	double d1;
	        double d2;
	        double d3;
	        double d4;
	        double d5;
	        double d6;
	        double d7;
	        double d8;
	        coord t;

             if ( i ==0 && j==0){
                 p1 = getPixel(I,i+1,j);
        	     p2 = getPixel(I,i,j+1);
        	     p3 = getPixel(I,i+1,j+1);
        	     d1 = calculContraste(p,p1);
	             d2 = calculContraste(p,p2);
	             d3 = calculContraste(p,p3);

        	     if (testContraste(d1)&&testContraste(d2)&&testContraste(d3)){
                     t.x = i;
	                 t.y = j;
	                 pushBackPixel(v,t);
        	        }
                }

             if ((i==0)&& (j==I->hauteur -1)){

                 p1 = getPixel(I,i+1,j);
                 p2 = getPixel(I,i,j-1);
        	     p3 = getPixel(I,i+1,j-1);
        	     d1 = calculContraste(p,p1);
	             d2 = calculContraste(p,p2);
	             d3 = calculContraste(p,p3);


        	     if (testContraste(d1)&&testContraste(d2)&&testContraste(d3)){
                     t.x = i;
	                 t.y = j;
	                 pushBackPixel(v,t);
	                 
	                        	
        	        }
                }
             if (i == 0 && j!=0 && j!= I->hauteur-1){
                 p1 = getPixel(I,i+1,j);
        	     p2 = getPixel(I,i+1,j-1);
        	     p3 = getPixel(I,i+1,j+1);
        	     p4 = getPixel(I,i,j-1);
        	     p5 = getPixel(I,i,j+1);
                 d1 = calculContraste(p,p1);
	             d2 = calculContraste(p,p2);
	             d3 = calculContraste(p,p3);
	             d4 = calculContraste(p,p4);
	             d5 = calculContraste(p,p5);
                 if (testContraste(d1)&&testContraste(d2)&&testContraste(d3)&&testContraste(d4)&&testContraste(d5)){
                     t.x = i;
	                 t.y = j;
	                 pushBackPixel(v,t);
        	        }
                }

             if ( i == I->largeur-1 && j==0){
        	     p1 = getPixel(I,i-1,j);
        	     p2 = getPixel(I,i,j+1);
        	     p3 = getPixel(I,i-1,j+1);
        	     d1 = calculContraste(p,p1);
	             d2 = calculContraste(p,p2);
	             d3 = calculContraste(p,p3);
        	     if (testContraste(d1)&&testContraste(d2)&&testContraste(d3)){
                     t.x = i;
	                 t.y = j;
	                 pushBackPixel(v,t);
	                }
                }
             if ((i==I->largeur-1)&& (j==I->hauteur -1)){
                 p1 = getPixel(I,i-1,j);
        	     p2 = getPixel(I,i,j-1);
        	     p3 = getPixel(I,i-1,j-1);
        	     d1 = calculContraste(p,p1);
	             d2 = calculContraste(p,p2);
	             d3 = calculContraste(p,p3);
        	     if (testContraste(d1)&&testContraste(d2)&&testContraste(d3)){
                     t.x = i;
	                 t.y = j;
	                 pushBackPixel(v,t);
        	        }
                }

             if (i == I->largeur-1 && j != 0 && j != I->hauteur-1){
                 p1 = getPixel(I,i-1,j);
        	     p2 = getPixel(I,i-1,j-1);
               	 p3 = getPixel(I,i-1,j+1);
        	     p4 = getPixel(I,i,j-1);
        	     p5 = getPixel(I,i,j+1);
                 d1 = calculContraste(p,p1);
	             d2 = calculContraste(p,p2);
	             d3 = calculContraste(p,p3);
	             d4 = calculContraste(p,p4);
	             d5 = calculContraste(p,p5);
                 if (testContraste(d1)&&testContraste(d2)&&testContraste(d3)&&testContraste(d4)&&testContraste(d5)){
                     t.x = i;
	                 t.y = j;
	                 pushBackPixel(v,t);
        	        }
                }

              if (j==0 && i!= 0 && i!= I->largeur-1){
        	     p1 = getPixel(I,i+1,j);
        	     p2 = getPixel(I,i-1,j);
        	     p3 = getPixel(I,i-1,j+1);
        	     p4 = getPixel(I,i,j+1);
        	     p5 = getPixel(I,i+1,j+1);
        	     d1 = calculContraste(p,p1);
	             d2 = calculContraste(p,p2);
	             d3 = calculContraste(p,p3);
	             d4 = calculContraste(p,p4);
	             d5 = calculContraste(p,p5);
                 if (testContraste(d1)&&testContraste(d2)&&testContraste(d3)&&testContraste(d4)&&testContraste(d5)){
                     t.x = i;
	                 t.y = j;
	                 pushBackPixel(v,t);  
        	        }
                }
             if (j == I->hauteur-1 && i!= 0 && i!= I->largeur-1){
                 p1 = getPixel(I,i-1,j);
        	     p2 = getPixel(I,i+1,j);
        	     p3 = getPixel(I,i-1,j-1);
        	     p4 = getPixel(I,i,j-1);
        	     p5 = getPixel(I,i+1,j-1);
        	     d1 = calculContraste(p,p1);
	             d2 = calculContraste(p,p2);
	             d3 = calculContraste(p,p3);
	             d4 = calculContraste(p,p4);
	             d5 = calculContraste(p,p5);
                 if (testContraste(d1)&&testContraste(d2)&&testContraste(d3)&&testContraste(d4)&&testContraste(d5)){
                     t.x = i;
	                 t.y = j;
	                 pushBackPixel(v,t);
        	        }
        	    }

             if(i>0 && j > 0 && i<I->largeur-1 && j < I->hauteur - 1){
	    
	             p1 = getPixel(I,i-1,j-1);
	             p2 = getPixel(I,i-1,j);
	             p3 = getPixel(I,i-1,j+1);
	             p4 = getPixel(I,i,j-1); 
	             p5 = getPixel(I,i,j+1); 
	             p6 = getPixel(I,i+1,j-1); 
	             p7 = getPixel(I,i+1,j);
	             p8 = getPixel(I,i+1,j+1);
	             d1 = calculContraste(p,p1);
	             d2 = calculContraste(p,p2);
	             d3 = calculContraste(p,p3);
	             d4 = calculContraste(p,p4);
	             d5 = calculContraste(p,p5);
	             d6 = calculContraste(p,p6);
	             d7 = calculContraste(p,p7);
	             d8 = calculContraste(p,p8);

	             if (testContraste(d1)&&testContraste(d2)&&testContraste(d3)&&testContraste(d4)&&testContraste(d5)&&testContraste(d6)&&testContraste(d7)&&testContraste(d8)){
                     t.x = i;
	                 t.y = j;
	                 pushBackPixel(v,t);
	                }
                }     		     

        }
    }  
}

//teste si deux pixels ont la même coordonnées.
int equalcoor(coord a , coord b){ 
     return ((a.x == b.x) && (a.y == b.y)) ;
}

//creer un vecteur de pixel qui sont connexes, en comparant leurs coordonnées
vectorPixel vectorPixelConnexes(vectorPixel v){
	vectorPixel v1 = newVectorPixel();
	int i=0;
	while(i<v->n-1){
		if(pixelConnexes(v->tab[i],v->tab[i+1])){
			if(!equalcoor(v1->tab[v1->n-1],v->tab[i]))
				pushBackPixel(v1,v->tab[i]);
			pushBackPixel(v1,v->tab[i+1]);
		}
		i=i+1;
	}
	return v1;
}

/*******************PIXEL**********************/
//permet de renvoyer un pixel du tableau a partir de ses coordonnées 
pixel getPixel(image img, int largeur, int hauteur){ 
	if(img){
		return img->pix[img->largeur*hauteur+largeur];
	}
	printf("Erreur lors de la récuperation du Pixel");
	return img->pix[0];	
}

//permet de sauvegarder les changements qu'on opérer sur un pixel a partir de ses coordonnées.
void SetPixel(image I,int largeur,int hauteur,pixel p) 
{
	assert(I && largeur>=0 && largeur<I->largeur && hauteur>=0 && hauteur<I->hauteur);
	I->pix[I->largeur*hauteur+largeur] = p;
}

//teste di deux pixels sont connexes
int pixelConnexes(coord a,coord b){ 
	return(((a.x == b.x) && (a.y == b.y+1)) ||
	   ((a.x == b.x) && (a.y == b.y-1)) ||
	   ((a.x == b.x-1) && (a.y == b.y)) ||
	   ((a.x == b.x+1) && (a.y == b.y)) ||
	   ((a.x == b.x+1) && (a.y == b.y+1)) ||
	   ((a.x == b.x-1) && (a.y == b.y+1)) ||
	   ((a.x == b.x+1) && (a.y == b.y-1)) ||
	   ((a.x == b.x-1) && (a.y == b.y-1)));			
}

