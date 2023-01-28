#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defs.h"

/*
  Function: loadBooks
  Purpose:  creates a new BookType structure for each book in booksData.txt and adds each book to the given book collection
      out:  book collection
   return:  void
*/
void loadBooks(BookListType *books) {
    FILE *infile;
    int id = 1001;
    char str[MAX_STR];
    char title[MAX_STR];
    char author[MAX_STR];
    int year;
    BookStatusType status;

    infile = fopen("booksData.txt", "r");

    if (!infile) {
        printf("Error: could not open file\n");
        exit(1);
    }

    while (1) {
        fgets(title, MAX_STR, infile);
        title[strcspn(title,"\n")] = 0;
        fgets(author, MAX_STR, infile);
        author[strcspn(author,"\n")] = 0;
        fgets(str, MAX_STR, infile);
        sscanf(str, "%d", &year);
        fgets(str, MAX_STR, infile);
        sscanf(str, "%d", &status);

        if (feof(infile)){
            break;
        }

        BookType *book;
        initBook(id++, title, author, year, status, &book);
        addBook(books, book);
    }

    fclose(infile);

    char log[MAX_BUFF];
    formatBooks(books, log);
    printf("\nBOOKS:\n%s\n\n", log);
}


/*
  Function: initLibrary
  Purpose:  initializes the given library
   in-out:  the library and the name
 return:  void
*/

void initLibrary(LibraryType **library, char *n){
    *library = malloc(sizeof(LibraryType));
    strcpy((*library)->name, n);
    initList(&(*library)->books);
    loadBooks(&(*library)->books);
}

/*
  Function: checkOutBook
  Purpose:  checks out the given book out from the given library
   in-out:  the library and the book id
   return:  C_OK for in case of success C_NOK in case of error
*/

int checkOutBook(LibraryType *lib, int bookId){
    //declare booktype pointer
    BookType *book;
    //check if the book is in the collection, if not, return book not found
    if (findBook(&lib->books, bookId, &book) == C_OK){
        // book is currently checkin in, otherwise return bad status
        if (book->status == CHECKED_IN) {
            //set status to be checked out and return sucess
            book->status = CHECKED_OUT;
            return C_OK;
        }else{
            return C_BAD_STATUS;
        }
    }else{
        return C_BOOK_NOT_FOUND;
    }
}

/*
  Function: checkInBook
  Purpose:  checks in the given book id into the given library
   in-out:  the library and the book id
   return:  C_OK for in case of success C_NOK in case of error
*/
int checkInBook(LibraryType *lib, int bookId){
    //declare booktype pointer
    BookType *book;

    //check if the book is in the collection, if not, return book not found
    if (findBook(&lib->books, bookId, &book) == C_OK){
        // book is currently checkin out, otherwise return bad status
        if (book->status == CHECKED_OUT){
            //set status to be checked in and return sucess
            book->status = CHECKED_IN;
            return C_OK;
        }else{
            return C_BAD_STATUS;
        }
    }else{
        return C_BOOK_NOT_FOUND;
    }
}

/*
  Function: cleanupLibrary
  Purpose:  deallocates memory used for library
       in:  the library
   return:  void
*/

void cleanupLibrary(LibraryType *lib){
    cleanupList(&lib->books);
    free(lib);
}
