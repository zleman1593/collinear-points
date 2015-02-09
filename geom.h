#ifndef __geom_h
#define __geom_h


typedef struct _point2d {
    int x,y;
} point2D;

typedef struct _lnSegment {
    point2D first, second;
    double slope;
 } lnSegment;

typedef struct _triplet {
    point2D a, b, c;
} triplet;



/* returns the signed area of triangle abc. The area is positive if c
   is to the left of ab, and negative if c is to the right of ab
 */
int signed_area2D(point2D a, point2D b, point2D c);

/* return 1 if p,q,r collinear, and 0 otherwise */
int collinear(point2D p, point2D q, point2D r);

/* return 1 if c is  strictly left of ab; 0 otherwise */
int left (point2D a, point2D b, point2D c); 


/* Deletes the duplicate points in the array*/
int deleteDuplicates(point2D* array, int size);

/* calculates the slope returns DBL_MAX if the slope is vertical */
double calc_slope(double x1, double y1, double x2, double y2);

/* calculates the y-intercept */
double calc_y_intercept(double x, double y, double slope);

/* Check if two floating or double points are within range of EPSILON*/
int isEqualFloat(float a, float b);


/* return all triplets of colinear points as an array using the
   straightforward algorithm that runs in cubic time 
*/
int find_collinear_straightforward(point2D* p, int n, triplet* t);

/* return all triplets of colinear points as an array using the
   an improved algorithm 
*/
int find_collinear_improved(point2D* p, int n, triplet* t);

#endif


