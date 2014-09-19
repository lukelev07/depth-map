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
    //calculate parameters to build displacement box on right image
    int box_dim = 2(maximum_displacement) + 1;

    int current_x;
    int current_y;
    int x;
    int y;
    int factor_x;
    int factor_y;
    int euc_dist_min;
    int euc_index;

    int i=feature_width+image_width*feature_height;
    int j=(image_width*image_height-1)-image_width*feature_height-feature_width;
	while (i <= j) {
		//start comparing with other factors inside the box on the right image
		if (i == '\0') {
			printf("wat, got to end\n");
		}
		current_x = i % image_width;
		current_y = (i-current_x)/image_width;
		
		//x+y*width=i

		if (current_x-feature_width-maximum_displacement < 0) {
			//big green box sticks over left edge
			x=(maximum_displacement)
		}
		if (current_x+feature_width+maximum_displacement > image_width-1) {
			//green box sticks over right edge
		}
		if (current_y-feature_width-maximum_displacement < 0) {
			//green box above top edge
		}
		if (current_y+feature_height+maximum_displacement > image_height -1) {
			//green box below bottom edge
		}

		//iterate on y from y=current_y+half_feature to current_y+max_disp-half_feature
		//iterate on x from x=current_x+half_feature to current_x + max_disp - half_feature
		else {
			x=current_x+h_factor_neg-(box_dim-1)/2;
			y=current_y+v_factor_neg-(box_dim-1)/2;
		}
		while (y < current_y-v_factor_pos+(box_dim-1)/2){
			while (x < current_x-h_factor_pos+(box_dim-1)/2) {
				//iterate through factor and contribute these values to the euclidian distance
				factor_x = current_x;
				factor_y = current_y;
				
				while (factor_y < y+v_factor_pos) {
					while (factor_x < x+h_factor_pos) {
						euc_pixel = factor_x+factor_y*image_width;
						euc_index += (left[euc_pixel]-right[euc_pixel])*(left[euc_pixel]-right[euc_pixel]);
						factor_x++;
					}
					factor_y++;
				}
				if (euc_index < euc_dist_min) {
					euc_dist_min=euc_index;
				}
				x++;
			}
			y++;
		}
		i++;
	}
}

// function idea
//returns array of x-displacements to form the feature box around on the right image
// x is the current pixel's x value
