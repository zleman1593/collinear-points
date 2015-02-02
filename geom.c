#include "geom.h"
#include <float.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Line segment representation */
struct LnSegment {
    double slope;
    double x1;
    double y1;
    double x2;
    double y2;
};

/*Quick sort functions*/

int cmpfunc (const void * a, const void * b) {
    /*Type cast*/
    struct LnSegment * x = (struct LnSegment*) a;
    struct LnSegment * y = (struct LnSegment*) b;
    
    return ( x->slope - y->slope );
}

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

/**/
int is_colinear(double x, double y, double slope, double y_intercept) {
    return (slope * x +  y_intercept  -  y) == 0;
}

/* **************************************** */
/* return all triplets of colinear points as an array using the
 straightforward algorithm that runs in cubic time
 */
void find_collinear_straightforward(point2D* p, int n) {
    assert(p);
    int ncol = 0; //nb distinct  collinear triplets

    for (int i = 0; i < n; i++) {
        point2D p1 = p[i];
        
        for (int j = i + 1; j < n; j++) {
            point2D p2 = p[j];
            
            // Make sure we are checking different points
            if(i != j) {
                double slope = calc_slope(p1.x, p1.y, p2.x, p2.y);
                double yIntercept = calc_y_intercept(p1.x, p1.y, slope);
                
                // If the slope is not vertical
                if (slope < DBL_MAX) {
                    for (int k = j + 1; k < n; k++) {
                        if((k != j) && (k != i)){
                            // Get third point
                            point2D p3 = p[k];
                            //Check to see if third point is colinear with line segement of first two points
                            if (is_colinear(p3.x, p3.y, slope, yIntercept)) {
                                ncol++;
                                printf("Points: %i, %i, %i\n", i, j, k);
                            }
                        }
                    }
                } else {
                    // Vertical slope
                    // printf("Vertical: Undefined slope");
                    for (int k = j + 1; k < n; k++) {
                        // Check if point k has a shared x coordinate with the other two points
                        if ((k != j)  && (k != i) && (p1.x == p[k].x)) {
                            ncol++;
                            printf("Vertical line segment. Points: %i, %i, %i \n", i, j, k);
                        }
                    }
                }
            }
        }
    }
    
    printf("find_collinear_straightforward: total %d distinct collinear triplets (out of max %ld triplets)\n", ncol, (long int) ((long int)n*(long int)(n-1)*(long int)(n-2))/6);
    fflush(stdout);
}

/* Checks if two points are on a vertical line
 */
int vertical(point2D a, point2D b) {
    if (a.x == b.x) {
        return 1;
    }
    return 0;
}

/* Returns the slope
   Returns DBL_MAX if the slope is vertical
 */
double calc_slope(double x1, double y1, double x2, double y2) {
    double denominator = x1 - x2;
    if (denominator != 0) {
        return (y1 - y2) / denominator;
    }
    return DBL_MAX;
}

/* Reutrns the y-intercept
 */
double calc_y_intercept(double x, double y, double slope) {
    return y - (slope * x);
}

/* Check if two line segments share a point
 */
int share_point(struct LnSegment l1, struct LnSegment l2) {
    return (l1.x1 == l2.x1 && l1.y1 == l2.y1) ||
           (l1.x1 == l2.x2 && l1.y1 == l2.y2) ||
           (l1.x2 == l2.x1 && l1.y2 == l2.y1) ||
           (l1.x2 == l2.x2 && l1.y2 == l2.y2);
}

/* **************************************** */
/* return all triplets of colinear points as an array using the
 improved algorithm that runs in O(n^2 lg n) time and O(n) memory 
 */
void find_collinear_improved(point2D* p, int n) {
    assert(p);
    int ncol = 0; //nb distinct collinear triplets

    for (int i = 0; i < n; i++) {
        point2D p1 = p[i];
        
        //Create a lnSegment array for the current point
        struct LnSegment lines[n];
        
        // Get all possible line segments with point i in them
        for (int j = i + 1; j < n; j++) {
            point2D p2 = p[j];
            
            if (i != j) {
                //Create struct lnSegment with two points (i and j) and current slope
                struct LnSegment line;
                line.slope = calc_slope(p1.x, p1.y, p2.x, p2.y);
                line.x1 = p1.x;
                line.y1 = p1.y;
                line.x2 = p2.x;
                line.y2 = p2.y;
                // Add lnSegment to array
                lines[j - 1] = line;
            }
        }
        
        // Sort array by slopes
        qsort(lines, n, sizeof(struct LnSegment), cmpfunc);
        
        // Iterate over array and see if elements that have the same slope share a point
        for (int i = 0; i < n - 1; i++) {
            struct LnSegment ln1 = lines[i];
            struct LnSegment ln2 = lines[i + 1];
            if (ln1.slope == ln2.slope && share_point(ln1, ln2)) {
                ncol++;
//                printf("Points: %i, %i, %i\n", i, j, k);
            }
        }
    }
    
    printf("find_collinear_improved: total %d distinct collinear triplets (out of max %ld triplets)\n", ncol, (long int) ((long int)n * (long int)(n-1) * (long int)(n - 2)) / 6);
    fflush(stdout);
}






