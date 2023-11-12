//include header files
#include<stdio.h>
#include<conio.h>
#include<windows.h>

#include "library.h"
#include "book.h"
#include "student.h"
#include "librarian.h"
#include "checkinout.h"

//function to show detaits(like book number, registered student number, librarian number, check-in number) in dashboards
void board(){
    struct BOOK book;
    struct STUDENT student;
    struct LIBRARIAN librarian;
    struct CHECKIN checkIn;

    char bookNo[50];
    char studentNo[50];
    char librarianNo[50];
    char checkInNo[50];

    int bookNum = 0;
    int studentNum = 0;
    int librarianNum = 0;
    int checkInNum = 0;

    FILE *bookfile, *studentfile, *librarianfile, *checkinfile;

    bookfile = fopen("bookData.dat", "rb");
    studentfile = fopen("studentData.dat", "rb");
    librarianfile = fopen("librarianData.dat", "rb");
    checkinfile = fopen("checkInData.dat", "rb");
    
    while(fread(&book, sizeof(book), 1, bookfile) > 0){
        bookNum++;
    }
    while(fread(&student, sizeof(student), 1, studentfile) > 0){
        studentNum++;
    }
    while(fread(&librarian, sizeof(librarian), 1, librarianfile) > 0){
        librarianNum++;
    }
    while(fread(&checkIn, sizeof(checkIn), 1, checkinfile) > 0){
        checkInNum++;
    }

    fclose(bookfile);
    fclose(studentfile);
    fclose(checkinfile);
    fclose(librarianfile);
    
    // Use sprintf to concatenate the integer with the string
    sprintf(bookNo, "Total number of Books : %d", bookNum);
    sprintf(studentNo, "Number of registered students : %d", studentNum);
    sprintf(checkInNo, "Number of checked-in books : %d", checkInNum);
    sprintf(librarianNo, "Number of Librarian : %d", librarianNum);
    
    gotoxy(3, 9);
    printf("+--------------------------------------------------+");
    gotoxy(3, 10);
    printf("|%-50s|", bookNo);
    gotoxy(3, 11);
    printf("+--------------------------------------------------+");
    gotoxy(3, 12);
    printf("|%-50s|", studentNo);
    gotoxy(3, 13);
    printf("+--------------------------------------------------+");
    gotoxy(3, 14);
    printf("|%-50s|", checkInNo);
    gotoxy(3, 15);
    printf("+--------------------------------------------------+");
    gotoxy(3, 16);
    printf("|%-50s|", librarianNo);
    gotoxy(3, 17);
    printf("+--------------------------------------------------+");
}

//function to search book from file and view data
void searchBook() {
    struct BOOK book;
    char temp[50];
    int found = 0; // To track if the book was found

    gotoxy(70, 18);
    printf("Enter Book Name or ID : ");
    fflush(stdin);
    gets(temp);

    FILE *fp = fopen("bookData.dat", "rb");
    int i = 22;

    gotoxy(0, i);
    printf("+---------------+----------------------------------------+-------------------------+----------+-------------+");
    gotoxy(0, i + 1);
    printf("|      ID       |                Title                   |         Author          |  Price   | Publication |");
    gotoxy(0, i + 2);
    printf("+---------------+----------------------------------------+-------------------------+----------+-------------+");
    i += 3;

    while (fread(&book, sizeof(book), 1, fp) > 0) {
        if (strcmp(book.id, temp) == 0 || strcmp(book.title, temp) == 0) {
            gotoxy(0, i);
            printf("|%-15s|%-40s|%-25s|%-10s|%-13s|", book.id, book.title, book.author, book.price, book.publicationYear);
            gotoxy(0, i + 1);
            printf("+---------------+----------------------------------------+-------------------------+----------+-------------+\nEnter to continue...");
            i += 2;
            found = 1; // Book found
        }
    }

    if (!found) {
        gotoxy(70, 19);
        printf("Not Found...Enter to continue...");
    }

    fclose(fp);
    getch();
}

//function to search student from file and view data
void searchStudent(){
    struct STUDENT student;
    char temp[50];
    int found = 0; // To track if the book was found

    gotoxy(70, 18);
    printf("Enter Student Name or Roll : ");
    fflush(stdin);
    gets(temp);

    FILE *fp = fopen("studentData.dat", "rb");
    int i = 22;

    gotoxy(0, i);
    printf("+-------------------------+---------------+---------------+-------------+--------------------+---------------+");
    gotoxy(0, i + 1);
    printf("|          NAME           |     ROLL      |     CLASS     |   STREAM    |      SUBJECT       |     PHONE     |");
    gotoxy(0, i + 2);
    printf("+-------------------------+---------------+---------------+-------------+--------------------+---------------+");
    i += 3;

    while (fread(&student, sizeof(student), 1, fp) > 0) {
        if (strcmp(student.student_name, temp) == 0 || strcmp(student.roll_no, temp) == 0) {
            gotoxy(0, i);
            printf("|%-25s|%-15s|%-15s|%-13s|%-20s|%-15s|", student.student_name, student.roll_no, student.student_class, student.stream, student.subject, student.phone);
            gotoxy(0, i + 1);
            printf("+-------------------------+---------------+---------------+-------------+--------------------+---------------+\nEnter to continue...");
            i += 2;
            found = 1; // Book found
        }
    }

    if (!found) {
        gotoxy(70, 19);
        printf("Not Found...Enter to continue...");
    }

    fclose(fp);
    getch();
}