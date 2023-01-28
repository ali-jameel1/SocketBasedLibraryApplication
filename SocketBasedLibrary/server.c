#include "defs.h"

int listenSocket;

int main() {
  //declare variable
  int socketClient;
  LibraryType *library;

  //initialize new library
  initLibrary(&library, "Ali's Library");
  
  setupServerSocket(&listenSocket);
  signal(SIGUSR1, handleSig1);

  printf("Waiting for a connection\n");
  acceptConnection(listenSocket, &socketClient);
  printf("You've been connected\n");
  serveOneClient(socketClient, library);
  
  return 0;
}


/*
  Function: serveOneClient
  Purpose:  deals with all the requests that the client makes
       in:  client socket and library
   return:  void
*/
void serveOneClient(int socketClient, LibraryType *lib) {
  char request[MAX_BUFF];
  char response[MAX_BUFF];
  
  int id;
  int statusChecker;
  int contain;

  while(1) {

    printf("waiting for message\n");

    rcvData(socketClient, request);
    printf("received message\n");

    //if the request is to close the program, print a thanks for using message
    if (request[0] - '0' == REQ_CLOSE) {
      printf("Thanks for using our program\n Bye! \n");
      //close the server, close the library, then exit the program
      close(socketClient);
      closeAll(lib);
      exit(0);

    //if the request is to checkin a book, check what checkInBook returns
    }else if (request[0] - '0' == REQ_CHECK_IN){
      sscanf(request, "%d %d", &contain, &id);
      statusChecker = checkInBook(lib, id);

      //if checkin books returns C_BAD_STATUS, tell user the book has not been checked out
      if (statusChecker == C_BAD_STATUS){
        sprintf(response, "Error: That book id is already checked in");

      //if checkin books returns C_BOOK_NOT_FOUND, tell user the book is not found
      }else if (statusChecker == C_BOOK_NOT_FOUND){
        sprintf(response, "Error: There is no book with that ID");

      //if checkin books returns anything else, the book was succesfully checked in
      }else{
        sprintf(response, "Book checked in");
      }
      sendData(socketClient, response);

    //if the request is to check-out a book, check what checkOutBook returns
    }else if (request[0] - '0' == REQ_CHECK_OUT){
      sscanf(request, "%d %d", &contain, &id);
      statusChecker = checkOutBook(lib, id);

      //if checkin books returns C_BAD_STATUS, tell user the book has already been checked out
      if (statusChecker == C_BAD_STATUS){
        sprintf(response, "Error: That book id is not currently checked in");

      //if checkin books returns C_BOOK_NOT_FOUND, tell user the book is not found
      }else if (statusChecker == C_BOOK_NOT_FOUND){
        sprintf(response, "Error: There is no book with that ID");

      //if check-out books returns anything else, the book was succesfully checked out
      }else{
        sprintf(response, "Book checked out");
      }
      sendData(socketClient, response);

    // If the request is to view the books call format books and sendData
    }else if (request[0] - '0' == REQ_RET_BOOKS){
      formatBooks(&lib->books, response);
      sendData(socketClient, response);

    }
  }
  
}

/*
  Function: closeAll
  Purpose:  closes the listening socket and calls cleanupLibrary
       in:  library
   return:  void
*/
void closeAll(LibraryType *lib) {
  close(listenSocket);
  cleanupLibrary(lib);
}

/*
  Function: handleSig1
  Purpose:  closes the listenin socket and exits the program
       in:  listening socket
   return:  void
*/
void handleSig1(int i) {
  close(listenSocket);
  exit(0);
}
