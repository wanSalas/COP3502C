#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "leak_detector_c.h"
int originX;
int originY;

typedef struct hunting{
    int currMonXCoord;
    int currMonYCoord; // make sure to get the absolute value of the coordinates
    int numberOfMonsters; //third number scanning in
    double distance; // need to calculate using pythag
}hunting;


int binarySearch(hunting* monsterArray, hunting searchArray, int l, int r);
hunting* calculateDistance(hunting *monsterArray, int numberOfMonsters, int hunterXCoord,int hunterYCoord);
int compareTo(hunting *ptr1, hunting *ptr2);
void insertionSort(hunting* monsterArray, int l, int r);
hunting* readData(FILE *inFile, hunting *ptrPt1, int numberOfMonsters, int pointToSearch, hunting* searchArray);
void merge(hunting *monsterArray, int l, int m, int r);
void mergeSort(hunting *monsterArray, int l, int r, int t);
void outPutResults(hunting *monsterArray,FILE *outFile, int numberOfMonsters);
void printingCoordinates(hunting *monsterArray,int numberOfMonsters);
hunting* spaceArray(FILE *inFile,int numberOfMonsters, int pointToSearch, hunting* searchArray,int hunterXCoord,int hunterYCoord);

int main(void) {
    atexit(report_mem_leak);

    int hunterXCoord, hunterYCoord;
    int numberOfMonsters;
    int pointToSearch;// fourth number
    int threshold; // determines wen to do merge sort of insertion sort
    int tempM;

    FILE *inFile, *outFile;
    inFile = fopen("in.txt", "r");
    outFile = fopen("out.txt", "w");
    fscanf(inFile, "%d %d %d %d %d", &hunterXCoord, &hunterYCoord, &numberOfMonsters, &pointToSearch, &threshold);
    //printf("%d %d %d %d %d\n",hunterXCoord, hunterYCoord, numberOfMonsters, pointToSearch, threshold);

    hunting *monsterArray = (hunting*)calloc(numberOfMonsters , sizeof(hunting));
    hunting *searchArray = (hunting*)calloc(pointToSearch , sizeof(hunting));


    readData(inFile,monsterArray,numberOfMonsters, pointToSearch, searchArray);
    spaceArray(inFile, numberOfMonsters, pointToSearch, searchArray, hunterXCoord,hunterYCoord);
    calculateDistance(monsterArray, numberOfMonsters, hunterXCoord,hunterYCoord);
    mergeSort(monsterArray, 0, numberOfMonsters - 1, threshold);
    printingCoordinates(monsterArray, numberOfMonsters);
    outPutResults(monsterArray, outFile, numberOfMonsters);

    for(int i=0; i < pointToSearch; i++){
        tempM = binarySearch(monsterArray, searchArray[i], 0, numberOfMonsters - 1);
        // I AM A GOD
        if(tempM != -1){
            printf("%d %d found at rank %d\n", searchArray[i].currMonXCoord,searchArray[i].currMonYCoord, tempM + 1);
            fprintf(outFile,"%d %d found at rank %d\n", searchArray[i].currMonXCoord,searchArray[i].currMonYCoord, i + 1);}
        else{
            printf("%d %d not found\n", searchArray[i].currMonXCoord,searchArray[i].currMonYCoord);
            fprintf(outFile,"%d %d not found\n", searchArray[i].currMonXCoord,searchArray[i].currMonYCoord);}
    }

    free(monsterArray);
    free(searchArray);
    fclose(inFile);
    fclose(outFile);
    return 0;
}
hunting* calculateDistance(hunting *monsterArray, int numberOfMonsters, int hunterXCoord, int hunterYCoord){
    for(int i = 0; i < monsterArray->numberOfMonsters; i++){
        monsterArray[i].distance = sqrt((double)pow(monsterArray[i].currMonXCoord - hunterXCoord,2)+pow(monsterArray[i].currMonYCoord - hunterYCoord, 2));
        /*printf("the distance of monster (%d %d) is: %.2lf \n", monsterArray[i].currMonXCoord,monsterArray[i].currMonYCoord, monsterArray[i].distance); // a bitch got the distance now for the hard compare function*/
    }

    return monsterArray;
}

hunting* readData(FILE *inFile, hunting *ptrPt1, int numberOfMonsters, int pointToSearch, hunting* searchArray){
    int i = 0;
    ptrPt1->numberOfMonsters = numberOfMonsters;
    while(i < numberOfMonsters){
        fscanf(inFile, "%d %d", &ptrPt1[i].currMonXCoord, &ptrPt1[i].currMonYCoord);
        //printf("THIS MONSTER IS #%d: %d %d\n", i + 1, ptrPt1[i].currMonXCoord, ptrPt1[i].currMonYCoord);
        i++;
    }

    for(int j = 0; j < pointToSearch; j++){
        fscanf(inFile, "%d %d", &searchArray[j].currMonXCoord, &searchArray[j].currMonYCoord);
        //printf("THIS IS THE S OF THE MONSTERS: %d %d\n", searchArray[j].currMonXCoord, searchArray[j].currMonYCoord);
    }

    return ptrPt1;
}

hunting* spaceArray(FILE *inFile,int numberOfMonsters, int pointToSearch, hunting* searchArray,int hunterXCoord,int hunterYCoord){
    for(int j = 0; j < pointToSearch; j++){
        fscanf(inFile, "%d %d", &searchArray[j].currMonXCoord, &searchArray[j].currMonYCoord);
        //printf("THIS IS THE S OF THE MONSTERS: %d %d\n", searchArray[j].currMonXCoord, searchArray[j].currMonYCoord);

        for(int i = 0; i < pointToSearch; i++){
            searchArray[i].distance = sqrt((double)pow(searchArray[i].currMonXCoord - hunterXCoord,2)+pow(searchArray[i].currMonYCoord - hunterYCoord, 2));
            /*printf("the distance of monster (%d %d) is: %.2lf \n", monsterArray[i].currMonXCoord,monsterArray[i].currMonYCoord, monsterArray[i].distance); // a bitch got the distance now for the hard compare function*/
        }
    }

    return searchArray;
}

int compareTo(hunting *ptr1, hunting *ptr2){
    if (fabs(ptr1->distance - ptr2->distance) <= 0.000001){
        if (ptr1->currMonXCoord < ptr2->currMonXCoord)
            return -1;
        if (ptr1->currMonXCoord > ptr2->currMonXCoord)
            return 1;
        if (ptr1->currMonYCoord < ptr2->currMonYCoord)
            return -1;
        if (ptr1->currMonYCoord > ptr2->currMonYCoord)
            return 1;
    }
    if (ptr1->distance < ptr2->distance){
        return  -1;
    }
    if (ptr1->distance > ptr2->distance){
        return  1;
    }
    return 0;
}

void mergeSort(hunting *monsterArray, int l, int r, int t){
    int m;

    if(r-l <= t){
        insertionSort(monsterArray, l, r);
    }
    else {
        // get the mid point
        m = (l+r)/2;

        mergeSort(monsterArray, l, m, t);
        mergeSort(monsterArray, m + 1, r, t);
        merge(monsterArray, l, m, r);
    }
}

void merge(hunting *monsterArray, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    hunting *L = (hunting*) malloc(n1*sizeof(hunting));
    hunting *R = (hunting*) malloc(n2*sizeof(hunting));

    for (i = 0; i < n1; i++){
        L[i] = monsterArray[l + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = monsterArray[m + 1+ j];
    }

    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2){
        if (compareTo(&L[i], &R[j]) < 0){
            monsterArray[k] = L[i];
            i++;
        }
        else{
            monsterArray[k] = R[j];
            j++;}
        k++;
    }
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1){
        monsterArray[k] = L[i];
        i++;
        k++;
    }
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2){
        monsterArray[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void insertionSort(hunting* monsterArray, int l, int r){
    int i, j; // Initialize variables
    hunting temp;

    for (i = l + 1; i <= r; i++){
        temp = monsterArray[i];
        for(j = i - 1; j >= l; j--){
            if(compareTo(&monsterArray[j], &temp) == 1)
                monsterArray[j + 1] = monsterArray[j];
            else
                break;
        }
        monsterArray[j+1] = temp;
    }
}
void printingCoordinates(hunting *monsterArray, int numberOfMonsters){
    for(int i =0; i < numberOfMonsters; i++){
        //need to change the outcome later
        //printf("Monster #%d: %d %d and has a distance of %.2lf \n", i+1, monsterArray[i].currMonXCoord, monsterArray[i].currMonYCoord, monsterArray[i].distance);
        printf("%d %d\n", monsterArray[i].currMonXCoord,monsterArray[i].currMonYCoord);
    }
}

int binarySearch(hunting* monsterArray, hunting searchArray, int l, int r){
    // first thing check for the left is less then the right bound this first case the upperbound if so then make a mid value
    int mid;
    if (l <= r){
        mid = (l + r)/2;
        //printf("left:%d right:%d mid:%d ValueOfMid: %.2lf\n", l,r,mid, monsterArray[mid].distance);
        if (compareTo(&monsterArray[mid], &searchArray) > 0){// == -1
            return binarySearch(monsterArray, searchArray, l, mid - 1);}

        else if (compareTo(&monsterArray[mid], &searchArray) < 0){ //==1
            return binarySearch(monsterArray, searchArray, mid + 1, r);}

        else if (compareTo(&monsterArray[mid], &searchArray) == 0){
            return mid;}
    }
    return -1;
}

void outPutResults(hunting *monsterArray,FILE *outFile, int numberOfMonsters){
    for(int i = 0; i < numberOfMonsters; i++){
        fprintf(outFile, "%d %d\n", monsterArray[i].currMonXCoord,monsterArray[i].currMonYCoord);
    }
}
