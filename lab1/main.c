#include <stdio.h>

int isHeap_recursive(int arr[], int i, int n)
{
    //if i is outside of the array range, it means this part is a heap
    if (i >= n || n <= 0)
        return 1;

    //if there is a left child, compare with it
    if ((2*i + 1) < n)
        if (arr[i] > arr[2*i+1])
            return 0;

    //if there is a right, compare with it
    if ((2*i + 2) < n)
        if (arr[i] > arr[2*i+2])
            return 0;

    //recursively go the the left and right child and return the final result based on && operation .
    return (isHeap_recursive(arr, 2*i+1, n) && isHeap_recursive(arr, 2*i+2, n));
}

// Returns 1 if arr[i..n-1] represents a
// max-heap
int isHeap_iter(int arr[],  int n)
{
    // Start from root and go till the last internal
    // node
    for (int i=0; i<=(n-2)/2; i++)
    {
        // If left child is smaller, return false
        if (arr[i] > arr[2*i+1])
            return 0;


        if (isHeap_recursive(arr, 2*i+1, n) && isHeap_recursive(arr, 2*i+2, n)) //Finish on your own
            return 0;
    }
    return 1;
}

// Driver program
int main()
{
    //int arr[6] = {12, 13, 14, 15, 110, 115}; //it is heap
    int arr[6] = {12, 110, 14, 15, 13, 115}; // not min heap


    isHeap_recursive(arr, 0, 6)? printf("Recursive says Yes!\n"): printf("Recursive says No!\n");
    isHeap_iter(arr, 6)? printf("Iterative says Yes!\n"): printf("Iterative says No!\n");
    //same as the following
    /*if(isHeap(arr, 0, 6)
       printf("Yes")
    else
        printf("No");*/

    return 0;
}