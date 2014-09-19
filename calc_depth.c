/*
 * PROJ1-1: YOUR TASK A CODE HERE
 *
 * Feel free to define additional helper functions.
 */

#include "calc_depth.h"
#include "utils.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

/* Implements the normalized displacement function */
unsigned char normalized_displacement(int dx, int dy,
        int maximum_displacement) {

    double squared_displacement = dx * dx + dy * dy;
    double normalized_displacement = round(255 * sqrt(squared_displacement) / sqrt(2 * maximum_displacement * maximum_displacement));
    return (unsigned char) normalized_displacement;

}

void calc_depth(unsigned char *depth_map, unsigned char *left,
        unsigned char *right, int image_width, int image_height,
        int feature_width, int feature_height, int maximum_displacement) {

    /* YOUR CODE HERE */
    //loop through each pixel in left
    if (feature_hight > maximum_displacement || feature_width > maximum_displacement) {
    	printf("feature height larger than displacement box\n");
    }

    // calculate parameters to build feature
    int h_factor_pos = (feature_width - 1)/2; //add or subtract these from current_pixel
    int h_factor_neg = (feature_width - 1)/2 + feature_width % 2; //in case it's even
    int v_factor_pos = (feature_height -1)/2;
    int v_factor_neg = (feature_height -1)/2 + feature_height %2;

    //calculate parameters to build displacement box on right image
    int box_width = 2(feature_width) + 1;
    int box_height = 2(feature_height) + 1
    int disp_h_factor_pos = ((i % box_width) -1)/2;
    int disp_h_factor_neg = ((i % box_width) -1)/2 + feature_width % 2;
    int disp_v_factor_pos = ((i % box_height) -1)/2;
    int disp_v_factor_neg = ((i % box_height) -1)/2 + feature_height % 2;


	while (left[i] != '\0') {
		//start comparing with other factors inside the box on the right image

	}
}

