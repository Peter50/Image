#include "image.h"
#include "image_util.h"
#include "quadtree.h"
//#include "../include/image.h"
//#include "../include/quadAppDesc.h"



int main()
{
    FILE* canal = NULL;
    char* fichier = NULL;
    unsigned char couleur[2];
    unsigned char couleurCarre[2];
    int xmin, ymin, xmax, ymax;

    Image pic;
    Quadtree quadtree;

    pic = initImage();

/*
    printf("Rentrer l'image a etudier..\n");
    scanf("%s", fichier);
*/

    pic=chargerImage("misc/fille.ppm");
    //canal = fopen(fichier, "r");

    //couleur = malloc(3*sizeof(unsigned char));
/*
    image_read_pixel(pic, 1, 1, couleur);

    fflush(stdout);
*/     

    image_write_pixel(pic, 1, 1, couleurCarre);
 
 //RECTANGLE
    
    printf("\n\nTracage du carre: \n");
    printf("xmin: ");
    scanf("%d", &xmin);
    printf("ymin: ");
    scanf("%d", &ymin);
    printf("xmax: ");
    scanf("%d", &xmax);
    printf("ymax: ");
    scanf("%d", &ymax);

    couleurCarre[0] = 255;
    couleurCarre[1] = 255;
    couleurCarre[2] = 0;
    draw_square(pic, xmin, ymin, xmax, ymax, couleurCarre);

    detruireImage(pic);
    return 0;
}
