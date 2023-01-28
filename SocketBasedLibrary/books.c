#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defs.h"

/*
  Function: initList
  Purpose:  initializes the book list
       in:  BookListType
   return:  void
*/

void initList(BookListType *list){
    //initialize the head and tail to be null
    list->head = NULL;
    list->tail = NULL;
}

/*
  Function: initBook
  Purpose:  initializes a given book
       in:  the id, title, author, year, status
   return:  void
*/

void initBook(int i, char *t, char *a, int y, BookStatusType st, BookType **book){
    //allocate space
    *book = malloc(sizeof(BookType));
    //set the book values to the given parameters
    (*book)->id = i;
    (*book)->year = y;
    (*book)->status = st;

    strcpy((*book)->title, t);
    strcpy((*book)->author, a);
}

/*
  Function: addBook
  Purpose:  inserts the new book into the book collection, directly in its correct 
            position, in ascending order by title
       in:  the book
   in-out:  the book collection
   return:  void
*/

void addBook(BookListType *list, BookType *b){
    //create node pointer for the current, previous and new node
    NodeType *current;
    NodeType *previous;
    NodeType *nodeNew;

    //allocate space for the new node
    nodeNew = malloc(sizeof(NodeType));

    //set the new nodes data to be b and its next to null
    nodeNew->data = b;
    nodeNew->next = NULL;

    //set the current node to be the list head and previous to null
    current = list->head;
    previous = NULL;

    //while the current node is not null
    while (current != NULL){
        //if the current node's title is greater then the added books title break the loop
        //so we have that value of the current node
        if (strcmp(current->data->title, b->title) > 0){
            break;
        }
        //change previous to current
        previous = current;
        //change current to currents next, and reapeat (provided curren still does not equal null)
        current = current->next;
    }

    

    //if the node is not the first node in the list, set its previous to ve the new node
    if (previous != NULL){
        previous->next = nodeNew;
    }else{
        //if it is the head of the list, set the new head to be the new node
        list->head = nodeNew;
    }

    //if the current node is not null, set the new nodes next to be the current node
    if (current != NULL){
        nodeNew->next = current;
    }else{
        //if it is null, set it to be the tail
        list->tail = nodeNew;
    }
}

/*
  Function: findBook
  Purpose:  go through the collection of books and compare each books id to given id, 
            in an attempt to check if the given book id is present in the collection
       in:  the idand book collection and a booktype ponter that will be set to be equal
            the found nodes data
   return:  C_OK in case of success, C_NOK in case of unsuccess 
*/

int findBook(BookListType *list, int id, BookType **b){
    //create node pointer for the current node
    NodeType *current;
    //set the current node to the list head
    current = list->head;

    //while the current null is not null
    while (current != NULL){
        //if the current nodes data id is equal to the given id, set the pointer b to the data and return C_OK
        if (current->data->id == id){
            (*b) = current->data;
            return C_OK;
        }
        //change current to currents next, and reapeat (provided curren still does not equal null)
        current = current->next;
    }
    //after traversing the whole linked list, return C_NOK
    //Only will run if the book with the given id is not in the collection
    return C_NOK;
}



/*
  Function: formatBook
  Purpose:  print a string which contains all of the books information, in a formatted fashion
       in:  the book
   return:  void
*/
void formatBook(BookType *b, char *outStr) {
    //create a new string
    char stat[MAX_STR];
    //depending on what the status is, set the string to be the following:
    getStatus(b->status, stat);
    //print out the books characteristics in a formatted way
    sprintf(outStr, "%d : %-38s : %-18s : %d : %-s", b->id, b->title, b->author, b->year, stat);
}

/*
  Function: getStatus
  Purpose:  set the string to be a message, depending on what the status is
       in:  BookStatusType and a string
   return:  void

*/

void getStatus(BookStatusType status, char *string){
    if (status == CHECKED_IN){
        strcpy(string, "Checked in");
    }else if (status == CHECKED_OUT){
        strcpy(string, "Checked out");
    }else if (status == LOST){
        strcpy(string, "Lost");
    }else if (status == UNDER_REPAIR){
        strcpy(string, "Under repair");
    }
}

/*
  Function: formatBooks
  Purpose:  for each book in the BookListType, use format book to print each book out
       in:  book collection
   return:  void
*/

void formatBooks(BookListType *list, char *outStr){

    //declare variables
    char formattedBook[MAX_BUFF];
    //create a NodeType pointer
    NodeType *current;

    //set the current to be the list head
    current = list->head;

    //while the current node is not equal to null
    while (current != NULL){
        formatBook(current->data, formattedBook);
        //add the current string to outStr (if its not the head add a new line before doing so)
        if (current != list->head){
            strcat(outStr, "\n");
            strcat(outStr, formattedBook);
        }else{

            strcpy(outStr, formattedBook);

        }
        //set current to be currents next
        current = current->next;
    }

    formatBook(list->head->data, formattedBook);
    strcat(outStr, "\n-- HEAD: ");
    strcat(outStr, formattedBook);
    formatBook(list->tail->data, formattedBook);
    strcat(outStr, "\n-- TAIL: ");
    strcat(outStr, formattedBook);

}
/*
  Function: cleanupList
  Purpose:  deallocation of memory
       in:  the book collection
   return:  void
*/

void cleanupList(BookListType *list){
    //create node pointer for the current and next node
    NodeType *current;
    NodeType *next;

    // set the current node to be the list head and its next to be null
    current = list->head;
    next = NULL;

    //iterate through the linked list and free each nodes data, then free the node
    while (current != NULL){
        free(current->data);
        next = current->next;
        free(current);
        current = next;
    }
}

