#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct sQuadtree * Quadtree;

extern Quadtree create_quadtree();

extern void quadtree_subdivide(Quadtree* quadtree);

extern void delete_quadtree(Quadtree* quadtree);

#endif // QUADTREE_H_INCLUDED
