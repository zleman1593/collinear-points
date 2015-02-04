#include "geom.h"
#include <float.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static const float EPSILON = 0.00001;

/* Line segment representation */
struct LnSegment {
    double slope;
    double x1;
    double y1;
    double x2;
    double y2;
    int index1;
    int index2;
};

/* Quick sort functions */

int cmpfunc (const void * a, const void * b) {
    /*Type cast*/
    struct LnSegment * x = (struct LnSegment*) a;
    struct LnSegment * y = (struct LnSegment*) b;
    
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

/* Computes n!
 */
int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
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

/* **************************************** */
/* return all triplets of colinear points as an array using the
 straightforward algorithm that runs in cubic time
 */
void find_collinear_straightforward(point2D* p, int n) {
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
                        ncol++;
//                        printf("Points: %i, %i, %i\n", i, j, k);
                    }
                }
            } else {
                // Vertical slope
                for (int k = j + 1; k < n; k++) {
                    // Check if the third point has a shared x coordinate
                    if (isEqualFloat(p[k].x, p1.x)) {
                        ncol++;
//                        printf("Vertical line segment. Points: %i, %i, %i \n", i, j, k);
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
void find_collinear_improved(point2D* p, int n) {
    assert(p);
    int ncol = 0; //nb distinct collinear triplets
    
    for (int i = 0; i < n - 1; i++) {
        point2D p1 = p[i];
        
        // Create a lnSegment array for the current point
        int size = n - i - 1;
        struct LnSegment lines[size];
    
        // Get all possible line segments with point i in them
        for (int j = i + 1; j < n; j++) {
            point2D p2 = p[j];
            
            //Create struct lnSegment with two points (i and j) and current slope
            struct LnSegment ln;
            ln.slope = calc_slope(p1.x, p1.y, p2.x, p2.y);
            ln.x1 = p1.x;
            ln.y1 = p1.y;
            ln.x2 = p2.x;
            ln.y2 = p2.y;
            ln.index1 = i;
            ln.index2 = j;
            // Add lnSegment to array
            lines[j - i - 1] = ln;
        }
        
        // Sort array by slopes
        qsort(lines, size, sizeof(struct LnSegment), cmpfunc);
        
        // DEBUG
//        printf("SORTED ARRAY OF SLOPES\n");
//        for (int index = 0; index < size; index++) {
//            struct LnSegment ln_t = lines[index];
//            printf("Points # %i, %i, has slope %f\n", ln_t.index1, ln_t.index2, ln_t.slope);
//        }
//        printf("\n");
        
        // Iterate over array and see if elements have the same slope
        // If so they are on the same line
//        struct LnSegment ln1;
//        struct LnSegment ln2;
//        int b = 0;
//        for (int a = 0; a < size - 1; a++) {
//            b = a + 1;
//            ln1 = lines[a];
//            ln2 = lines[b];
//            
//            while (ln1.slope == ln2.slope) {
//                /*Expected output is four points. Two should have the same number. Three unique points for a colinear triplet*/
//                printf("Points #: %i, %i, %i, %i\n", ln1.index1, ln1.index2, ln2.index1,ln2.index2);
//                printf("Points coordinates: (%f,%f);(%f,%f); (%f,%f); (%f,%f);\n", ln1.x1, ln1.y1, ln1.x2,ln1.y2,ln2.x1,ln2.y1, ln2.x2, ln2.y2);
//                
//                b++;
//                ncol++;
//                if (b >= size) {
//                    break;
//                }
//                ln2 = lines[b];
//            }
//        }
        
        struct LnSegment ln1;
        struct LnSegment ln2;
        for (int a = 0; a < size - 1; a++) {
            // Number of slopes with the same value
            int count = 1;
            ln1 = lines[a];
            ln2 = lines[a + 1];
            while (isEqualFloat(ln1.slope, ln2.slope)) {
                count++;
                if (a + count >= size) {
                    break;
                }
                // Check next line
                ln2 = lines[a + count];
            }
            if (count > 1) {
                /* n choose k where n is the number of consecutive same slopes and k is the number of points to choose (3)
                 * n = count + 1, because for m number of line segments on the same line, there are m + 1 endpoints
                 * Formula: n! / k!(n - k)!
                 */
                int numOfTriplets = factorial(count + 1) / (factorial(3) * factorial(count + 1 - 3));
                ncol = ncol + numOfTriplets;
            }
            // Move index a along
            a = a + count - 1;
        }
    }
    
    printf("find_collinear_improved: total %d distinct collinear triplets (out of max %ld triplets)\n", ncol, (long int) ((long int)n * (long int)(n-1) * (long int)(n - 2)) / 6);
    fflush(stdout);
}