#include <stdio.h>
#include "ppm.h"

#define NOM_DEFAULT "Cordiliere2_V3.ppm" //On définie le nom du fichier par defaut.

#include <GL/glut.h>
#include <GL/glu.h>

//Definit en global, car appelé en avec extern dans "affichage.c"
image img,x,y,z,a,b; 

int main(int argc, char *argv[]){

    if(argc  == 2){ //Si on met un argument apres l'executable.
        img = charger(argv[1]); //Alors l'argument apres l'executable est le nom du fichier à charger.
    } else if(argc == 1){
        img = charger(NOM_DEFAULT); // Sinon on charge le fichier par défaut défine en tête de fichier.
    } else{
        printf("Nombre d'arguments invalides.\n(Appel: ./Exe OU ./Exe image.ppm)\n");
        exit(1);
    }

    vectorPixel v,v1;
	vectorAlignement l,f;

    x=img; //On stock l'image originale dans x.

    /*On remplit un vecteur de pixels à fort contraste
    et on créer une nouvelle image a partir de ce vecteur*/
    v = newVectorPixel();
    remplirVectorPixel(img,v);
    y=afficheimagemodifier(img,v);

    /*On remplit un vecteur de pixels à fort contraste CONNEXES
    et on créer une nouvelle image a partir de ce vecteur*/
    v1 = vectorPixelConnexes(v);
    z=afficheimagemodifier(img,v1);

    /*On remplit un nouveau vecteur d'alignements, c'est a dire que ce vecteur
    contiens plusieur tableaux de pixels qui forment des lignes*/
    //MEME RENDU QUE LES PIXELS A FORT CONTRASTE CONNEXES MAIS PAS LE MEME TYPE DE VECTEUR.
   	l = vectorAlign(v1);
    a = afficheImageAlignement(img, l);

    /*On remplit un nouveau vecteur de formes (qui est en fait un vecteur 
    d'alignement sans les nuages de points a l'interieur des formes),
    puis on créer une nouvelle image.*/
    f = vectorForme(z, l); //On reprend l'image qu'avec les pixels fort contraste connexes
    b = afficheImageAlignement(img, f);

    /*AFFICHAGE*/
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(0,0);  
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Projet 3: Contrastes et Alignements");  

    init();
    glutCreateMenu(menu);

    /*LES 5 OPTIONS DE NOTRE MENU*/
    glutAddMenuEntry("Quitter", 0);
    glutAddMenuEntry("Image originale", 1);
    glutAddMenuEntry("Pixels a fort contraste", 2);
    glutAddMenuEntry("Pixels a fort contraste connexes", 3);
    glutAddMenuEntry("Alignements",4);
    glutAddMenuEntry("Forme",5);


    glutAttachMenu(GLUT_LEFT_BUTTON);


    glutDisplayFunc(Draw);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
  
    glutMouseFunc(Mouse);
    glutMainLoop();
    
    return 0;
}
