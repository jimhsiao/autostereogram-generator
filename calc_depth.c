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

    int leftImage[image_width][image_height];  /* Transferring to an array */
    for (int i = 0; i < image_width; i++) {
    	for (int j = 0; j < image_height; j++) {
    		leftImage[i][j] = *left;
    		left = left + 1;
    	}
    }


 /*   for(int i = 0; i < image_width; i++) {
    for(int j = 0; j < image_height; j++) {
        printf("%d ", leftImage[i][j]);
    }
    printf("\n");
 }
printf("\n");
printf("\n"); */
    int rightImage[image_width][image_height];    
    for (int i = 0; i < image_width; i++) {
    	for (int j = 0; j < image_height; j++) {
    		rightImage[i][j] = *right;
    		right = right + 1;
    	}
    }


 /*       for(int i = 0; i < image_width; i++) {
    for(int j = 0; j < image_height; j++) {
        printf("%d ", rightImage[i][j]);
    }
    printf("\n");
}  */

	int first = 1;
	int currentMin;
	int minX;
	int minY;
/*	printf("feature width is ");
	printf("%d",feature_width);
	printf("\n");
	printf("feature height is ");
	printf("%d",feature_height);
	printf("\n");
	printf("image_width is: ");
	printf("%d",image_width);
	printf("\n");
	printf("image_height is: ");
	printf("%d",image_height);
	printf("\n");
	printf("maximum_displacement is: ");
	printf("%d",maximum_displacement);
	printf("\n"); */
	int curDisplacement;
for (int i = 0; i < image_width; i++) {
	for (int j = 0; j < image_height; j++) {  
	first = 1;       
		if ((i - feature_width < 0) | (i + feature_width > image_width) | (j - feature_height < 0) | (j + feature_height > image_height)) {        /* if part of feature lies outside image, set corresponding depth to zero and move on to next pixel */
			*depth_map = 0;
			depth_map = depth_map + 1;
		}
		else {
			for (int x = i - maximum_displacement; x <= i + maximum_displacement; x++) {        /* x and y loop through the "search space" surrounding the pixel */
				for (int y = j - maximum_displacement; y <= j + maximum_displacement; y++) {
					if ((x - feature_width < 0) | (x + feature_width > image_width) | (y - feature_height < 0) | (y + feature_height > image_height)) {

				}
					else {  	
						int leftImageSum[2*feature_width + 1][2*feature_height+1];
						int *pointer;
						pointer = &leftImageSum[0][0];
						for (int a = i - feature_width; a <= i + feature_width; a++) {
							for (int b = j - feature_height; b <= j + feature_height; b++) {
									*pointer = leftImage[a][b];
									pointer = pointer + 1;
							}
						}		
						int currentSum[2*feature_width + 1][2*feature_height+1];
						int *pointer1;
						pointer1 = &currentSum[0][0];
						for (int a  = x - feature_width; a <= x + feature_width; a++) {
							for (int b = y - feature_height; b <= y + feature_height; b++) {
								*pointer1 = rightImage[a][b];
								pointer1 = pointer1 + 1;
							}
						}
						int EuclidianSum = 0;
						for (int a = 0; a < 2*feature_width + 1; a++) {
							for (int b = 0; b < 2*feature_height + 1; b++) {
								EuclidianSum = EuclidianSum + (leftImageSum[a][b] - currentSum[a][b])*(leftImageSum[a][b] - currentSum[a][b]);
							}
						}
						int tempDisplacement = normalized_displacement(x-i,y-j,maximum_displacement);
				if (first) {
					currentMin = EuclidianSum;
					minX = x;
					minY = y;
					first = 0;
					curDisplacement = tempDisplacement;
					}
				else if (EuclidianSum < currentMin) {
					currentMin = EuclidianSum;
					minX = x;
					minY = y;
					curDisplacement = tempDisplacement;
				}
				else if ((EuclidianSum == currentMin) & (tempDisplacement < curDisplacement)) {
					currentMin = EuclidianSum;
					minX = x;
					minY = y;
					curDisplacement = tempDisplacement;
				}
				}
			}
		}


/* printf("Setting graph depth to: ");
*depth_map = normalized_displacement(minX-i,minY-j,maximum_displacement);   /* After looping through every feature in the search space, assign the value to depth map */
depth_map = depth_map + 1;
}
}
}
}