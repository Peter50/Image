#ifndef IMAGE_UTIL_H_INCLUDED
#define IMAGE_UTIL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "image.h"

//////////
// Fonctions lire et ecrire une valeur de pixel dans image
extern void image_read_pixel(image pic, int ligne, int colonne, unsigned char* couleur);
extern void image_write_pixel(image pic, int ligne , int colonne, unsigned char* couleur);


//////////
// Dessine un rectangle dans une image
//(xmin,ymin) -> Haut Gauche
// (xmax,ymax) -> Bas Droite
extern void draw_square(image pic, int xmin, int ymin, int xmax, int ymax, unsigned char* couleur);


/////////
// Calcul des moments d'ordre 0,1 et 2 des pixls dans un rect

extern void give_moments(image pic, int xmin, int ymin, int xmax, int ymax, int* ordre0, double* ordre1, double* ordre2);




#endif // IMAGE_UTIL_H_INCLUDED
