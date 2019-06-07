#include <stdio.h>
#include "ppm.h"

extern image img;

/*Les deux valeurs sont proportionnelles pour l'universalité du programme.
cette méthode est universelle par rapport a la taille de l'image, pas a la
densité de points que nous pouvons y trouver.

Plus la valeur de DISTANCE est grande, plus il y aura de calcul, donc plus 
de temps (mais par contre, cela sera plus précis, par contre, il faudrait 
changer la formule de SEUIL car il ne dépend pas de DISTANCE).	
Donc il y a des consessions à faire entre:
	-la rapidité du programme.
	-la qualité des formes affichés.

Il suffit de changer la valeur avec laquelle on divise pour etre plus 
ou moins exigeant sur les formes que l'on laisse.

En effet si on a une DISTANCE minuscule pour un grand seuil, le programme va
garder que très peu de points. Si l'ont veut modifier cette valeur, on ajoute/soustrait
maximum 2 a cette valeur, sinon cela prendra, soit trop de points, soit pas assez.

Le plus dur est de trouver le bon "ratio" entre distance et seuil, cela depend en fonction
de l'image, sa taille etc.

-Pépins pour l'image du requin
-Ne marche pas du tout pour l'image chatou.*/
#define SEUIL ((img->hauteur * img->largeur) / (img->hauteur+ img->largeur))
#define DISTANCE SEUIL / 19 

/*****************FORMES********************/

/*CREER UN VECTEUR NE GARDANT QUE LES CONTOUR DES FORMES*/
vectorAlignement vectorForme(image img, vectorAlignement v){
	int i,j;
	vectorAlignement a = newVectorAlignement();
	for(i = 0; i<v->n; i++){
		for(j = 0; j<v->tab[i]->n; j++){
			if(isole(img, v->tab[i])) //on vérifie si l'alignement en question ne possède pas trop de pixels voisins
				pushBackAlignement(a,v->tab[i]);//si c'est le cas on ajoute l'alignemnt a notre vecteur.
		}
	}
	return a;
}


/*Excepté les pixels du vecteur, on vérifie les alentours du vecteur
délimité par DISTANCE (on peut imaginer que le point analysé est le milieu
d'un carré. Le pixels est donc a "DISTANCE" pixels de chaque coté. On va
parcourir tout le carré pour compter le nombre de pixels qu'il y a dedans.).

Combien de pixels il y a en dessous de SEUIL ?

Si le nombre est supérieur à ce qu'on a définie, on ne fais rien,
sinon on l'ajoute au nouveau vecteur d'alignement. 
Predicat pour savoir si le vecteur de pixel est isolé d'autres pixels.*/
int voisin(image I, int largeur, int hauteur, vectorPixel v, int taille){
	int nb = 0;
	for(int i = largeur-DISTANCE; i<largeur+DISTANCE; ++i){
		for(int j = hauteur-DISTANCE; j<hauteur+DISTANCE; ++j){
			pixel p;
       		p.r = getPixel(I,i,j).r;
        	p.g = getPixel(I,i,j).g;
        	p.b = getPixel(I,i,j).b;
			if(p.r != 255 || p.g != 255 || p.b != 255 ){ //Si le pixel de l'image n'es pas blanc.
				nb++;
			}
		}
	}
	if(nb < SEUIL - taille)//On enlève "taille", c'est a dire le nombre de pixels qu'il y a dans le vecteur, car on ne veut pas les compter.
		return 1;
	//Peut ête utile de décommenter pour voir les pixels qui prend.
	//printf("%d\n",nb);
	return 0;
}

/*PERMET DE SAVOIR SI L'ALIGNEMENT NE POSSEDE PAS TROP DE POINT AUX ALENTOURS*/
int isole(image img, vectorPixel v){
	int i, taille;
	/*Sert a définir la taille de la variable taille*/
	for(i = 0; i<v->n; i++){//on parcour la taille de l'alignement
		continue;
	}
	if(i>DISTANCE*2) //inutile de garder la taille totale si la taille est plus grande que 2*DISTANCE, cad la largeur ou la hauteur du carré analysé. 
		i=DISTANCE*2;
	taille = i;

	for(i = 0; i<v->n; i++){
		if(!voisin(img, v->tab[i].x, v->tab[i].y, v, taille)) //On appel !voisin a chaque pixels de l'alignement.
			return 0;
	}
	return 1;
}