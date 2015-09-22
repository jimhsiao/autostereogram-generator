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

int homogenous(unsigned char *depth_map, int map_width, int x, int y, int section_width) {

    unsigned char *tempPointer = depth_map;
    unsigned char in2d[map_width][map_width];
    for (int i = 0; i < map_width; i++) {
        for (int j = 0; j < map_width; j++) {
            in2d[i][j] = *tempPointer;
            tempPointer = tempPointer + 1;
        }
    }

    /* YOUR CODE HERE */
    int col = in2d[x][y];
    if(((x + section_width) > map_width) & ((y + section_width) > map_width)) {
        for(int i = x; i < map_width; i++) {
            for(int j = y; j < map_width; j++) {
                if(col != in2d[i][j]) {
                    return 0;
                }
            }
        }
    }
    if(x + section_width > map_width) {
        for(int i = x; i < map_width; i++) {
            for(int j = y; j < y + section_width; j++) {
                if(col != in2d[i][j]) {
                    return 0;
                }
            }
        }
    } else if(y + section_width > map_width) {
        for(int i = x; i < x + section_width; i++) {
            for(int j = y; j < map_width; j++) {
                if(col != in2d[i][j]) {
                    return 0;
                }
            }
        }
    } else {
        for(int i = x; i < x + section_width; i++) {
            for(int j = y; j < y + section_width; j++) {
                if(in2d[i][j] != col) {
                    return 0;
                }
            }
        }
    }
    return 1;

}

qNode *restOfNode(unsigned char *depth_map, int map_width, int xCor, int yCor, int size) {
    unsigned char *temp = depth_map;
    unsigned char in2d[map_width][map_width];
    for (int i = 0; i < map_width; i++) {
        for (int j = 0; j < map_width; j++) {
            in2d[i][j] = *temp;
            temp = temp + 1;
        }
    }
    qNode *curr = malloc(sizeof(qNode));
    curr->x = xCor;
    curr->y = yCor;
    curr->size = size;
    if(homogenous(depth_map, map_width, xCor, yCor, size)) {
        curr->leaf = 1;
        int temp = in2d[xCor][yCor];
        curr->gray_value = *(depth_map + xCor + yCor * map_width);
        curr->child_NW = NULL;
        curr->child_NE = NULL;
        curr->child_SW = NULL;
        curr->child_SE = NULL;
    } else {
        curr->leaf = 0;
        curr->gray_value = 256;
        curr->child_NW = restOfNode(depth_map, map_width, xCor, yCor, size/2);
        curr->child_NE = restOfNode(depth_map, map_width, xCor + size/2, yCor, size/2);
        curr->child_SW = restOfNode(depth_map, map_width, xCor, yCor + size/2, size/2);
        curr->child_SE = mrestOfNode(depth_map, map_width, xCor + size/2, yCor + size/2, size/2);
    }
    return curr;
}

qNode *depth_to_quad(unsigned char *depth_map, int map_width) {

    /* YOUR CODE HERE */
    if(map_width == 1) {
        qNode *curr = malloc(sizeof(qNode));
        curr->x = 0;
        curr->y = 0;
        curr->size = 1;
        curr->leaf = 1;
        curr->gray_value = *depth_map;
        return curr;
    } else {
        return restOfNode(depth_map, map_width, 0, 0, map_width);
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
