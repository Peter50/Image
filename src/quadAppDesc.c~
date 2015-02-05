/**
* @file quadAppDesc.c
* @author CHEN Denis - 1A Info ENSICaen
*/

#include "image.h"
#include "quadtree.h"
#include "quadAppDesc.h"

/**
* Divise une image dans que la variance est supérieure à un seuil défini
* @param Image(Image) Image à diviser
* @param Seuil(double) Seuil pour arrêter la division
* @return Quadtree
*/
extern Quadtree split_image(Image pic, double seuil)
{
    Quadtree quadtree = create_quadtree();
    int* M0 = NULL;
    double* M1 = NULL;
    double* M2 = NULL;
    int largeur = image_give_largeur(pic);
    int hauteur = image_give_hauteur(pic);

    give_moments(image, xmin, ymin, xmax, ymax, M0, M1, M2);


    var = ((*M2) - ((*M1)*(*M1) /(*M0) ) / (*M0);





//    for (i = 0; i < 4; i++)
 //   {
        
        give_moments(image, xmin, ymin, xmax, ymax, M0, M1, M2);

        if ( var < seuil)
        {
            quadtree.sons[i] = split_image(quadtree.sons[i], seuil);
        }
  //  }
    
    return quadtree;
}


//Quadtree = split_image
extern void draw_quadtree(Image pic, Quadtree quadtree, unsigned char* couleur)
{
    int xmin, ymin, xmax, ymax;
    xmin = 0;
    xmax = image_give_largeur(pic);
    ymin = image_give_hauteur(pic);
    ymax = 0;

    if (quadtree->sons[0] != NULL &&
        quadtree->sons[1] != NULL &&
        quadtree->sons[2] != NULL &&
        quadtree->sons[3] != NULL)
    {
        draw_square(pic, xmin, ymin/2, xmax/2, ymax);
        draw_square(pic, xmax/2, ymin/2, xmax, ymax);
        draw_square(pic, xmin, ymin/2, xmax/2, ymin/2);
        draw_square(pic, xmax/2, ymin/2, xmax/2, ymax);
        draw_quadtree(pic, quadtree->sons[0], couleur);
        draw_quadtree(pic, quadtree->sons[1], couleur);
        draw_quadtree(pic, quadtree->sons[2], couleur);
        draw_quadtree(pic, quadtree->sons[3], couleur);
    }
    





}
