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
    printf("max displacement is %d\n", maximum_displacement);
    if (feature_height > maximum_displacement || feature_width > maximum_displacement) {
    	printf("feature height larger than displacement box\n");
    }

    // calculate parameters to build feature
    //calculate parameters to build displacement box on right image
    //int box_dim = 2*(maximum_displacement) + 1;

    int current_x;
    int current_y;
    int x=0;
    int xt=0;
    int x2=0;
    int y=0;
    int y2=0;
    int factor_x;
    int factor_y;
    int euc_dist_min=55;
    int euc_index;
    int euc_pixel;
    //located closest match
    int best_x;
    int best_y;

    //int i=feature_width+image_width*feature_height;
    //int j=(image_width*image_height-1)-image_width*feature_height-feature_width;
    int i = 0;
	while (i < image_height*image_width) {
		//printf("entered");
		//start comparing with other factors inside the box on the right image

		current_x = i % (image_width);
		current_y = (i-current_x)/image_width;
		
		//x+y*width=i
		
		//TODO maybe remove first half or OR?
		if (current_x-maximum_displacement < 0 || current_x-feature_width < 0) {
			//big green box sticks over left edge
			xt=feature_width;
		}
		else {
			xt=current_x-maximum_displacement;
		}
		if (current_x+maximum_displacement > image_width-1 || current_x+feature_width > image_width-1) {
			//green box sticks over right edge
			x2=feature_width+image_width-1;
		}
		else{
			x2=current_x+maximum_displacement-2*feature_width;
		}
		if (current_y-maximum_displacement < 0 || current_y-feature_height < 0) {
			//green box above top edge
			y=feature_height;
		}
		else{
			y=current_y-maximum_displacement;
		}
		if (current_y+maximum_displacement > image_height -1 || current_y+feature_height > image_height -1) {
			//green box below bottom edge
			y2=feature_height+image_height-1;
		}
		else{
			y2=current_y+maximum_displacement-2*feature_height;
		}

		//iterate on y from y=current_y+half_feature to current_y+max_disp-half_feature
		//iterate on x from x=current_x+half_feature to current_x + max_disp - half_feature

		best_x=current_x;
		best_y=current_y;
		printf("scanning features around pixel (%d,%d)\n", current_x, current_y);
		printf("ok big green box: x %d x2 %d y %d y2 %d\n", xt, x2, y, y2);
		//TODO just determine how far right and how far down the box needs to go from the padded x calculated up top. then no need for actually figuring out the size of the giant green box.
		x=xt;
		while (y <= y2){
			while (x <= x2) {
				printf("scanning feature whose center is (%d,%d)\n", x+feature_width, y+feature_width);
				//iterate through factor and contribute these values to the euclidian distance
				factor_x = x;
				factor_y = y;
				
				while (factor_y <= y+2*feature_height) {
					while (factor_x <= x+2*feature_width) {
						euc_pixel = factor_x+factor_y*image_width;
						euc_index += (left[i]-right[euc_pixel])*(left[i]-right[euc_pixel]);
						printf("currently (%d,%d)\n", factor_x, factor_y);
						printf("feature width %d feature height %d\n", feature_width, feature_height);
						factor_x++;
					}
					factor_y++;
					factor_x=x; //reset factor_x
				}
				printf("new euc calculated as %d\n", euc_index);
				if (euc_index < euc_dist_min) {
					euc_dist_min=euc_index;
					best_x=x+feature_width;
					best_y=y+feature_width;
				}
				x++;
				euc_index=0;
			}
			y++;
			x=xt; //reset x

		}
		printf("best match for left's x=%d y=%d is x=%d y=%d\n", current_x, current_y, best_x, best_y);
		depth_map[i] = normalized_displacement(best_y-current_y, best_x-current_x, maximum_displacement);
		i++;
	}
}


// function idea
//returns array of x-displacements to form the feature box around on the right image
// x is the current pixel's x value
