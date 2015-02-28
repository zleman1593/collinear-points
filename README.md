# collinear-points

Count the number of distinct collinear triplets in a set of n points in the plane.

Straightforward Algorithm:
1. For every point i, we check every j and k and see if ij have the same slope and y-intercetp as jk.
2. This takes O(n^3) time and constant space.

Improved Algorithm:
1. For every point, we calculate its slope with every other point, store these slopes in an array, and sort the array.
2. Then we check adjacent entries in the array - having the same slope implies colinearity.
3. We reuse the array for next point.
4. This takes O(n^2 * lg(n)) time and O(n) space.

Testing:
1. The constant MAX_NUM_TRIPLETS at the top is the maximum size of the array that stores triplets. 
2. If n is large, you will need to modify this number to avoid overflow (maximum number of triplets for n is n choose 3).
