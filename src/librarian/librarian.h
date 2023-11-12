#ifndef LIBRARIAN_H
#define LIBRARIAN_H

//create a LIBRARIAN stucture to represent a librarian information
struct LIBRARIAN{
    char name[30];
    char appDate[15];
    char address[100];
    char phone[15];
};

//a function that take input librarian information from user
struct LIBRARIAN inputLibrarianData(void);

//create a function that show librarian information in tabular form
//5 argument receives (header file names-2D aray, column length in array form, column number, librarian data file name, file openning mode)
void printLibrarianTable(char (*)[20], int[], int, char[], char[]);

//a function that add librarian record in database
void addLibrarian(void);

//a function that delete librarian record from database
void deleteLibrarian(void);

//a function that view librarian record from database
void viewLibrarian(void);

//create a function that edit librarian data
void editLibrarianInfo(void);

#endif