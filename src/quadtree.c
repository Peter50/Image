/**
* @file quadtree.c
* @author CHEN Denis - 1A Info ENSICaen
*/
#include "quadtree.h"
#include "image.h"

struct sQuadtree
{
    Quadtree sons[4];
    double M0, M1[3], M2[3];
};

/**
* Fonction initialisant un quadtree, les fils de l'arbre sont mis à NULL
* @return Quadtree
*/
extern Quadtree create_quadtree()
{
    Quadtree quadtree;

    int i;

    for (i = 0; i < 4; i++)
    {
        quadtree->sons[i] = NULL;
    }

    return quadtree;
}

/**
* Initialise les fils d'un quadtree
* @param Quadtree(Quadtree*) à diviser
*/
extern void quadtree_subdivide(Quadtree* quadtree)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        (*quadtree)->sons[i] = create_quadtree();
    }
}


/**
* Supprime un quadtree de manière récursive
* @param Quadtree(Quadtree*) à supprimer
*/
extern void delete_quadtree(Quadtree* quadtree)
{
    int i;

    
    for (i = 0; i < 4; i++)
    {
        if ((*quadtree)->sons[0] != NULL &&
            (*quadtree)->sons[1] != NULL &&
            (*quadtree)->sons[2] != NULL &&
            (*quadtree)->sons[3] != NULL)
        {
            delete_quadtree((*quadtree)->sons[i]);
        }
        (*quadtree) = NULL;
    }
}
