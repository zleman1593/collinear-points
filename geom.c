#include "geom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/* **************************************** */
/* returns the signed area of triangle abc. The area is positive if c
 is to the left of ab, and negative if c is to the right of ab
 */
int signed_area2D(point2D a, point2D b, point2D c) {
    
    return 1;
}



/* **************************************** */
/* return 1 if p,q,r collinear, and 0 otherwise */
int collinear(point2D p, point2D q, point2D r) {
    
    return 1;
}



/* **************************************** */
/* return 1 if c is  strictly left of ab; 0 otherwise */
int left (point2D a, point2D b, point2D c) {
    
    return 1;
}
/* **************************************** */
/* return all triplets of colinear points as an array using the
 straightforward algorithm that runs in cubic time
 */
void find_collinear_straightforward(point2D* p, int n) {

    
    /*
    printf("(%i,%i,)\n",p[74].x,p[74].y);
    printf("(%i,%i,)\n",p[306].x,p[306].y);
    printf("(%i,%i,)\n",p[383].x,p[383].y);
    */
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            //Make sure first two points are not identical
            if(i != j){
                double slope = 0;
                double denominator = (p[j].x - p[i].x );
                if (denominator != 0) {
                    slope = ((double) p[j].y - (double)p[i].y)/(denominator);
                    
                    double  yIntercept =   (double)p[i].y - (slope*(double)p[i].x);
                    
                    for (int k = j+1; k < n; k++){
                        if((k != j)  && (k != i)){

                            
                            //Check to see if third point is colinear with line segement of first two points
                            if(  (( (slope*(double)p[k].x) +  yIntercept)  -  (double)p[k].y ) == 0){
                                printf("Points: %i, %i, %i\n",i,j,k);
                                
                            }
                        }
                    }
                    
                } else {
                    // printf("Vertical: Undefined slope");
                    for (int k = j+1; k < n; k++){
                        if((k != j)  && (k != i)){
                            /*Check if point k has a shared x coordinate with one of the other two points*/
                            if (p[i].x == p[k].x) {
                                printf("Vertical line segment. Points: %i, %i, %i \n",i,j,k);
                            }
                        }
                    }
                    
                    
                }
                
                
                
            }
            
        }
    }
    
    
    
    
    assert(p);
    int ncol=0; //nb distinct  collinear triplets
    
    
    
    
    
    
    
    
    
    printf("find_collinear_straightforward: total %d distinct collinear triplets (out of max %ld triplets)\n", ncol, (long int) ((long int)n*(long int)(n-1)*(long int)(n-2))/6);
    fflush(stdout);
}




int vertical (point2D a, point2D b) {
    
    if (a.x == b.x) return 1;
    return 0;
}


/* **************************************** */
/* return all triplets of colinear points as an array using the
 improved algorithm that runs in O(n^2 lg n) time
 
 
 */
void find_collinear_improved(point2D* p, int n) {
    
    assert(p);
    int ncol=0; //nb distinct collinear triplets
    
    //.....
    
    printf("find_collinear_improved: total %d distinct collinear triplets (out of max %ld triplets)\n", ncol, (long int) ((long int)n*(long int)(n-1)*(long int)(n-2))/6);
    fflush(stdout);
}

