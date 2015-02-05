#ifndef _IMAGE_
#define _IMAGE_

typedef enum{

	NOIR=0,
	COULEUR=1,
	BIN=2,
	INCOLORE=3,

}Couleur;

typedef enum{

	BINAIRE=0,
	DECIMAL=1,
	INCONUE=2,

}Codage;

typedef struct sPixel * Pixel;

Pixel initPixel(Couleur couleur);

void detruirePixel(Pixel pixel);

void setValeurPixel(Pixel pixel, unsigned char * valeur); 

unsigned char getValeurPixel(Pixel pixel, int couleur);

typedef struct sImage * Image;

Image initImage(void);

void detruireImage(Image image);

void infoImage(Image image);

Image chargerImage(char * fichier);

void sauverImage(Image image, char * fichier, Codage codage, Couleur couleur);

Pixel getPixelImage(Image image, int i, int j);

#endif
