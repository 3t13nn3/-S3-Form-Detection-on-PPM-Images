#include <GL/gl.h>	

/*DEFINITION DES STRUCTURES*/

struct Pixel{
	GLubyte r,g,b; //unsigned char car un pixel comporte 255 couleurs, comme le nombre de bytes d'un unsigned char.
};
typedef struct Pixel pixel;

struct coord
{
	int x,y;
};
typedef struct coord coord;


struct Image{
	int hauteur, largeur;
	pixel * pix;
};
typedef struct Image image_t;
typedef struct Image * image; //Evite de passer image_t* pour l'utilisation


struct VectorPixel{
	coord * tab;
	int n;
	int cap;
};
typedef struct VectorPixel vectorPixel_t;
typedef struct VectorPixel * vectorPixel;

struct VectorAlignement{
	vectorPixel * tab;
	int n;
	int cap;
};
typedef struct VectorAlignement vectorAlignement_t;
typedef struct VectorAlignement * vectorAlignement;

/**********************************************************************/
/**********************************************************************/

/*DEFINITION DES PROTOTYPES*/

/*Image*/
image charger(const char *); //FAIT//// Prend le nom de l'image et retourne l'image en question (Enfait ses données).
image imageVierge(int,int); //FAIT//// Hauteur,Largeur.
void supprimer(image); //FAIT////
image afficheimagemodifier(image, vectorPixel);//FAIT////
image afficheImageAlignement(image , vectorAlignement);
image CopieImage(image);//FAIT////

/*Pixel*/
pixel getPixel(image, int, int); //FAIT//// Image, coordonnées x et y.
void SetPixel(image,int,int,pixel);//FAIT////
int pixelConnexes(coord,coord); //FAIT//// Test si deux pixels se touches (Diagonale comprise).
void remplirVectorPixel(image , vectorPixel);//FAIT////
int inVectorPixel(vectorPixel, coord);//FAIT////
void afficheVectorPixel(vectorPixel);//FAIT////
vectorPixel newVectorPixel(); //FAIT////
void pushBackPixel(vectorPixel, coord); //FAIT////
void pop_back(vectorPixel v);//FAIT////
void deleteVectorPixel(vectorPixel); //FAIT////
void reserveCoordonnes(vectorPixel, int); //FAIT////
int size(vectorPixel);//FAIT////
vectorPixel vectorPixelConnexes(vectorPixel);//FAIT////
vectorPixel copy(vectorPixel);//FAIT////
int equalcoor(coord , coord);//FAIT////
int empty(vectorPixel);//FAIT////
void clear(vectorPixel);//FAIT///

/*Contraste*/
double calculContraste(pixel, pixel); //FAIT////
int testContraste(double); //FAIT//// Test si le contraste est suffisament grand pour le garder.


/*Vector d'Alignements*/
void afficheVectorAlignement(vectorAlignement); //FAIT////
vectorAlignement newVectorAlignement(); //FAIT////
vectorAlignement trouveAlignement(vectorPixel); //Renvoie un tableau, contenant les Alignements.
void pushBackAlignement(vectorAlignement, vectorPixel); //FAIT////
void deleteVectorAlignement(vectorAlignement); //FAIT////
void reserveAlignement(vectorAlignement, int); //FAIT////
int Nbalignes (vectorPixel );//FAIT////
vectorAlignement vectorAlign(vectorPixel);//FAIT////
int coleinaire(coord,coord,coord);//FAIT////
int ligne (vectorPixel);//FAIT////
vectorAlignement vectorligne(vectorAlignement);//FAIT////
vectorAlignement decoupe(vectorPixel);//FAIT////

/*Mémoire*/
void* my_malloc(unsigned int); //FAIT//// unsigned int == size_t.
void* my_realloc(void *, unsigned int);//FAIT////

/*Affichage*/
void init();//FAIT////
void Reshape(int, int);//FAIT////
void Draw();//FAIT////
void menu(int);//FAIT////
void Keyboard(unsigned char, int, int);//FAIT////
void Mouse(int, int, int, int);//FAIT////

/*Forme*/
vectorAlignement vectorForme(image, vectorAlignement);//FAIT////
int voisin(image I, int largeur, int hauteur, vectorPixel v, int taille);//FAIT////
int isole(image,vectorPixel);//FAIT////