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
#include <stdlib.h>

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
    //printf("max displacement is %d\n", maximum_displacement);

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
    int euc_dist_min=-1;
    int euc_index=0;
    int euc_pixel;
    int left_pixel;
    int euc_me=0;
    //located closest match
    int best_x;
    int best_y;

    //int i=feature_width+image_width*feature_height;
    //int j=(image_width*image_height-1)-image_width*feature_height-feature_width;
    int i = 0;
	while (i < image_height*image_width) {
		////printf("entered");
		//start comparing with other factors inside the box on the right image

		current_x = i % (image_width);
		current_y = (i-current_x)/image_width;
		
		//x+y*width=i
		
		//TODO maybe remove first half or OR?
		if (current_x-maximum_displacement < 0) {
			//big green box sticks over left edge
			xt=0;
		}
		else {
			xt=current_x-maximum_displacement;
		}
		if (current_x+maximum_displacement+2*feature_width > image_width-1) {
			//green box sticks over right edge
			x2=image_width-1-2*feature_width;
		}
		else{
			x2=current_x+maximum_displacement-2*feature_width;
		}
		if (current_y-maximum_displacement < 0) {
			//green box above top edge
			y=0;
		}
		else{
			y=current_y-maximum_displacement;
		}
		if (current_y+maximum_displacement+2*feature_height > image_height -1) {
			//green box below bottom edge
			y2=image_height-1-2*feature_height;
		}
		else{
			y2=current_y+maximum_displacement-2*feature_height;
		}

		//iterate on y from y=current_y+half_feature to current_y+max_disp-half_feature
		//iterate on x from x=current_x+half_feature to current_x + max_disp - half_feature

		best_x=current_x;
		best_y=current_y;
		//printf("scanning features around pixel (%d,%d)\n", current_x, current_y);
		//printf("ok big green box: x %d x2 %d y %d y2 %d\n", xt, x2, y, y2);
		if (current_x<feature_width || current_y<feature_height || current_x>(image_width-1)-feature_width || current_y>(image_height-1)-feature_height){
			////printf("yeah\n");
			depth_map[i]=0;
			i++;
			continue;
		}
		//TODO just determine how far right and how far down the box needs to go from the padded x calculated up top. then no need for actually figuring out the size of the giant green box.
		x=xt;
		while (y <= y2){
			while (x <= x2) {
				//printf("scanning feature whose center is (%d,%d)\n", x+feature_width, y+feature_height);
				//iterate through factor and contribute these values to the euclidian distance
				factor_x = x;
				factor_y = y;
				
				while (factor_y <= y+2*feature_height) {
					while (factor_x <= x+2*feature_width) {
						euc_pixel = factor_x+factor_y*image_width;
						left_pixel= ((current_x-feature_width)+(factor_x-x))+((current_y-feature_height)+(factor_y-y))*image_width;
						//printf("left pixel=%d right pixel=%d\n", left_pixel, euc_pixel);
						if (x+feature_width == current_x && y+feature_height == current_y){
							//printf("modifying euc dist\n");
							euc_me += (left[left_pixel]-right[euc_pixel])*(left[left_pixel]-right[euc_pixel]);
						}
						euc_index += (left[left_pixel]-right[euc_pixel])*(left[left_pixel]-right[euc_pixel]);

						//printf("currently (%d,%d)\n", factor_x, factor_y);
						//printf("feature width %d feature height %d\n", feature_width, feature_height);
						factor_x++;
					}
					factor_y++;
					factor_x=x; //reset factor_x
				}
				//printf("new euc calculated as %d\n", euc_index);
				if (euc_index == euc_dist_min) {
					if (normalized_displacement(best_x-current_x, best_y-current_y, maximum_displacement) > normalized_displacement((x+feature_width)-current_x, (y+feature_height)-current_y, maximum_displacement)){
						best_x=(x+feature_width);
						best_y=(y+feature_height);
					}
				}
				if (euc_index < euc_dist_min || euc_dist_min == -1) {
					euc_dist_min=euc_index;
					best_x=x+feature_width;
					best_y=y+feature_height;
					//printf("bestx=%d besty=%d\n", best_x, best_y);
				}
				x++;
				euc_index=0;
				//euc_me=0;
			}
			y++;
			x=xt; //reset x

		}
		if (euc_dist_min==euc_me) {
			//printf("eucdist %d\n", euc_dist_min);
			best_x=current_x;
			best_y=current_y;
		}
		//printf("best match for left's x=%d y=%d is x=%d y=%d\n", current_x, current_y, best_x, best_y);
		//printf("using parameters dx=%d dy=%d\n", best_x-current_x, best_y-current_y);
		depth_map[i] = normalized_displacement(best_x-current_x, best_y-current_y, maximum_displacement);
		i++;
		euc_dist_min=-1;
		euc_me=0;
	}
}


// function idea
//returns array of x-displacements to form the feature box around on the right image
// x is the current pixel's x value
