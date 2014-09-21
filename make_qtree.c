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
    for (int i = start; i < range - 1; i++) {
        if (!(depth_map[i] == hue)) {
            return NON_LEAF;
        }
    }
    // they must all be the same return the original hue
    return hue;
}

qNode *quad_help(unsigned char *quadrant, int quad_width, int x, int y) {
    // recursively creates qNodes and assigns pointers.
    if (homogenous(quadrant, quad_width, x, y, quad_width) != NON_LEAF) {
        // base case assign leaf node and NULL children pointers
        qNode *leaf = (qNode *)malloc(sizeof(qNode));
        // set traits of LEAF
        leaf->leaf = 1;
        leaf->size = quad_width;
        leaf->x = x;
        leaf->y = y;
        leaf->gray_value = quadrant[0];
        (*leaf).child_NW = NULL;
        (*leaf).child_NE = NULL;
        (*leaf).child_SE = NULL;
        (*leaf).child_SW = NULL;
        return leaf;
    } else {
        qNode *branch = (qNode *)malloc(sizeof(qNode));
        // set traits of NON_LEAF
        branch->leaf = 0;
        branch->size = quad_width;
        branch->x = x;
        branch->y = y;
        branch->gray_value = NON_LEAF;
        (*branch).child_NW = quad_help(quadrant, quad_width / 2, 0, 0);
        (*branch).child_NE = quad_help(quadrant, quad_width / 2, (quad_width / 2), 0);
        (*branch).child_SE = quad_help(quadrant, quad_width / 2, (quad_width / 2), (quad_width / 2));
        (*branch).child_SW = quad_help(quadrant, quad_width / 2, 0, (quad_width / 2));
        return branch;
    }
}

qNode *depth_to_quad(unsigned char *depth_map, int map_width) {
    // paranoid edge case 
    // base case call helper
    return quad_help(depth_map, map_width, 0, 0);
}

// DO NOT MODIFY
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
