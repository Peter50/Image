/**
* @file image_util.c
* @author CHEN Denis - 1A Info ENSICaen
*/

#include "image.h"
#include "image_util.h"

struct sOrdre{

	double M0,
	double * M1,
	double * M2,

};

Ordre initOrdre(void){

	Ordre ordre=malloc(sizeof(struct sOrdre));

	ordre->M0=0;
	ordre->M1=calloc(3,sizeof(double));
	ordre->M2=calloc(3,sizeof(double));

	return ordre;
}

void detruireOrdre(Ordre ordre){

	free(ordre->M2);
	free(ordre->M1);
	free(ordre);
}

/**
* Lecture d'une image
* @param Image(Image) à analyser
* @param Ligne(int) du pixel à lire
* @param Colonne(int) du pixel à lire
* @param Couleur(unsigned char*) du pixel à lire
*/

extern void image_read_pixel(Image pic, int ligne, int colonne, unsigned char* couleur)
{

	Pixel pixel=getPixelImage(pic,ligne,colonne);

	couleur[0]=getValeurPixel(pixel,0);
	couleur[1]=getValeurPixel(pixel,1);
	couleur[2]=getValeurPixel(pixel,2);
}

/**
* Ecriture d'un pixel dans une image
* @param Image(Image) où écrire le pixel
* @param Ligne(int): Abscisse du pixel à remplir
* @param Colonne(int): Ordonnée du pixel à remplir
* @param Couleur(unsigned char*) du pixel
*/

extern void image_write_pixel(Image pic, int ligne , int colonne, unsigned char* couleur)
{
    int i;

    Pixel pixel=getPixelImage(pic,ligne,colonne);
	setValeurPixel(pixel,couleur);
}

/**
* La fonction permet de dessiner les bordures d'un carré dans l'image selectionnée
* @brief Fonction dessinant un carré
* @param Image(Image) dans laquelle on veut dessiner le carré
* @param xmin(int) Abscisse Haut Gauche du carré
* @param ymin(int) Abscisse Haut Droite du carré
* @param xmax(int) Abscisse bas droite du carré
* @param ymax(int) Ordonnée bas droite du carré
* @param Couleur(unsigned char*) des bordures du carré
*/


extern void draw_square(Image pic, int xmin, int ymin, int xmax, int ymax, unsigned char* couleur) //x=ligne; y=colonne
{
	int i;

	for(i=xmin;i<=xmax;i++){
		image_write_pixel(pic,ymin,i,couleur);	
		image_write_pixel(pic,ymax,i,couleur);
	}
	for(i=ymin;i<=ymax;i++){
		image_write_pixel(pic,i,xmin,couleur);
		image_write_pixel(pic,i,xmax,couleur);
	}

	sauverImage(pic,"misc/imageModifie.ppm",INCONUE,INCOLORE);

}


/**
* Fonction qui calcul les moments d'une image
* @param Image(Image) à analyser
* @param xmin(int) Abscisse Haut Gauche de la section à analyser
* @param ymin(int) Abscisse Haut Droite de la section à analyser
* @param xmax(int) Abscisse bas droite de la section à analyser
* @param ymax(int) Ordonnée bas droite de la section à analyser
* @param ordre0(int*) :
* @param ordre1(double*)
* @param ordre2(double*)
*/

extern Ordre give_moments(image pic, int xmin, int ymin, int xmax, int ymax, int* ordre0, double* ordre1, double* ordre2)
{
    int i,j;
    int distAbs = xmin - xmax;
    int distOrd = ymax - ymin;
    unsigned char tab[2];
    int dim = image_give_dim(pic);

    Point p;

    COORDX(p) = xmin;
    COORDY(p) = ymin;


    ordre0[0] = (xmin-xmax)*(ymax-ymin);

    for (i = 0; i < distAbs; i++)
    {
        for (j = 0; j < distOrd ; j++)
        {
            image_move_to(pic, &p);
            image_read_pixel(pic, COORDX(p), COORDY(p), tab);
            if (dim == 3)
            {
                ordre1[0] = ordre1[0] + tab[0];
                ordre1[1] = ordre1[1] + tab[1];
                ordre1[2] = ordre1[2] + tab[2];
            }

            else
            {
                ordre1[0] = ordre1[0] + tab[0];
            }
            COORDY(p)++;
        }
        COORDX(p)++;
    }

    COORDX(p) = xmin;
    COORDY(p) = ymin;
    for (i = 0; i < distAbs; i++)
    {
        for (j = 0; j < distOrd ; j++)
        {
            image_move_to(pic, &p);
            image_read_pixel(pic, COORDX(p), COORDY(p), tab);
            if (dim == 3)
            {
                ordre1[0] = ordre1[0] + tab[0]*tab[0];
                ordre1[1] = ordre1[1] + tab[1]*tab[1];
                ordre1[2] = ordre1[2] + tab[2]*tab[2];
            }

            else
            {
                ordre1[0] = ordre1[0] + tab[0]*tab[0];
            }
            COORDY(p)++;
        }
        COORDX(p)++;
    }
}

