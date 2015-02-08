#include "geom.h"
#include <float.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static const float EPSILON = 0.00001;

/* Quick sort functions */

/* Sort slopes in increasing order
 */
int cmpfunc(const void * a, const void * b) {
    /*Type cast*/
    lnSegment* x = (lnSegment*) a;
    lnSegment* y = (lnSegment*) b;
    
    if (x->slope < y->slope) {
        return -1;
    } else if (x->slope > y->slope) {
        return 1;
    } else {
        return 0;
    }
}

/* Tests for floating point equality
 */
int isEqualFloat(float a, float b) {
    if (fabsf(a - b) < EPSILON) {
        return 1;
    }
    return 0;
}

int isEqualPoint(point2D a, point2D b) {
    return (a.x == b.x) && (a.y == b.y);
}

/* Gets rid of the repeated points in the input array
 * Returns the new "size" of the array without duplicates
 */
int deleteDuplicates(point2D* array, int size) {
    int index = 0;
    point2D newArray[size];
    
    for (int i = 0; i < size - 1; i++) {
        point2D p = array[i];
        int hasDuplicate = 0;
        for (int j = i + 1; j < size; j++) {
            if (isEqualPoint(p, array[j])) {
                hasDuplicate = 1;
            }
        }
        if (!hasDuplicate) {
            newArray[index] = p;
            index++;
        }
    }
    
    int newSize = index + 1;
    
    // Copy array
    for (int n = 0; n < newSize; n++) {
        array[n] = newArray[n];
    }
    
    return newSize;
}

void debugDeleteDuplicates(point2D* array, int size) {
    printf("size: %i\n", size);
//    for (int i = 0; i < size; i++) {
//        point2D p = array[i];
//        printf("x: %d, y: %d\n", p.x, p.y);
//    }
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

/* Calculates the slope
 * Returns DBL_MAX if the slope is vertical
 */
double calc_slope(double x1, double y1, double x2, double y2) {
    double denominator = x1 - x2;
    if (!isEqualFloat(denominator, 0)) {
        return (y1 - y2) / denominator;
    }
    return DBL_MAX;
}

/* Returns the y-intercept
 */
double calc_y_intercept(double x, double y, double slope) {
    return y - (slope * x);
}

/* Checks if the third point is colinear
 */
int is_colinear(double x, double y, double slope, double y_intercept) {
    return isEqualFloat(y, slope * x + y_intercept);
}

void add_triplet(triplet* array, int index, point2D p_a, point2D p_b, point2D p_c) {
    triplet tri;
    tri.a = p_a;
    tri.b = p_b;
    tri.c = p_c;
    array[index] = tri;
}

/* **************************************** */
/* return all triplets of colinear points as an array using the
 straightforward algorithm that runs in cubic time
 */
void find_collinear_straightforward(point2D* p, int n, triplet* t) {
    assert(p);
    int ncol = 0; //nb distinct  collinear triplets
    
    for (int i = 0; i < n - 2; i++) {
        point2D p1 = p[i];
        
        for (int j = i + 1; j < n - 1; j++) {
            point2D p2 = p[j];
    
            double slope = calc_slope(p1.x, p1.y, p2.x, p2.y);
            double yIntercept = calc_y_intercept(p1.x, p1.y, slope);
            
            if (slope < DBL_MAX) {
                // If the slope is not vertical
                for (int k = j + 1; k < n; k++) {
                    point2D p3 = p[k];
                    //Check to see if third point is colinear with line segement of first two points
                    if (is_colinear(p3.x, p3.y, slope, yIntercept)) {
                        add_triplet(t, ncol, p1, p2, p3);
                        ncol++;
                    }
                }
            } else {
                // The two points are different and have a vertical slope
                for (int k = j + 1; k < n; k++) {
                    point2D p3 = p[k];
                    
                    // Check if the third point has a shared x coordinate
                    if (p3.x == p1.x) {
                        // Add the triplet
                        add_triplet(t, ncol, p1, p2, p3);
                        ncol++;
                    }
                }
            }
        }
    }
    
    printf("find_collinear_straightforward: total %d distinct collinear triplets (out of max %ld triplets)\n", ncol, (long int) ((long int)n*(long int)(n-1)*(long int)(n-2))/6);
    fflush(stdout);
}

/* **************************************** */
/* return all triplets of colinear points as an array using the
 improved algorithm that runs in O(n^2 lg n) time and O(n) memory
 */
void find_collinear_improved(point2D* p, int n, triplet* t) {
    assert(p);
    int ncol = 0; //nb distinct collinear triplets
    
    for (int i = 0; i < n - 1; i++) {
        point2D p1 = p[i];
        
        // Create a lnSegment array for the current point
        int size = n - i - 1;
        lnSegment lines[size];
        
        // Get all possible line segments with point i in them
        for (int j = i + 1; j < n; j++) {
            point2D p2 = p[j];
            
            //Create struct lnSegment with two points (i and j) and current slope
            lnSegment ln;
            ln.slope = calc_slope(p1.x, p1.y, p2.x, p2.y);
            ln.first = p1;
            ln.second = p2;
            // Add to array
            lines[j - i - 1] = ln;
        }
        
        // Sort array by slopes
        qsort(lines, size, sizeof(lnSegment), cmpfunc);

        // Count triplets
        for (int a = 0; a < size; a++) {
            lnSegment ln1 = lines[a];
            lnSegment ln2 = lines[a + 1];
            int b = a + 1;
            
            while (isEqualFloat(ln1.slope, ln2.slope)) {
                // Only 3 out of the 4 points are distinct
                point2D p1, p2, p3;
                p1 = ln1.first;
                p2 = ln1.second;
                if (isEqualPoint(ln2.first, p1) || isEqualPoint(ln2.first, p2)) {
                    p3 = ln2.second;
                } else {
                    p3 = ln2.first;
                }
                // Add the 3 points
                add_triplet(t, ncol, p1, p2, p3);
                
                // Go to next slope
                b++;
                ncol++;
                ln2 = lines[b];
            }
        }
    }
    
    printf("find_collinear_improved: total %d distinct collinear triplets (out of max %ld triplets)\n", ncol, (long int) ((long int)n * (long int)(n-1) * (long int)(n - 2)) / 6);
    fflush(stdout);
}