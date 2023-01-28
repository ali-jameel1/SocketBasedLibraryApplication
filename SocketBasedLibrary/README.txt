

COMP2401 Assignment #4

Ali Jameel 101185339

Nov 24 2021

Purpose: Write a program in C with multiple processes, this program will be a library manager. The program will allow users to check in and check out books, so long as they are available.

Source and Header files: 

						- README.txt

						- booksData.txt

						- defs.h

						- lib.c

						- client.c

						- connect.c

						- server.c

						- books.c



Compilation command: in the assignment4 folder, open a new terminal, that is, open a terminal IN THE SAME LOCATION AS THE ASSIGNMENT and enter "make"



Server instructions: 

		1. on the same terminal that you entered "make" now enter ./server& 

		2. You can enter "ps" to check if the server is running (this is NOT necessary)

		3. To test for memory leaks on this assignment enter "valgrind --leak-check=yes ./server" to test the server



Client instructions:

		1. Open a new terminal, also in the same location as the assignment and now enter ./client

		2. You will now see 4 options, enter 0 to quit, enter 1 to view the list of books, enter 2 to check out a book and enter 3 to check in a book. Entering 2 or 3 will then require you to enter the id of the book you wish to either check in or check out, so you may want to print the list first so you can see the options.

		3. To test for memory leaks on this assignment enter "valgrind --leak-check=yes ./client" to test the client
