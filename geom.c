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

  assert(p); 
  int ncol=0; //nb distinct  collinear triplets

  //........

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

