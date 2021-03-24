#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"
/* COP 3502C Assignment 1
This program is written by: Juan Salas Paredes */

typedef struct MONSTER{
    char *name;
    char *element;
    int population;
}MONSTER;

typedef struct REGION{
    char *name;
    int numMonster;
    int totalPopulation;
    MONSTER **monster;
}REGION;

typedef struct ITINERARY{
    int nRegions;
    REGION **regions;
    int captures;
}ITINERARY;

typedef struct TRAINER{
    char *name;
    ITINERARY *itinerary;
}TRAINER;

MONSTER *createMonster(char *name, char *element, int population);
REGION *createRegions(char name[],char **arrayMonsters,int regionMonster,int *regionCount, MONSTER **monsters, int monsterCount);
TRAINER *createTrainers(char trainerName[],int numberRegion, int monsterCapture,char **regionName, REGION **regions, int regionCount);
MONSTER **readMonsters(FILE* fptr, int *monsterCount);
REGION **readRegions(FILE* fptr, int *regionCount,MONSTER **monsters,int monsterCount);
TRAINER **readTrainer(FILE* fptr, int *trainerCount, REGION **regions, int regionCount);
int outfile(TRAINER **trainers, FILE *fptr2, int trainerCount);
void freeMemory(MONSTER **monsters,REGION **regions,TRAINER **trainers, int monsterCount,int regionCount,int trainerCount);

int main(void) {
    atexit(report_mem_leak);
    FILE *fptr, *fptr2;
    fptr = fopen("in.txt", "r");// reading the file of that the user provided
    fptr2 = fopen("out.txt", "w");// creating the out file to output my results
    if (fptr == NULL){
        printf("Error!");
        exit(1);
    }// this if statement basically is just trying to see if the file is being read

    // making a double pointer array to store the information from the file
    MONSTER **monsters = NULL;
    REGION **regions = NULL;
    TRAINER **trainers = NULL;

    // initializing variable to store the amount of monsters, regions and trainers the file is outputting
    int monsterCount = 0 , regionCount = 0, trainerCount = 0;

    // making the double pointer equal a function to where the data will be taken in from the file
    monsters = readMonsters(fptr, &monsterCount);
    regions = readRegions(fptr, &regionCount, monsters,monsterCount);
    trainers = readTrainer(fptr,&trainerCount,regions, regionCount);

    //retrieve the information now stored from the file and pass it to a function where it will be output on a text file
    outfile(trainers, fptr2, trainerCount);

    // free all the memory used
    freeMemory(monsters,regions,trainers, monsterCount,regionCount,trainerCount);
    fclose(fptr);
    fclose(fptr2);
    return 0;
}

MONSTER** readMonsters(FILE* fptr, int *monsterCount){
    //initializing temporary variables
    char monsterN[51],monsterE[51];
    int population;

    // scan the first line of the file
    fscanf(fptr,"%d monsters",monsterCount);

    // allocate space for the list of monsters
    MONSTER **monsters = (MONSTER**) calloc(*monsterCount,sizeof(MONSTER*));

    // scan within a for loop as many times as the number of monsters the next lines
    for (int i=0; i< *monsterCount; i++){
        // retrieving the name of the monster, its element, and the population of each monster
        fscanf(fptr,"%s %s %d",monsterN,monsterE, &population);

        // taking in the information of monster and passing it to create monster function
        monsters[i] = createMonster(monsterN, monsterE, population);
    }
    return (monsters);
}

MONSTER* createMonster(char *name, char *element, int population){
    // allocating memory for the given monster
    MONSTER* thisMonsters = (MONSTER*) calloc(1,sizeof(MONSTER));

    // allocating memory for the name and element of each monster
    thisMonsters->name = (char*) calloc(strlen(name) + 1,sizeof(char));
    thisMonsters->element = (char*) calloc(strlen(element) + 1,sizeof(char));
    thisMonsters->population = population;
    strcpy(thisMonsters->name, name);
    strcpy(thisMonsters->element, element);
    return thisMonsters;
}

REGION** readRegions(FILE* fptr, int *regionCount,MONSTER **monsters,int monsterCount){
    // initialize temporary variables
    char **arrayMonsters;
    int regionMonster;
    char name[51];

    // search in the file for the number of regions that exist
    fscanf(fptr,"%d regions",regionCount);

    REGION **regions = (REGION **) calloc(*regionCount,sizeof(REGION*));

    for (int i=0; i< *regionCount; i++){
        fscanf(fptr,"%s",name);
        fscanf(fptr,"%d monsters",&regionMonster);
        arrayMonsters = (char **)calloc(regionMonster,sizeof(char*));
        for (int j=0; j < regionMonster;j++){
            arrayMonsters[j] = (char *)calloc(51, sizeof(char ));
            fscanf(fptr,"%s", arrayMonsters[j]);
        }
        regions[i] = createRegions(name,arrayMonsters,regionMonster,regionCount, monsters, monsterCount);
        for (int k = 0; k < regionMonster; ++k) {
            free(arrayMonsters[k]);
        }
        free(arrayMonsters);
    }

    return(regions);
}

REGION* createRegions(char name[],char **arrayMonsters,int regionMonster,int *regionCount, MONSTER **monsters, int monsterCount){
    // allocate memory for cR
    REGION *createRegions = (REGION*) calloc(1, sizeof(REGION));

    // allocate memory for the size of monsters
    createRegions->monster = (MONSTER**) calloc(regionMonster, sizeof(monsters));

    createRegions->name = (char*) calloc(strlen(name) + 1, sizeof(char));
    // make char name equal to the allocated memory of its region
    strcpy(createRegions->name,name);
    createRegions->numMonster = regionMonster;

    for (int i =0;i < regionMonster ;i++){
        for (int j = 0; j < monsterCount ;j++){
            if(strcmp(monsters[j]->name,arrayMonsters[i]) == 0){
                createRegions->monster[i] = monsters[j];
                createRegions->totalPopulation += monsters[j]->population;
            }
        }
    }
    return (createRegions);
}

TRAINER** readTrainer(FILE* fptr, int *trainerCount, REGION **regions, int regionCount){
    // initialize temporary variables
    char **regionName, trainerName[51];
    int monsterCapture = 0, numberRegion = 0;
    // scan the file for the number of trainers and the word trainers
    fscanf(fptr,"%d Trainers",trainerCount);
    TRAINER **trainers =(TRAINER**) calloc(*trainerCount, sizeof(TRAINER*));
    for (int i=0; i< *trainerCount; i++){
        // scan the file for the trainer names, monsters captured, and its region count
        fscanf(fptr,"%s",trainerName);
        fscanf(fptr,"%d captures", &monsterCapture);
        fscanf(fptr,"%d regions",&numberRegion);
        regionName = (char**) calloc(numberRegion,sizeof(char*));
        for (int j = 0; j < numberRegion; j++) {
            // allocate and scan for the region names
            regionName[j] = (char*) calloc(51,sizeof(char));
            fscanf(fptr,"%s",regionName[j]);
        }
        // pass all the information to a new function
        trainers[i] = createTrainers(trainerName,numberRegion, monsterCapture,regionName, regions, regionCount);
        for (int k = 0; k < numberRegion; ++k) {
            free(regionName[k]);
        }
        free(regionName);
    }
    return (trainers);
}

TRAINER *createTrainers(char trainerName[],int numberRegion, int monsterCapture,char **regionName, REGION **regions, int regionCount){
    // allocate space for the trainers
    TRAINER  *createTrainers = (TRAINER*)calloc(1,sizeof(TRAINER));
    //allocate space for the visits(itinerary)
    createTrainers->itinerary = (ITINERARY*)calloc(1,sizeof(ITINERARY));
    // allocate space for the name of the trainer
    createTrainers->name = (char*) calloc(strlen(trainerName) + 1, sizeof(char));
    // allocate space for the region names and its number of regions
    createTrainers->itinerary->regions = (REGION**)calloc(numberRegion, sizeof(REGION*));
    strcpy(createTrainers->name,trainerName);
    createTrainers->itinerary->captures = monsterCapture;
    createTrainers->itinerary->nRegions = numberRegion;
    for (int i = 0; i < createTrainers->itinerary->nRegions; i++) {
        for (int j = 0; j < regionCount; j++) {
            if(strcmp(regions[j]->name,regionName[i]) == 0){
                createTrainers->itinerary->regions[i] = regions[j];
            }
        }
    }
    return (createTrainers);
}

int outfile(TRAINER **trainers, FILE *fptr2, int trainerCount){
    // pass all the information from trainer and save it to the outfile fptr
    for (int i = 0; i < trainerCount; i++){
        fprintf(fptr2, "%s\n",trainers[i]->name);
        for (int j = 0; j < trainers[i]->itinerary->nRegions; j++) {
            fprintf(fptr2, "%s\n",trainers[i]->itinerary->regions[j]->name);
            for (int k = 0; k < trainers[i]->itinerary->regions[j]->numMonster; k++) {
                int count  = round((1.0*trainers[i]->itinerary->regions[j]->monster[k]->population/trainers[i]->itinerary->regions[j]->totalPopulation) * trainers[i]->itinerary->captures);
                if (count > 0) {
                    fprintf(fptr2, "%d %s", count, trainers[i]->itinerary->regions[j]->monster[k]->name);
                    fprintf(fptr2, "\n");
                }
            }
        }
        if(i < trainerCount - 1) {
            fprintf(fptr2, "\n");
        }
    }
    return 0;
}

void freeMemory(MONSTER **monsters,REGION **regions,TRAINER **trainers, int monsterCount,int regionCount,int trainerCount){
    for (int i = 0; i < monsterCount; ++i){
        free(monsters[i]->name);
        free(monsters[i]->element);
        free(monsters[i]);
    }
    for (int j = 0; j < regionCount ; ++j) {
        free(regions[j]->name);
        free(regions[j]->monster);
        free(regions[j]);
    }
    for (int k = 0; k < trainerCount; ++k) {
        free(trainers[k]->name);
        free(trainers[k]->itinerary->regions);
        free(trainers[k]->itinerary);
        free(trainers[k]);
    }
    free(monsters);
    free(regions);
    free(trainers);// this will work
}
