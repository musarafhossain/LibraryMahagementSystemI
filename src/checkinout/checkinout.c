//include header files
#include<stdio.h>
#include<conio.h>
#include<windows.h>

#include "library.h"
#include "book.h"
#include "student.h"
#include "checkinout.h"

//create a function to take input of checkIn data
struct CHECKIN inputCheckInData(){
    struct CHECKIN checkIn;
    gotoxy(30,10);
    printf("Enter Student Name :- ");
    fflush(stdin);
    gets(checkIn.studentName);
    gotoxy(30,12);
    printf("Enter Student Phone Number :- ");
    fflush(stdin);
    gets(checkIn.studentPhone);
    gotoxy(30,14);
    printf("Enter Student Class :- ");
    fflush(stdin);
    gets(checkIn.studentClass);
    gotoxy(30,16);
    printf("Enter Book Title :- ");
    fflush(stdin);
    gets(checkIn.title);
    gotoxy(30,18);
    printf("Enter Book ID :- ");
    fflush(stdin);
    gets(checkIn.bookId);
    gotoxy(30,20);
    printf("Enter Check-In Date (DD/MM/YYYY) :- ");
    fflush(stdin);
    gets(checkIn.checkInDate);
    gotoxy(30,21);
    printf("Enter Check-Out Date (DD/MM/YYYY) :- ");
    fflush(stdin);
    gets(checkIn.checkOutDate);
    return checkIn;
}

//create a function that current checkin book information in tabular form
//5 argument receives (header file names-2D aray, column length in array form, column number, check in data file name, file openning mode)
void printDataTable(char (*header)[20], int columnLength[], int columnNo, char fileName[], char fileMode[]){
    
    //print header's top border
    printf("+");
    for(int i=0; i<columnNo; i++){
        for(int j=0; j<columnLength[i];j++){
            printf("-");
        }
        printf("+");
    }
    printf("\n");
    //print headers
    for(int i=0; i<columnNo; i++){
        printf("|%-*s",columnLength[i] ,header[i]);
    }
    printf("|\n");
    //print header's bottom border
    printf("+");
    for(int i=0; i<columnNo; i++){
        for(int j=0; j<columnLength[i];j++){
            printf("-");
        }
        printf("+");
    }
    printf("\n");
    //print data
    FILE *fp;
    fp = fopen(fileName,fileMode);
    if(fp==NULL){
        system("cls");
        fclose(fp);
        printf("File Not Found...\nEnter to continue...");
        getch();
        return;
    }
    struct CHECKIN checkin;
    // Read and print each record with dynamic column lengths
    while (fread(&checkin, sizeof(checkin), 1, fp) > 0) {
        for (int i = 0; i < columnNo; i++) {
            printf("|%-*s", columnLength[i], i == 0 ? checkin.studentName : (i == 1 ? checkin.bookId : (i == 2 ? checkin.title : 
                    (i == 3 ? checkin.studentClass : (i ==4 ? checkin.checkInDate : (i==5 ? checkin.checkOutDate : checkin.studentPhone))))));
        }
        printf("|\n");
        printf("+");
        for(int i=0; i<columnNo; i++){
            for(int j=0; j<columnLength[i];j++){
                printf("-");
            }
            printf("+");
        }
        printf("\n");
    }
    fclose(fp);
    printf("\nEnter to continue...");
    getch();
}


//a function that check in books
void checkInBook(){
    system("cls");
    greetingMessage(25, 3, "~: Book Check-In :~");
    struct CHECKIN checkIn;
    struct BOOK book;
    struct STUDENT student;
    checkIn = inputCheckInData();
    FILE *checkinfile, *bookfile, *studentfile;
    checkinfile = fopen("checkInData.dat", "ab+");
    bookfile = fopen("bookData.dat", "rb");
    studentfile = fopen("studentData.dat", "rb");
    if(checkinfile==NULL||bookfile==NULL||studentfile==NULL){
        system("cls");
        fclose(checkinfile);
        fclose(bookfile);
        fclose(studentfile);
        printf("File Not Found...\nEnter to continue...");
        getch();
        return;
    }
    int found1 = 0;
    int found2 = 0;
    while (fread(&book, sizeof(struct BOOK), 1, bookfile) == 1 || fread(&student, sizeof(struct STUDENT), 1, studentfile) == 1) {
        if (strcmp(book.title, checkIn.title) == 0) {
            found1 = 1;
        }
        if (strcmp(student.student_name, checkIn.studentName) == 0) {
            found2 = 1;
        }
    }
    fclose(bookfile);
    fclose(studentfile);
    if (found1 && found2) {
        gotoxy(30, 22);
        printf("Press enter to add Check-In record.....");
        getch();
        fwrite(&checkIn, sizeof(struct CHECKIN), 1, checkinfile);
        fclose(checkinfile);
        gotoxy(30, 24);
        printf("Record successfully saved.....");
        gotoxy(30, 25);
        printf("Press any key to continue.....");
        getch();
    } else {
        gotoxy(60, 22);
        fclose(checkinfile);
        printf("Student or Book not found...");
        errorMessage(60,23);
    }
}

//a function that view current checked in books
void currentCheckInBook(){
    system("cls");
    char header[][20] = {"STUDENT NAME", "BOOK ID", "BOOK NAME", "STD. CLASS", "CHECK-IN-DATE", "CHECK-OUT-DATE", "PHONE"};
    int columnLen[] = {20,10,25,15,15,15,12};
    int columnNo = 7;
    char fileName[] = "checkInData.dat";
    char fileMode[] = "rb";
    greetingMessage(26, 2, "~: Current Checked-In Books :~");
    printDataTable(header, columnLen, columnNo, fileName, fileMode);
}

//a function that check out books
void checkOutBook(){
    system("cls");
    greetingMessage(25, 3, "~: Book Check-Out :~");
    struct CHECKIN checkIn;
    checkIn = inputCheckInData();
    FILE *fp = fopen("checkInData.dat", "rb+");
    if(fp==NULL){
        system("cls");
        fclose(fp);
        printf("File Not Found...\nEnter to continue...");
        getch();
        return;
    }
    // Create a temporary file to store the records that are not being deleted
    FILE *tempFile = fopen("tempfile.dat", "wb"); // Open for writing
    FILE *checkoutfile = fopen("checkOutData.dat", "ab+");
    if(tempFile==NULL){
        system("cls");
        fclose(fp);
        printf("Error File openning...\nEnter to continue...");
        getch();
        return;
    }
    struct CHECKIN checkIn2;
    int deleted = 0;
    // Read and process each book record
    while (fread(&checkIn2, sizeof(checkIn2), 1, fp) > 0) {
        // Check if the book name matches the name to be deleted
        if (!strcmp(checkIn2.studentName, checkIn.studentName) || !strcmp(checkIn2.bookId, checkIn.bookId) || !strcpy(checkIn2.title, checkIn.title)) {
            // Book to be deleted - skip it
            fwrite(&checkIn, sizeof(checkIn), 1, checkoutfile);
            deleted = 1;
        } else {
            // Write the book to the temporary file (not being deleted)
            fwrite(&checkIn2, sizeof(checkIn2), 1, tempFile);
        }
    }
    // Close both files
    fclose(fp);
    fclose(tempFile);
    // Remove the original file
    remove("checkInData.dat");
    // Rename the temporary file to the original file name
    if (rename("tempfile.dat", "checkInData.dat") == 0) {
        if (deleted) {
            gotoxy(30, 22);
            printf("Checked-out successfully.\n");
        } else {
            gotoxy(30, 17);
            printf("No record found...\n");
        }
    } else {
        gotoxy(30, 17);
        printf("Error renaming the file.\n");
    }
    gotoxy(30, 25);
    printf("Press any key to continue.....");
    getch();
}

//a function that view checked out books
void checkOutHistory(){
    system("cls");
    char header[][20] = {"STUDENT NAME", "BOOK ID", "BOOK NAME", "STD. CLASS", "CHECK-IN-DATE", "CHECK-OUT-DATE", "PHONE"};
    int columnLen[] = {20,10,25,15,15,15,12};
    int columnNo = 7;
    char fileName[] = "checkOutData.dat";
    char fileMode[] = "rb";
    greetingMessage(26, 2, "~: Current Checked-Out Books :~");
    printDataTable(header, columnLen, columnNo, fileName, fileMode);
}

