
/*COP 3502C Assignment 2
This program is written by: Juan Salas Paredes  */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

typedef struct soldier
{
    int sequence;
    struct soldier *prev;
    struct soldier *next;

}soldier;

typedef struct queue
{
    struct soldier *front;
    struct soldier *back;
    int numberOfSquadrian;
    int numberOfSoldiers;
    int k;
    int th;
    char squadrianName[51];
}army;

soldier* createSoldier(int soldier_order){

    soldier *curr_soldier = malloc(sizeof(soldier)); //Allocate for soldier node
    curr_soldier->sequence = soldier_order;
    curr_soldier->next = curr_soldier->prev = NULL;

    return curr_soldier;

}

int empty(army *qPtr){
    if(qPtr->front==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int peek(army *qPtr){
    if(empty(qPtr))  //if the list is empty return -1
    {
        return -1;
    }
    else  //return the front element of the army
        return qPtr->front->sequence;
}

void display(army* qPtr, FILE *outfile){
    if(empty(qPtr))
        return;

    soldier *front = qPtr->front;
    soldier *curr = front;
    fprintf(outfile, "%d %s %d", qPtr->numberOfSquadrian, qPtr->squadrianName, front->sequence);
    printf("%d %s %d", qPtr->numberOfSquadrian, qPtr->squadrianName, front->sequence);
    front=front->next;

    while( curr != front)
    {
        fprintf( outfile," %d",front->sequence);
        printf(" %d",front->sequence);
        front=front->next;
    }
    fprintf(outfile,"\n");
    printf("\n");
}


soldier* dequeue(army* qPtr){
    soldier *tmp;


    if(empty(qPtr))
    {
        return NULL;
    }

    tmp = qPtr->front;


    qPtr->front = qPtr->front->next;



    qPtr->numberOfSoldiers--;

    if(qPtr->numberOfSoldiers == 0)
    {
        qPtr->front = NULL;
        qPtr->back = NULL;
    }


    //free(tmp);
    return tmp;


}



void enqueue(army *q, int sequence){

    soldier *temp = createSoldier(sequence);

    if (!q->front)
    {

        q->front = temp;
        q->front->next = q->front->prev = q->front;

        return;
    }

    temp->next = q->front;
    temp->prev = q->front->prev;

    temp->prev->next = temp;

    q->front->prev = temp;
    q->back = temp;
}

void createReverseCircle(army *q){

    for (int i = q->numberOfSoldiers; i > 0; i--)
    {
        enqueue(q, i);
    }
}

void rearrangeCircle(army *q){

    if (empty(q))
        return;

    soldier *current = q->front;
    soldier *temp;

    do
    {

        temp = current->prev;

        current->prev = current->next;
        current->next = temp;

        current = current->next;

    } while (current != q->front);

    q->front = q->front->next;
}

soldier *death(army *qPtr, FILE *outfile){
    int soldier_skipped;
    int survivors;
    int soldier_num;
    int count;


    if(empty(qPtr) || qPtr->numberOfSoldiers <= 0 || qPtr->k <= 0)
    {
        return NULL;
    }

    fprintf(outfile, "\nLine# %d %s\n", qPtr->numberOfSquadrian, qPtr->squadrianName);
    printf("\nLine# %d %s\n", qPtr->numberOfSquadrian, qPtr->squadrianName);

    soldier *deadHomies = qPtr->front;// bored made a funny temp name

    count = qPtr->numberOfSoldiers;



    while(count > qPtr->th )
    {
        count--;

        for(int j=0;j<qPtr->k-1;j++)
        {
            deadHomies = deadHomies->next;
        }


        soldier *euphoria = deadHomies; // euphoria temp 2

        soldier *euphoria2; //euphoria temp 3



        if(euphoria->next == NULL)
        {
            qPtr->front = NULL;
            fprintf(outfile, "Soldier# %d executed\n", euphoria->sequence);
            printf("Soldier# %d executed\n", euphoria->sequence);
            free(euphoria);

            break;
        }

        else if(euphoria->next == euphoria->prev)  //check to see if the next is the last in the army free that node
        {
            qPtr->front = deadHomies->next;
            euphoria2 = euphoria->next;
            euphoria2->next = NULL;
            fprintf(outfile, "Soldier# %d executed", euphoria->sequence);
            printf("Soldier# %d executed", euphoria->sequence);
            free(euphoria);
            deadHomies = euphoria2;

            break;
        }

        else if(euphoria == qPtr->front)         // check to see if the next node is the front of the army
        {
            qPtr->front = deadHomies->next;
            qPtr->back->next = deadHomies->next;

        }

        else if(euphoria == qPtr->back)       // check to see if the next node is the back of the army
        {
            qPtr->back = deadHomies->prev;
            qPtr->front->prev = qPtr->back;

        }

        euphoria->prev->next = euphoria->next;
        euphoria->next->prev = euphoria->prev;

        fprintf(outfile,"Soldier# %d executed\n",deadHomies->sequence);
        printf("Soldier# %d executed\n",deadHomies->sequence);

        free(euphoria);
        deadHomies = euphoria->next;

        qPtr->numberOfSoldiers--;

    }

    return deadHomies;

}

void beginningPhase2(army **newQueue, int groupCount, FILE *outfile)  //beginningPhase2 or the phase 2 execution function will compare all the front of the queues using the seek function and eliminate all except 1
{
    int HighestSoldierInTheRoom;
    int survivors = 0;
    int q;
    int temp = 0;
    int count = 0;
    soldier *tempNode;
    army *deadpeople;
    army *last;

    for(q=0;q<10;q++)
    {

        if(!empty(newQueue[q]))
        {
            survivors += newQueue[q]->numberOfSoldiers;
        }

    }
    survivors = survivors - 1;

    while(survivors != 1)                    // while loop will run until there is 1 survivor left
    {
        int headsoldier =0;
        for(q=0;q<10;q++)
        {

            if(!empty(newQueue[q]))                          // for loop runs and highest soldier gets updated
            {
                if(headsoldier < peek(newQueue[q]))
                {
                    headsoldier = peek(newQueue[q]);
                    tempNode = newQueue[q]->front;
                    deadpeople = newQueue[q];
                }

            }

        }
        fprintf(outfile,"Executed Soldier %d from line %d\n",headsoldier ,deadpeople->numberOfSquadrian);
        printf("Executed Soldier %d from line %d\n",headsoldier ,deadpeople->numberOfSquadrian);


        dequeue(deadpeople);
        survivors--;

    }

}


void  finalSentence(army **newQueue)  //SentToTheGulag or free function will be called when it is time to free the queues and the last soldier node
{
    for(int j =0; j<10;j++)
    {
        if(newQueue[j])
        {
            army *Queue = newQueue[j];
            soldier *deadHomies = Queue->front;
            while(deadHomies->next != Queue->front)
            {
                free(deadHomies);
                deadHomies = deadHomies->next;
            }

            free(Queue);

        }
    }

    free(newQueue);

}

int main() {

    atexit(report_mem_leak);

    FILE *infile = fopen("in.txt", "r");
    FILE *outfile = fopen("out.txt", "w");

    int groupCount; // number of groups
    char ground_name[100]; // name of each ground
    int sequence_num; // number of soldiers in each group
    int ground_num; // number of the ground
    int k; // number of soldiers skipped in the execution phase
    int threshold; // number of soldiers necessary to proceed to the next phase of execution

    fscanf(infile, "%d", &groupCount);

    army** newQueue = malloc(10 * sizeof(army*));


    for(int i=0;i<10;i++)
    {
        newQueue[i] = malloc(sizeof(army));
        newQueue[i]->front =  NULL;
    }




    for (int i = 0; i < groupCount; i++) {

        fscanf(infile, "%d %s %d %d %d", &ground_num, ground_name, &sequence_num, &k, &threshold);



        army *qPtr = malloc(sizeof(army));
        strcpy(qPtr->squadrianName, ground_name);
        qPtr->numberOfSquadrian = ground_num;
        qPtr->numberOfSoldiers = sequence_num;
        qPtr->k = k;
        qPtr->th = threshold;


        newQueue[ground_num - 1] = qPtr;
    }


    fprintf(outfile,"Initial nonempty lists status\n");
    printf("Initial nonempty lists status\n");

    for (int i = 0; i < 10; i++) {

        if (newQueue[i])
        {

            army *exeground = newQueue[i];

            createReverseCircle(exeground);
            display(exeground,outfile);

        }


    }

    fprintf(outfile,"\n");
    printf("\n");


    fprintf(outfile,"After ordering nonempty lists status\n");
    printf("After ordering nonempty lists status\n");


    for (int j = 0; j < 10; j++)
    {

        if (newQueue[j])
        {

            army *exeground = newQueue[j];


            rearrangeCircle(exeground);
            display(exeground,outfile);

        }


    }


    fprintf(outfile,"\n");

    fprintf(outfile,"Phase1 execution");

    fprintf(outfile,"\n");

    printf("\n");
    printf("Phase1 execution");
    printf("\n");


    for (int k = 0; k < 10; k++) {

        if (newQueue[k])
        {

            army *exeground = newQueue[k];


            death(exeground, outfile);
            //display(exeground,outfile);


        }


    }

    fprintf(outfile,"\n");

    fprintf(outfile,"Phase2 execution\n");

    printf("\nPhase2 execution\n");

    beginningPhase2(newQueue, groupCount, outfile);

    //finalSentence(newQueue);

    return 0;
}