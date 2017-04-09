/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */
student_t student = {
    "Muntadher AlZayer",     /* First member full name */
    "mual3154@colorado.edu"  /* First member email address */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/
 
/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim; j++){
            dst[RIDX(dim-1-j, i, dim)].red   = src[RIDX(i, j, dim)].red;
            dst[RIDX(dim-1-j, i, dim)].green = src[RIDX(i, j, dim)].green;
            dst[RIDX(dim-1-j, i, dim)].blue  = src[RIDX(i, j, dim)].blue;
        }
    }
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
	int i, j;
	int buff = dim*dim;
	
	dst += buff - dim;
	for(i=0 ; i <dim ; i +=32){
	
		for(j = 0; j < dim; j++){
			*dst = *src;
			src +=dim;
		
			*(dst+1) = *src;
			src +=dim;

			*(dst+2) = *src;
			src +=dim;
		
			*(dst+3) = *src;
			src +=dim;
		
			*(dst+4) = *src;
			src +=dim;
		
			*(dst+5) = *src;
			src +=dim;
		
			*(dst+6) = *src;
			src +=dim;
		
			*(dst+7) = *src;
			src +=dim;
		
			*(dst+8) = *src;
			src +=dim;
		
			*(dst+9) = *src;
			src +=dim;
		
			*(dst+10) = *src;
			src +=dim;
		
			*(dst+11) = *src;
			src +=dim;
		
			*(dst+12) = *src;
			src +=dim;
		
			*(dst+13) = *src;
			src +=dim;
		
			*(dst+14) = *src;
			src +=dim;
		
			*(dst+15) = *src;
			src +=dim;
		
			*(dst+16) = *src;
			src +=dim;
		
			*(dst+17) = *src;
			src +=dim;
		
			*(dst+18) = *src;
			src +=dim;
		
			*(dst+19) = *src;
			src +=dim;
		
			*(dst+20) = *src;
			src +=dim;
		
			*(dst+21) = *src;
			src +=dim;
		
			*(dst+22) = *src;
			src +=dim;
		
			*(dst+23) = *src;
			src +=dim;
		
			*(dst+24) = *src;
			src +=dim;
		
			*(dst+25) = *src;
			src +=dim;
		
			*(dst+26) = *src;
			src +=dim;
		
			*(dst+27) = *src;
			src +=dim;
		
			*(dst+28) = *src;
			src +=dim;
		
			*(dst+29) = *src;
			src +=dim;
		
			*(dst+30) = *src;
			src +=dim;
		
			*(dst+31) = *src;
		
			dst -= dim;
			src -=dim*31 - 1;
		}
		dst += 32+buff;
		src += dim*31;
	}
	return;
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/
 
/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* Compute min of two integers */
static int min(int a, int b) {
    if(a<b){
        return a;
    }else{
        return b;
    }
}

/* Compute max of two integers */
static int max(int a, int b) {
    if(a>b){
        return a;
    }else{
        return b;
    }
}

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum){
    sum->red = 0;
    sum->green = 0;
    sum->blue = 0;
    sum->num = 0;
}

static void accumulate_sum(pixel_sum *sum, pixel p){
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
}
/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j, ii, jj;
    pixel_sum ps;
    
    for (j = 0; j < dim; j++){
        for (i = 0; i < dim; i++){
            initialize_pixel_sum(&ps);
            for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++){
                for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++){
                    accumulate_sum(&ps, src[RIDX(ii,jj,dim)]);
                }
            }
            dst[RIDX(i,j,dim)].red   = ps.red/ps.num;
            dst[RIDX(i,j,dim)].green = ps.green/ps.num;
            dst[RIDX(i,j,dim)].blue  = ps.blue/ps.num;
        }
    }
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
	int i, j, myJ;
    //four corners
	dst[0].red = (src[0].red + src[1].red + src[dim+1].red + src[dim].red)>>2;
	dst[0].blue = (src[0].blue + src[1].blue + src[dim].blue + src[dim+1].blue)>>2;
	dst[0].green = (src[0].green + src[1].green + src[dim].green + src[dim+1].green)>>2;
    
	i = dim*2-1;
	dst[dim-1].red = (src[dim-2].red + src[dim-1].red + src[i-1].red + src[i].red)>>2;
	dst[dim-1].blue = (src[dim-2].blue + src[dim-1].blue + src[i-1].blue + src[i].blue)>>2;
	dst[dim-1].green = (src[dim-2].green + src[dim-1].green + src[i-1].green + src[i].green)>>2;
    
	j = dim*(dim-1);
    	i = dim*(dim-2);
    	dst[j].red = (src[j].red + src[j + 1].red + src[i].red + src[i + 1].red)>>2;
    	dst[j].blue = (src[j].blue + src[j + 1].blue + src[i].blue + src[i + 1].blue)>>2;
    	dst[j].green = (src[j].green + src[j + 1].green + src[i].green + src[i + 1].green)>>2;
    
    	j = dim*dim-1;
    	i = dim*(dim-1)-1;
    	dst[j].red = (src[j - 1].red + src[j].red + src[i - 1].red + src[i].red)>>2;
    	dst[j].blue = (src[j - 1].blue + src[j].blue + src[i - 1].blue + src[i].blue)>>2;
   	dst[j].green = (src[j - 1].green + src[j].green + src[i - 1].green + src[i].green)>>2;
    	//end of four corners
    	i = dim - 1;
   	for (j = 1; j < i; j++) 
   	{
       		 dst[j].red = (src[j].red+src[j-1].red+src[j+1].red+src[j+dim].red+src[j+1+dim].red+src[j-1+dim].red)/6;
      		 dst[j].green = (src[j].green+src[j-1].green+src[j+1].green+src[j+dim].green+src[j+1+dim].green+src[j-1+dim].green)/6;
      		 dst[j].blue = (src[j].blue+src[j-1].blue+src[j+1].blue+src[j+dim].blue+src[j+1+dim].blue+src[j-1+dim].blue)/6;
   	}
    
    	i = dim*dim-1;
   	for (j = i - dim + 2; j < i; j++) 
   	{
       		 dst[j].red = (src[j].red + src[j-1].red + src[j+1].red + src[j-dim].red + src[j+1-dim].red + src[j-1-dim].red)/6;
      		 dst[j].green = (src[j].green + src[j-1].green + src[j+1].green + src[j-dim].green + src[j+1-dim].green + src[j-1-dim].green)/6;
    		 dst[j].blue = (src[j].blue + src[j-1].blue + src[j+1].blue + src[j-dim].blue + src[j+1-dim].blue + src[j-1-dim].blue)/6;
   	}
    
   	for (j = dim+dim-1; j < dim*dim-1; j+=dim)
   	{
		dst[j].red = (src[j].red + src[j-1].red + src[j-dim].red + src[j+dim].red + src[j-dim-1].red + src[j-1+dim].red)/6;
        	dst[j].green = (src[j].green + src[j-1].green + src[j-dim].green + src[j+dim].green + src[j-dim-1].green + src[j-1+dim].green)/6;
        	dst[j].blue = (src[j].blue + src[j-1].blue + src[j-dim].blue + src[j+dim].blue + src[j-dim-1].blue + src[j-1+dim].blue)/6;
    	}

    	i = i - (dim - 1);
    	for (j = dim; j < i; j+=dim)
     	{
        	dst[j].red = (src[j].red + src[j-dim].red + src[j+1].red + src[j+dim].red + src[j+1+dim].red + src[j-dim+1].red)/6;
        	dst[j].green = (src[j].green + src[j-dim].green + src[j+1].green + src[j+dim].green + src[j+1+dim].green + src[j-dim+1].green)/6;
        	dst[j].blue = (src[j].blue + src[j-dim].blue + src[j+1].blue + src[j+dim].blue + src[j+1+dim].blue + src[j-dim+1].blue)/6;
	}
    
    	myJ = dim;

    	for (i = 1; i < dim-1; i++)
    	{
		for (j = 1; j < dim-1; j++)
	    	{
            		myJ ++;
            		dst[myJ].red = (src[myJ-1].red + src[myJ].red + src[myJ+1].red + src[myJ-dim-1].red + src[myJ-dim].red + src[myJ-dim+1].red + src[myJ+dim-1].red + src[myJ+dim].red + src[myJ+dim+1].red)/9;
           		dst[myJ].green = (src[myJ-1].green + src[myJ].green + src[myJ+1].green + src[myJ-dim-1].green + src[myJ-dim].green + src[myJ-dim+1].green + src[myJ+dim-1].green + src[myJ+dim].green + src[myJ+dim+1].green)/9;
            		dst[myJ].blue = (src[myJ-1].blue + src[myJ].blue + src[myJ+1].blue + src[myJ-dim-1].blue + src[myJ-dim].blue + src[myJ-dim+1].blue + src[myJ+dim-1].blue + src[myJ+dim].blue + src[myJ+dim+1].blue)/9;
        	}
        	myJ += 2;
    	}
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

