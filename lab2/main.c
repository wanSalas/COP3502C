#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;


node*  insert_front(node *root, int item)
{
    node *temp;
    //create a new node and fill-up the node
    temp= (node *) malloc(sizeof(node));
    temp->data=item;
    temp->next=NULL;
    if(root==NULL) //if there is no node in the linked list
        root=temp;
    else //there is an existing linked list, so put existing root after temp
    {
        temp->next = root; //put the existing root after temp
        root = temp; //make the temp as the root!
    }
    return root;

}

node* reverse(node* head)
{
    if(head==NULL || head->next ==NULL)
    {
        return head;
    }

    node* main_list = head->next;

    node* reversed_list = head;
    head->next = NULL;

    while(main_list != NULL)
    {
        node* temp= main_list;
        main_list= main_list->next;

        temp->next = reversed_list;
        reversed_list = temp;
    }



    return reversed_list;
}

void inserttoPlace(node* head,int val,int place)
{
    if(head == NULL|| place < 1)
    {
        printf("\nList is empty or place is not valid");
        return;
    }

    node* tmp = (node*)malloc(sizeof(node));
    tmp->data =  val;

    int i = 1;
    while (head->next != NULL && i<place-1)
    {
        head = head->next;
        i++;
    }

    tmp->next = head->next;
    i++;
    head->next = tmp;

}
void display(node* t)
{
    printf("\nPrinting your link list.......");

    while(t!=NULL)
    {
        printf("%d ",t->data);
        t=t->next;
    }

}


int main()
{
    node *root=NULL; //very important line. Otherwise all function will fail
    node *t;
    int choice,ele,v, del;
    while(1) {
        printf("\nMenu: 1. insert at front, 2. reverse list, 3. Insert to place 0. exit: ");
        scanf("%d", &choice);
        if (choice == 0) {
            printf("\nGOOD BYE>>>>\n");
            break;
        }
        if (choice == 1) {
            printf("\nEnter data(an integer): ");
            scanf("%d", &ele);
            root = insert_front(root, ele);

            display(root);

        }
        if (choice == 2) {
            root = reverse(root);
            printf("List reversed");
            display(root);

        }
        if (choice == 3) {
            int place;
            printf("\nEnter data (an integer) and place (>1) separated by a space");
            scanf("%d %d", &ele, &place);
            inserttoPlace(root, ele, place);
            display(root);

        }

    }
    return 0;
}