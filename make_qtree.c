/*
 * PROJ1-1: YOUR TASK B CODE HERE
 *
 * Feel free to define additional helper functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include "quadtree.h"
#include "make_qtree.h"
#include "utils.h"

#define ABS(x) (((x) < 0) ? (-(x)) : (x))
#define NON_LEAF 256

int homogenous(unsigned char *depth_map, int map_width, int x, int y, int section_width) {
    // declare range of iteration through memory
    int range = section_width * section_width;
    int start = x + (y * map_width);
    int hue = depth_map[start];

    // begin search for same val
    for (i = start; i < range - 1; i++) {
        if (!(depth_map[i] == hue)) {
            return NON_LEAF;
        }
    }
    // they must all be the same return the original hue
    return hue;
}

qNode *depth_to_quad(unsigned char *depth_map, int map_width) {
    // paranoid edge case 
    if (!*depth_map) {
        return NULL;
    }
}

void free_qtree(qNode *qtree_node) {
    if(qtree_node) {
        if(!qtree_node->leaf){
            free_qtree(qtree_node->child_NW);
            free_qtree(qtree_node->child_NE);
            free_qtree(qtree_node->child_SE);
            free_qtree(qtree_node->child_SW);
        }
        free(qtree_node);
    }
}
