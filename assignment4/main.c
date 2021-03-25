/*
 *             COP 3502C Assignment 4
This program is written by: Juan Salas Paredes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define MAXLEN 50


typedef struct itemNode
{
    char name[MAXLEN];
    int count;
    struct itemNode *left, *right;
}itemNode;

typedef struct treeNameNode
{
    char treeName[MAXLEN];
    struct treeNameNode *left, *right;
    itemNode *theTree;
}treeNameNode;


treeNameNode * createTreeNameNode(char *tree_name);
treeNameNode* buildNameTree(FILE * infile, int treeCount);
void traverse_in_traverse(treeNameNode *root);
itemNode* createItemNode(char* item_name, int pop_count);
void buildItemTree(FILE *infile, treeNameNode* myTree, int num_items);
void Queries(FILE *infile, treeNameNode* myTree, int num_queries);
treeNameNode * searchNameNode(treeNameNode* root, char treeName[MAXLEN]);
itemNode * searchItemNode(itemNode* root, char itemName[MAXLEN]);
treeNameNode* insert(treeNameNode* root, treeNameNode* species);
itemNode* insertItemNodeToTree(itemNode* newItem, itemNode* item);
int leftHeight(itemNode* palmTree);
int rightHeight(itemNode* palmTree);
int previous_item(itemNode* palmTree, char itemName[MAXLEN]);
int itemCount(itemNode* palmTree);
void inorder(treeNameNode *curr_ptr);
void inorderItemNode(itemNode *curr_ptr);
itemNode* parentNode(itemNode *root, itemNode *nodePtr);
treeNameNode* parentTreeName(treeNameNode *root, treeNameNode *node);
int onlyLeftChild(itemNode *node);
int onlyRightChild(itemNode *node);
itemNode* minimum(itemNode *root);
treeNameNode* minimumTreeName(treeNameNode *root);
int leaf_Function(itemNode *node);
itemNode* deleteItemNode(itemNode* palmTree, char itemName[MAXLEN]);
void undo_Tree(itemNode* palmTree, char *itemName, int reducedValue);
void deleteItemTree(itemNode *palmTree);
treeNameNode* delete_name(treeNameNode* myTree, char treeName[MAXLEN]);
void free_Node(treeNameNode *myTree);




void traverse_in_traverse(treeNameNode *root)
{
    if(root == NULL)
        return;

    traverse_in_traverse(root->left);
    printf("\n===%s===\n", root->treeName);
    inorderItemNode(root->theTree);
    traverse_in_traverse(root->right);

}


int main(void)
{
    atexit(report_mem_leak);
    FILE *infile;
    FILE *outfile;
    infile = fopen("in.txt", "r");
    outfile = freopen("out.txt", "w", stdout);
    int num_of_trees,num_items,num_queries;
    treeNameNode* myTree;
    treeNameNode *temp;
    fscanf(infile, "%d %d %d", &num_of_trees, &num_items, &num_queries);
    myTree = buildNameTree(infile, num_of_trees);
    buildItemTree(infile, myTree, num_items);
    inorder(myTree);
    traverse_in_traverse(myTree);
    printf("\n");
    Queries(infile, myTree, num_queries);
    free_Node(myTree);

    return 0;

}

treeNameNode * createTreeNameNode(char *tree_name) //creates a treename node
{
    treeNameNode * newTree = (struct treeNameNode*)malloc(sizeof(struct treeNameNode));

    strcpy(newTree->treeName, tree_name);
    newTree->left = NULL;
    newTree->right = NULL;
    newTree->theTree = NULL;
    //copy the newtree pointer to tree name and return it
    return newTree;
}

treeNameNode* buildNameTree(FILE * infile, int treeCount) // build a tree for a name node that was created
{
    treeNameNode * palmTree = NULL; // make a tree name pointer and set it to NULL
    char thatsmyName[31];
    for(int i = 0; i < treeCount; i++)
    {
        fscanf(infile, "%s", thatsmyName);
        treeNameNode* tmp = createTreeNameNode(thatsmyName);  // call the create Tree function and pass a tree node pointer
        palmTree = insert(palmTree, tmp);
    }
    return palmTree;
}

itemNode* createItemNode(char* item_name, int pop_count) //Creates an item node and returns it
{
    itemNode* newItem = (struct itemNode*)malloc(sizeof(struct itemNode)); // Make a new item pointer copy it and return it
    strcpy(newItem->name, item_name);
    newItem->count = pop_count;
    newItem->left = NULL;
    newItem->right = NULL;

    return newItem;
}

void buildItemTree(FILE *infile, treeNameNode* myTree, int num_items) // Build tree allocate space and call the insert item node function
{
    char treeName[MAXLEN], itemName[MAXLEN];
    treeNameNode * thisNode;
    itemNode* tmp;
    int population;
    for(int i = 0; i < num_items; i++)
    {
        fscanf(infile, "%s %s %d", treeName, itemName, &population); // scan for the tree and item name and the population
        thisNode = searchNameNode(myTree, treeName);
        tmp = createItemNode(itemName, population);
        thisNode->theTree = insertItemNodeToTree(thisNode->theTree, tmp);
    }
}

void Queries(FILE *infile, treeNameNode* myTree, int num_queries) // Queries function handles all the queries like search etc....
{
    for(int i = 0; i < num_queries; i++)
    {
        char querylen[MAXLEN];
        char treeName[MAXLEN];
        char itemName[MAXLEN];
        fscanf(infile, "%s%s ", querylen, treeName);
        treeNameNode * palmTree;
        itemNode* tmp_item;

        if(strcmp(querylen, "search") == 0)
        {
            fscanf(infile, "%s ", itemName);
            palmTree = searchNameNode(myTree, treeName);
            if(palmTree)
            {
                tmp_item = searchItemNode(palmTree->theTree, itemName);
                if(tmp_item)
                    printf("%d %s found in %s\n", tmp_item->count, tmp_item->name, palmTree->treeName);
                else
                    printf("%s not found in %s\n", itemName, palmTree->treeName);
            }
            else
                printf("%s does not exist\n", treeName);
        }

        else if(strcmp(querylen, "item_before") == 0)
        {
            fscanf(infile, "%s ", itemName);
            palmTree = searchNameNode(myTree, treeName);
            int count = previous_item(palmTree->theTree, itemName);
            printf("item before %s: %d\n", itemName, count);
        }

        else if(strcmp(querylen, "height_balance") == 0)
        {

            palmTree = searchNameNode(myTree, treeName);
            char balanced[50] = "balanced";
            int difference = 0;

            int left = leftHeight(palmTree->theTree->left);

            int right = rightHeight(palmTree->theTree->right);
            if(abs(right - left) > 1)
            {
                strcpy(balanced, "not balanced");
                difference = abs(right - left);
            }
            printf("%s: left height %d, right height %d, difference %d, %s\n", palmTree->treeName, left, right, difference, balanced);

        }
        else if(strcmp(querylen, "count") == 0)
        {
            int num_items;
            palmTree = searchNameNode(myTree, treeName);
            num_items = itemCount(palmTree->theTree);
            printf("%s count %d\n", palmTree->treeName, num_items);
        }
        else if(strcmp(querylen, "delete") == 0)
        {
            fscanf(infile, "%s ", itemName);
            palmTree = searchNameNode(myTree, treeName);
            palmTree->theTree = deleteItemNode(palmTree->theTree, itemName);
            printf("%s deleted from %s\n", itemName, treeName);
        }
        else if(strcmp(querylen, "delete_name") == 0)
        {
            palmTree = searchNameNode(myTree, treeName);
            deleteItemTree(palmTree->theTree);
            myTree = delete_name(myTree, treeName);
            printf("%s deleted\n", treeName);
        }


        else if(strcmp(querylen, "reduce") == 0)
        {
            int itemCount;
            fscanf(infile, "%s %d", itemName, &itemCount);
            palmTree = searchNameNode(myTree, treeName);
            palmTree->theTree = searchItemNode(palmTree->theTree, itemName);
            undo_Tree(palmTree->theTree, itemName, itemCount);
            printf("%s reduced\n", itemName);
        }
    }
}

treeNameNode * searchNameNode(treeNameNode* root, char treeName[MAXLEN]) // search through the tree and return the root and treeName
{
    if(root == NULL)
        return root;

    else
    {    if(strcmp(root->treeName, treeName) == 0)
            return root;

        if(strcmp(root->treeName, treeName) > 0)
        {
            return searchNameNode(root->left, treeName);
        }
        else
        {
            return searchNameNode(root->right, treeName);
        }
    }
}

itemNode * searchItemNode(itemNode* root, char itemName[MAXLEN]) // Searches the items and returns a root or a recursive call to the item node function
{
    if(root == NULL)
        return 0;

    else
    {    if(strcmp(root->name, itemName) == 0)
            return root;

        if(strcmp(root->name, itemName) > 0)
        {
            return searchItemNode(root->left, itemName);
        }
        else
        {
            return searchItemNode(root->right, itemName);
        }
    }
}

treeNameNode* insert(treeNameNode* root, treeNameNode* species) //Inserts the nodes into the tree
{
    if(root==NULL)
        return species;
    else
    {
        if(strcmp(species->treeName, root->treeName) > 0)
        {
            if(root->right != NULL)
                root->right = insert(root->right, species);
            else
                root->right = species;
        }
        else
        {
            if(root->left != NULL)
                root->left  = insert(root->left, species);
            else
                root->left = species;
        }
        return root;
    }
}

itemNode* insertItemNodeToTree(itemNode* newItem, itemNode* item) // insert node to the item tree and return the item
{
    if(newItem==NULL)
        return item;
    else
    {
        if(strcmp(item->name, newItem->name) > 0)
        {
            if(newItem->right != NULL)
                newItem->right = insertItemNodeToTree(newItem->right, item);
            else
                newItem->right = item;
        }
        else
        {
            if(newItem->left != NULL)
                newItem->left  = insertItemNodeToTree(newItem->left, item);
            else
                newItem->left = item;
        }

        return newItem;
    }

}

int leftHeight(itemNode* palmTree)
{
    // function that measures the left height
    int left_height;
    int right_height;
    if(palmTree == NULL)
    {
        return -1;
    }
    left_height = leftHeight(palmTree->left);
    right_height = rightHeight(palmTree->right);

    if(left_height > right_height)
    {
        return left_height + 1;
    }

    return right_height + 1;
}

int rightHeight(itemNode* palmTree)
{
    // function that measures the right height
    int left_height;
    int right_height;
    if(palmTree == NULL)
    {
        return -1;
    }
    left_height = leftHeight(palmTree->left);
    right_height = rightHeight(palmTree->right);

    if(left_height > right_height)
    {
        return left_height + 1;
    }

    return right_height + 1;
}


int previous_item(itemNode* palmTree, char itemName[MAXLEN])
{
    // previous item function returns the value of the item
    int return_value = 0;
    if(palmTree == NULL)
    {
        return 0;
    }

    if(strcmp(palmTree->name, itemName) < 0)
    {
        return 1 + previous_item(palmTree->left, itemName) + previous_item(palmTree->right, itemName);
    }
    else
        return previous_item(palmTree->left, itemName) + previous_item(palmTree->right, itemName);

    return return_value;
}

int itemCount(itemNode* palmTree)
{
    // function that counts the amount of items in the tree
    int left_return_value;
    int right_return_value;
    if(palmTree == NULL)
        return 0;

    return palmTree->count + itemCount(palmTree->left) + itemCount(palmTree->right);
}

void inorder(treeNameNode *curr_ptr)
{
    //function that put the tree inorder
    if(curr_ptr != NULL)
    {
        inorder(curr_ptr->left);
        printf("%s ", curr_ptr->treeName);
        inorder(curr_ptr->right);
    }
}

void inorderItemNode(itemNode *curr_ptr)
{
    // puts the item node in the right order
    if(curr_ptr != NULL)
    {
        inorderItemNode(curr_ptr->left);
        printf("%s ", curr_ptr->name);
        inorderItemNode(curr_ptr->right);
    }
}

itemNode* parentNode(itemNode *root, itemNode *nodePtr)
{

    // function that makes the parent node and sets in the tree
    if (root == NULL || root == nodePtr)
        return NULL;


    if (root->left == nodePtr || root->right == nodePtr)
        return root;


    if (strcmp(nodePtr->name, root->name) < 0)
        return parentNode(root->left, nodePtr);


    else if (strcmp(nodePtr->name, root->name) > 0)
        return parentNode(root->right, nodePtr);

    return NULL;

}

treeNameNode* parentTreeName(treeNameNode *root, treeNameNode *node)
{
    // function that sets the name of the parent nodes in the tree
    if (root == NULL || root == node)
        return NULL;


    if (root->left == node || root->right == node)
        return root;


    if (strcmp(node->treeName, root->treeName) < 0)
        return parentTreeName(root->left, node);


    else if (strcmp(node->treeName, root->treeName) > 0)
        return parentTreeName(root->right, node);

    return NULL;

}

int onlyLeftChild(itemNode *node)
{
    //Boolean function that returns 1 if there is only a left child in the tree
    return (node->left != NULL && node->right == NULL);
}


int onlyRightChild(itemNode *node)
{
    //Boolean function that returns 1 if there is only a right child in the tree
    return (node->left == NULL && node->right != NULL);
}

itemNode* minimum(itemNode *root)
{
    // function gets the smallest node in the tree

    if (root->left == NULL)
        return root;


    else
        return minimum(root->left);
}

treeNameNode* minimumTreeName(treeNameNode *root)
{
// gets the smallest tree name in the BST

    if (root->left == NULL)
        return root;


    else
        return minimumTreeName(root->left);
}

int leaf_Function(itemNode *node)
{
//Boolean function that returns 1 if there is a Leaf
    return (node->left == NULL && node->right == NULL);
}

itemNode* deleteItemNode(itemNode* palmTree, char itemName[MAXLEN])
{
//Deletes a item node from the tree and returns the root
    itemNode *del_node;
    itemNode *tmp_del_node;
    itemNode *save_node;
    itemNode *parent;
    char save_value[MAXLEN];
    int save_int;

    del_node = searchItemNode(palmTree, itemName);

    parent = parentNode(palmTree, del_node);


    if (leaf_Function(del_node))
    {

        // Delete the node in the tree.
        if (parent == NULL)
        {
            free(palmTree); // free the memory for that node.
            return NULL;
        }

        // Deletes the node if it's a left child.
        if(strcmp(itemName, parent->name) < 0)
        {
            free(parent->left); // Free the memory for the node.
            parent->left = NULL;
        }

            // Deletes the node if it's a right child.
        else
        {
            free(parent->right); // Free the memory for the node.
            parent->right = NULL;
        }

        return palmTree; // Return the root of the new tree.
    }

    // Take care of the case where the node to be deleted only has a left
    // child.
    if(onlyLeftChild(del_node))
    {

        // Deleting the root node of the tree.
        if (parent == NULL)
        {
            save_node = del_node->left;
            free(del_node); // Free the node to delete.
            return save_node; // Return the new root node of the resulting tree.
        }

        // Deletes the node if it's a left child.
        if (strcmp(itemName, parent->name) < 0)
        {
            save_node = parent->left; // Save the node to delete.
            parent->left = parent->left->left; // Readjust the parent pointer.
            free(save_node); // Free the memory for the deleted node.
        }

            // Deletes the node if it's a right child.
        else
        {
            save_node = parent->right; // Save the node to delete.
            parent->right = parent->right->left; // Readjust the parent pointer.
            free(save_node); // Free the memory for the deleted node.
        }

        return palmTree; // Return the root of the tree after the deletion.
    }

    // Takes care of the case where the deleted node only has a right child.
    if (onlyRightChild(del_node))
    {

        // Node to delete is the root node.
        if (parent == NULL)
        {
            save_node = del_node->right;
            free(del_node);
            return save_node;
        }

        // Delete's the node if it is a left child.
        if (strcmp(itemName, parent->name) < 0)
        {
            save_node = parent->left;
            parent->left = parent->left->right;
            free(save_node);
        }

            // Delete's the node if it is a right child.
        else
        {
            save_node = parent->right;
            parent->right = parent->right->right;
            free(save_node);
        }
        return palmTree;
    }
//if your code reaches hear it means delnode has two children
    // Find the new physical node to delete.
    tmp_del_node = minimum(del_node->right);
    strcpy(save_value, tmp_del_node->name);
    save_int = tmp_del_node->count;

    deleteItemNode(palmTree, save_value);  // Now, delete the proper value.

    // Restore the data to the original node to be deleted.
    strcpy(del_node->name, save_value);
    del_node->count = save_int;

    return palmTree;
}

void undo_Tree(itemNode* palmTree, char *itemName, int reducedValue)
{
    // reduce function that will help with the reduction the nodes in the tree
    itemNode* tmp;
    palmTree->count = palmTree->count - reducedValue;
    if(palmTree->count <= 0)
        deleteItemNode(palmTree, itemName);
}

void deleteItemTree(itemNode *palmTree)
{
    // delete function which deletes the item trees
    itemNode* nodeToDelete = palmTree;
    if(nodeToDelete == NULL)
        return;
    deleteItemTree(palmTree->left);
    deleteItemTree(palmTree->right);
    free(palmTree);
    palmTree = NULL;
}

// look for the parent and then free the child and delete that tree
treeNameNode* delete_name(treeNameNode* myTree, char treeName[MAXLEN])
{
    // deletes the names of the node in the BST
    treeNameNode *del_node;
    treeNameNode *tmp_del_node;
    treeNameNode *save_node;
    treeNameNode *parent;
    char save_value[MAXLEN];
    int save_int;

    del_node = searchNameNode(myTree, treeName); // Get a pointer to the node to delete.

    parent = parentTreeName(myTree, del_node); // Get the parent of this node.

    // the node here is a leaf which needs to be deleted.
    if (del_node->left == NULL && del_node->right == NULL)
    {

        // Deleting the only node in the tree.
        if (parent == NULL)
        {
            free(myTree); // free the memory for the node.
            return NULL;
        }

        // Deletes the node if it's a left child.
        if(strcmp(treeName, parent->treeName) < 0)
        {
            free(parent->left); // Free the memory for the node.
            parent->left = NULL;
        }

            // Deletes the node if it's a right child.
        else
        {
            free(parent->right); // Free the memory for the node.
            parent->right = NULL;
        }

        return myTree; // Return the root of the new tree.
    }

    // Deletes the node if has only a left child.
    if (del_node->left != NULL && del_node->right == NULL)
    {

        // Deleting the root node of the tree.
        if (parent == NULL)
        {
            save_node = del_node->left;
            free(del_node); // Free the node to delete.
            return save_node; // Return the new root node of the resulting tree.
        }

        // Deletes the node if it's a left child.
        if (strcmp(treeName, parent->treeName) < 0)
        {
            save_node = parent->left; // Save the node to delete.
            parent->left = parent->left->left; // Readjust the parent pointer.
            free(save_node); // Free the memory for the deleted node.
        }

            // Deletes the node if it's a right child.
        else
        {
            save_node = parent->right; // Save the node to delete.
            parent->right = parent->right->left; // Readjust the parent pointer.
            free(save_node); // Free the memory for the deleted node.
        }

        return myTree; // Return the root of the tree after the deletion.
    }

    // Helps with the deleting of a node with only a right child.
    if (del_node->left == NULL && del_node->right != NULL)
    {
        // Node to delete is the root node.
        if (parent == NULL)
        {
            save_node = del_node->right;
            printf("%s %s\n", del_node->treeName, save_node->treeName);
            free(del_node);
            return save_node;
        }

        // Delete's the node if it is a left child.
        if (strcmp(treeName, parent->treeName) < 0)
        {
            save_node = parent->left;
            parent->left = parent->left->right;
            free(save_node);
        }

            // Delete's the node if it is a right child.
        else
        {
            save_node = parent->right;
            parent->right = parent->right->right;
            free(save_node);
        }
        return myTree;
    }
// Delete node here has 2 nodes
    // Find the node to delete.
    tmp_del_node = minimumTreeName(del_node->right);
    strcpy(save_value, tmp_del_node->treeName);

    delete_name(myTree, save_value);  //Delete the value in that node

    // Append the data for the value of the node orginally
    strcpy(del_node->treeName, save_value);

    return myTree;
}

void free_Node(treeNameNode *myTree) // Free function that takes care of the remaining item nodes
{

    treeNameNode* free_this_tree = myTree;
    if(free_this_tree == NULL)
        return;
    free_Node(free_this_tree->left);
    free_Node(free_this_tree->right);
    deleteItemTree(myTree->theTree);
    free(free_this_tree);
    free_this_tree = NULL;
}
