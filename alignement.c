#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

//Teste si trois pixels sont sur la même ligne.
int coleinaire(coord a ,coord b,coord c){ 
   coord ab ,ac ;
   int t;
   ab.x= b.x - a.x;
   ab.y= b.y - a.y;  
   ac.x= c.x - a.x;
   ac.y= c.y - a.y;
   t = ab.x * ac.y - ac.x * ab.y;

   return (!t);
}

//Prend en argument un vectorPixel et teste si les pixels qui le composent forment une ligne.
int ligne (vectorPixel v){ 
  int i;
  if (size(v) < 2)
    return 0;
  if (size(v)== 2)
    return 1;
  if(size(v) > 2){
    for(i=0;i<v->n-2;i++){
      if(!(coleinaire(v->tab[i],v->tab[i+1],v->tab[i+2])))
        return 0;
    }
    return 1;
  }
  return 0;
}


/*Prends en argument un vectorPixel et des coordonnes d'un pixel,
teste si les coordonnes des pixels qui composent ce vectorPixel forme une ligne 
avec les coordonnes du pixel qu'on a mis en argument.*/
int linair(vectorPixel v , coord p){ 
  pushBackPixel(v,p);
  if(ligne(v)){
    pop_back(v);
    return 1;
  }
  pop_back(v);
  return 0;
}

/*Prend un vectorPixel en argument et renvoie un vectorAlignement.
Cette fonction parcours le vectorPixel et le découpe en ligne  
a chaque fois qu'on trouve une ligne on la met dans le vectorAlignement 
a la fin on le renvoie.*/
vectorAlignement decoupe(vectorPixel v){  
  int i;
  vectorAlignement a = newVectorAlignement();
  vectorPixel v1=newVectorPixel();
  vectorPixel v2=newVectorPixel();
  pushBackPixel(v1,v->tab[0]);
  pushBackPixel(v1,v->tab[1]);
  for(i=2;i<v->n;i++){
    if(linair(v1,v->tab[i]))
      pushBackPixel(v1,v->tab[i]);
    else{
      v2 = copy(v1);
      pushBackAlignement(a,v2);
      clear(v1);
      pushBackPixel(v1,v->tab[i-1]);
      pushBackPixel(v1,v->tab[i]);
    }
  }
  pushBackAlignement(a,v1);
  return a;
}

//vide le vectorAlignement
void cleara(vectorAlignement v) {
  v->tab = realloc(v->tab,sizeof(vectorPixel));
  v->n = 0;
  v->cap = 2;
}

//fais une copie du vectorAlignement
vectorAlignement copyy(vectorAlignement v) { 
     vectorAlignement vcop = my_malloc(sizeof(*vcop));
     vcop->tab = my_malloc(v->n * sizeof(vectorPixel));
     memcpy(vcop->tab, v->tab, v->n * sizeof(vectorPixel));
     vcop->n = v->n;
     vcop->cap = v->n;
     return vcop;
}

//permet de déclarer un vectoralignement vide de taille 0 et capacite 0.
vectorAlignement newVectorAlignement(){  
	vectorAlignement v = my_malloc(sizeof(*v));
    v->tab = my_malloc(sizeof(vectorPixel));
    v->n = 0;
    v->cap = 0;
    return v;
}

//Permet de réserver de la mémoire pour accueillir un nouvel élément du vectorAlignement
void reserveAlignement(vectorAlignement v, int newcap){
	v->tab = my_realloc(v->tab, newcap * sizeof(vectorPixel));
        v->cap = newcap;
    	if(v->n > v->cap)
             v->n = v->cap;
}

//Qui permet de rajouter un vectorPixel en dernière position du vectoAlignement.
void pushBackAlignement(vectorAlignement v, vectorPixel data){ 
	reserveAlignement(v, v->cap + 1);
	v->tab[v->n] = data;
	v->n++;
}

//supprime le vectorPixel de la mémoire 
void deleteVectorAlignement(vectorAlignement v){ 
	free(v->tab);
    free(v);
}

//affiche le vectorAlignement
void afficheVectorAlignement(vectorAlignement v){ 
	for(int i = 0; i<v->n; i++){
	  printf("va[%d]=",i);
	   afficheVectorPixel(v->tab[i]);
	}
}

/* Cette fonction prend le vectorpixel qui est renvoyer par vectorpixelconnexes 
le parcours tant que les pixels du vectorPixel forme une ligne ou une courbe continue  
et met chaque lignes ou courbe dans un vectoralignement et a la fin de la boucle on renvoie le vectoralignemet.*/
vectorAlignement vectorAlign(vectorPixel v){
  vectorAlignement a = newVectorAlignement();
  vectorPixel v1 = newVectorPixel();
  vectorPixel v2 = newVectorPixel();
  int i;
  for( i = 0;i<v->n;++i){
    if ((pixelConnexes(v->tab[i],v->tab[i+1]))){
        if(!equalcoor(v1->tab[v1->n-1],v->tab[i]))
         pushBackPixel(v1,v->tab[i]);
      pushBackPixel(v1,v->tab[i+1]);

    }
    else{
       if(!(empty(v1))){
        v2 = copy(v1);
        pushBackAlignement(a,v2);
        clear(v1);
       }
    }
  }
  return a;
}

/*Cette fonction prend le vectorAlignement renvoyer par 
la fonctions vectoralign et découpe chacun de ses éléments en lignes 
ce qui nous fais un vectoralignement de lignes et a la fin de la boucle on le renvoie.*/
vectorAlignement vectorligne(vectorAlignement a){
  vectorAlignement v = newVectorAlignement();
  vectorAlignement b = newVectorAlignement();
  int i,j;
  for(i=0;i<a->n;i++){
    if(ligne(a->tab[i]))
      pushBackAlignement(v,a->tab[i]);
    else{
      b = decoupe(a->tab[i]);
      for(j=0;j<b->n;++j)
        pushBackAlignement(v,b->tab[j]);

    }
  }
  return v;
}