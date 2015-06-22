/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int result = b_search(value, values, 0, n-1);
    if(result == 1)
        return false;
    else 
        return true;
}

int b_search(int value, int arr[], int first, int last)
{
    int mid = first + (last - first) / 2; // find middle
    
    if(arr[mid] == value){ // Value is found
        return 0;
    }
    
    if(first >= last){ // Base case
        return 1;
    }
           
    if(arr[mid] > value){
        return b_search(value, arr, first, mid-1); // Go left
    } else {
        return b_search(value, arr, mid+1, last); // Go right
    }
    
    return 1;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int i ,j, swapcount = 0, compcount = 0;
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            compcount++;
            if(values[i]>values[j])
            {
                swap(&values[i], &values[j]);
                swapcount++;
            }
        }
    }
    return;
}

