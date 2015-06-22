/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);
int b_search(int value, int arr[], int first, int last);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);
void swap(int *xp, int *yp);
