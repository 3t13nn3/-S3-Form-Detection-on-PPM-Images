#include <stdio.h>
	
#include "ppm.h"

#include <GL/glut.h>
#include <GL/glu.h>

extern image img,x,y,z,a,b; //On passe les images du main en extern ici.

/*ON DEFINIT LE CODE ASCII DES TOUCHES EN QUESTION*/
#define ESCAPE 27
#define Q 113

void Keyboard(unsigned char key, int x, int y)  {
  switch(key){
  case ESCAPE:
    supprimer(img);
    exit(1);                 
    break;
  case Q:
    supprimer(img);
    exit(1);                 
    break;
  default:
    fprintf(stderr, "Touche inutile\n");
  }
}

void Mouse(int button, int state, int x, int y) {

  switch(button){
  case GLUT_LEFT_BUTTON:
    break;
  case GLUT_MIDDLE_BUTTON:
    break;
  case GLUT_RIGHT_BUTTON:
    break;    
  }
  glutPostRedisplay();
}

void init(){
	if(img == NULL) {
    	printf("L'image ne s'est pas chargé correctement.\n");
    	return;
  	}else{
  		glClearColor(0.0, 0.0, 0.0, 0.0);
  		glShadeModel(GL_FLAT);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glutReshapeWindow(img->largeur, img->hauteur);
  	}
}

void Reshape(int w, int h) {
  	glViewport(0, 0, (GLsizei)w, (GLsizei) h);
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();  
  	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble)h);
 	  glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
}

void Draw(){
  	glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(img->largeur, img->hauteur, GL_RGB, GL_UNSIGNED_BYTE, img->pix);

    glFlush();
}

/*FONCTION REPRENNANT TOUT LES CHOIX DE NOTRE MENU DANS UN SWITCH*/

/*On voit ici qu'on ne charge pas l'image quand on veut l'afficher,
mais plutôt, on attribut juste la valeur de l'image à afficher à la
variable "img". La valeur de l'image à afficher est calculé au début
du programme (dans le main), cela évite de recalculer la valeur de 
la nouvelle image si on veut alterner entres deux pour les comparer
(on pense ici à la detections de formes qui met un temps considérable.*/

void menu(int etat){
  
  switch(etat){
    case 0:
      supprimer(img);
      exit(1);
      break;
    case 1:
        img = x;
        printf("AFFICHE L'IMAGE ORIGINALE'\n");
      break;
    case 2:
        img = y;
        printf("AFFICHE LES PIXELS A FORT CONTRASTE\n");
      break;
    case 3:
        img = z;
        printf("AFFICHE LES PIXELS A FORT CONTRASTE CONNEXES\n");
      break;
    case 4:
        printf("AFFICHE LES ALIGNEMENTS\n");
        img = a;
      break;
    case 5:
    	printf("AFFICHE LES FORMES\n");
    	img = b;
      break;
    default:
      break;
  }
}