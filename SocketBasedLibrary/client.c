#include "defs.h"


int main()
{
  int  choice = -1;
  int clientSocket; 

  char req[MAX_BUFF];
  char res[MAX_BUFF];
  int id;
  char str[MAX_STR];

  setupClientSocket(&clientSocket);

  while (1) {

   clientMenu(&choice);

   switch(choice) {
     // if user enters 0, end the program
      case 0:
        sprintf(req, "%d", REQ_CLOSE);
        sendData(clientSocket, req);
        close(clientSocket);
        return 0;
        break;
      // if user enters 1, print the books
      case 1:
        sprintf(req, "%d", REQ_RET_BOOKS);
        sendData(clientSocket, req);
        rcvData(clientSocket, res);
        printf("%s\n", res);
        break;
      // if user enters 2, ask for id of the book to be checked out
      case 2:
        printf("Please enter the id of the book you wish to check out : ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", &id);
        sprintf(req, "%d %d", REQ_CHECK_OUT, id);

        sendData(clientSocket, req);

        rcvData(clientSocket, res);

        printf("%s\n", res);
        break;
      // if user enters 2, ask for id of the book to be checked in
      case 3:
        printf("Please enter the id of the book you wish to check in: ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", &id);
        sprintf(req, "%d %d", REQ_CHECK_IN, id);

        sendData(clientSocket, req);

        rcvData(clientSocket, res);

        printf("%s\n", res);
        break;
      // default should be set to an invalid option, so if user enters something unaccounted for, an error is printed
      default:
        printf("ERROR:  invalid option\n");
    }
  }

  return 0;
}

void clientMenu(int* choice)
{
  int c = -1;
  int numOptions = 3;
  char str[MAX_STR];

  printf("\nMAIN MENU\n");
  printf("  (1) Print books\n");
  printf("  (2) Check out a book\n");
  printf("  (3) Check in a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
  sscanf(str, "%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &c);
  }

  *choice = c;
}

