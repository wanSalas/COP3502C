#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXVAL 1000000

void randArray(int array[] ,int size,int max);
void arrayCopy(int from[],int to[],int size);
long timediff(clock_t start, clock_t finished);
void bubbleSort(int sortedArray[],int size);
void insertionSort(int sortedArray[],int size);
void selectionSort(int arr[],int size);
void quickSort(int *sortedArray, int low, int high);
int partition(int *vals, int low, int high);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void swap(int *a, int *b);


int main(void) {
    int size[] = {1000,10000,20000,40000,50000,100000};
    //arrays
    int *originalArray;
    int *sortedArray;
    //variables
    long elapsed;
    clock_t start, end;

    for(int i = 0; i < 6; i++){
        //allocate for the six sizes of the nubers of the array
        originalArray = (int*)malloc(sizeof(int)*size[i]);
        sortedArray = (int*)malloc(sizeof(int)*size[i]);

        randArray(originalArray,size[i],MAXVAL);

        arrayCopy(originalArray,sortedArray,size[i]);

        //start with the time and array sort
        start = clock();
        bubbleSort(sortedArray,size[i]);
        end = clock();
        elapsed = timediff(start,end);
        printf("Sorting %d value took %ld milliseconds for bubble sort.\n",size[i], elapsed);

        arrayCopy(originalArray,sortedArray,size[i]);

        start = clock();
        insertionSort(sortedArray,size[i]);
        end = clock();
        elapsed = timediff(start,end);
        printf("Sorting %d value took %ld milliseconds for Insertion sort.\n",size[i], elapsed);

        start = clock();
        mergeSort(sortedArray, 0 ,size[i]);
        end = clock();
        elapsed = timediff(start,end);
        printf("Sorting %d value took %ld milliseconds for Merge sort.\n",size[i], elapsed);

        start = clock();
        selectionSort(sortedArray,size[i]);
        end = clock();
        elapsed = timediff(start,end);
        printf("Sorting %d value took %ld milliseconds for selection sort.\n",size[i], elapsed);

        start = clock();
        quickSort(sortedArray, 0 ,size[i]);
        end = clock();
        elapsed = timediff(start,end);
        printf("Sorting %d value took %ld milliseconds for quick sort.\n",size[i], elapsed);

        free(sortedArray);
        free(originalArray);
    }
    return 0;
}
void randArray(int array[] ,int size,int max){
    for(int i = 0; i < size; i++)
        array[i] =rand()%max + 1;
}
void arrayCopy(int from[],int to[],int size){
    for(int j = 0; j < size; j++){
        to[j] = from[j];
    }
}

long timediff(clock_t start, clock_t finished){
    long elapsed;
    elapsed = ((double)finished - start) / CLOCKS_PER_SEC *1000;
    return elapsed;
}
void bubbleSort(int sortedArray[],int size){
    for(int i = size - 2; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            if(sortedArray[j] > sortedArray[j+1])
                swap(&sortedArray[j], &sortedArray[j+1]);
        }
    }
}

void insertionSort(int sortedArray[],int size){
    int item;
    for(int i = 0; i < size; i++){
        item = sortedArray[i];
        for(int j = i-1;j >= 0; j--){
            if(sortedArray[j] > item)
                sortedArray[j+1] = sortedArray[j];
            else
                break;
            sortedArray[j+1] =item;
        }
    }
}

void mergeSort(int arr[], int l, int r){
    if (l < r){
        int m = (l+r)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 =  r - m;

/* create temp arrays */
    int *L = (int*) malloc(n1*sizeof(int));
    int *R = (int*) malloc(n2*sizeof(int));

/* Copy data to temp arrays L[] and R[] */
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    int i = 0;  // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = l; // Initial index of merged subarray
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    /* Copy the remaining elements of L[], if there       are any */
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there       are any */
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void swap(int *a, int *b){
    int tempArray = *a;
    *a = *b;
    *b = tempArray;
}

void selectionSort(int arr[],int size){
    int i, j, min_idx, temp;

    for (i = 0; i < size-1; i++){
        min_idx = i;
        for (j = i+1; j < size; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[i], &arr[min_idx]);
    }
}

void quickSort(int *sortedArray, int low, int high){
    if (low < high) {
        int split = partition(sortedArray,low,high);
        quickSort(sortedArray,low,split-1);
        quickSort(sortedArray,split+1,high);    }
}

int partition(int *vals, int low, int high){
    int i = low + rand()%(high-low+1);
    swap(&vals[low], &vals[i]);
    int lowpos = low;
    low++;
    while(low<=high){
        while(low<=high && vals[low]<=vals[lowpos]) low++;
        while(high>=low && vals[high] > vals[lowpos]) high--;
        if (low<high)
            swap(&vals[low], &vals[high]);
    }
    swap(&vals[lowpos], &vals[high]);
    return high;
}