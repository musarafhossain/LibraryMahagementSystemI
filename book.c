//include header files
#include<stdio.h>
#include<conio.h>
#include<windows.h>

#include "library.h"
#include "book.h"

//create a function to take input of book data
struct BOOK inputBookData(){
    struct BOOK book;
    gotoxy(30,10);
    printf("Enter Book ID :- ");
    fflush(stdin);
    gets(book.id);
    gotoxy(30,12);
    printf("Enter Book Title :- ");
    fflush(stdin);
    gets(book.title);
    gotoxy(30,14);
    printf("Enter Book Author Name :- ");
    fflush(stdin);
    gets(book.author);
    gotoxy(30,16);
    printf("Enter Book Price :- ");
    fflush(stdin);
    gets(book.price);
    gotoxy(30,18);
    printf("Enter Book Publication Year :- ");
    fflush(stdin);
    gets(book.publicationYear);
    return book;
}

//create a function that show book information in tabular form
//5 argument receives (header file names-2D aray, column length in array form, column number, book data file name, file openning mode)
void printBookTable(char (*header)[20], int columnLength[], int columnNo, char fileName[], char fileMode[]){
    
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
    struct BOOK book;
    //serial number of each student data
    int temp=1;
    // Read and print each record with dynamic column lengths
    while (fread(&book, sizeof(book), 1, fp) > 0) {
        char serial[8];
        //serial number of each student data
        sprintf(serial, " %d", temp);
        temp++;
        for (int i = 0; i < columnNo; i++) {
            printf("|%-*s", columnLength[i], i == 0 ? serial : (i==1 ? book.id : (i == 2 ? book.title : (i == 3 ? book.author : (i == 4 ? book.price : book.publicationYear)))));
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

//create a function to add book information in database
void addBook(){
    system("cls");
    struct BOOK book;
    greetingMessage(25,3,"~: Add New Book Record :~");
    book = inputBookData();
    gotoxy(30,20);
    printf("Press enter to add book.....");
    getch();
    FILE *fp;
    fp = fopen("bookData.dat","ab+");
    if(fp==NULL){
        system("cls");
        fclose(fp);
        printf("File Not Found...\nEnter to continue...");
        getch();
        return;
    }
    fwrite(&book, sizeof(book), 1, fp);
    fclose(fp);
    gotoxy(30,22);
    printf("Your book is successfully added.....");
    gotoxy(30,23);
    printf("Press any key to continue.....");
    getch();
}

//a function that delete book record from database
void deleteBook(){
    system("cls");
    char temp[100];
    greetingMessage(25,3, "~: Delete Books Record :~");
    gotoxy(30,10);
    printf("Enter Book ID or Name : ");
    fflush(stdin);
    gets(temp);
    FILE *fp = fopen("bookData.dat", "rb+");
    if(fp==NULL){
        system("cls");
        fclose(fp);
        printf("File Not Found...\nEnter to continue...");
        getch();
        return;
    }
    // Create a temporary file to store the records that are not being deleted
    FILE *tempFile = fopen("tempfile.dat", "wb"); // Open for writing
    if(tempFile==NULL){
        system("cls");
        fclose(fp);
        printf("Error File openning...\nEnter to continue...");
        getch();
        return;
    }
    struct BOOK book;
    int deleted = 0;
    // Read and process each book record
    while (fread(&book, sizeof(struct BOOK), 1, fp) > 0) {
        // Check if the book name matches the name to be deleted
        if (!strcmp(book.title, temp) || !strcmp(book.id, temp)) {
            // Book to be deleted - skip it
            deleted = 1;
        } else {
            // Write the book to the temporary file (not being deleted)
            fwrite(&book, sizeof(struct BOOK), 1, tempFile);
        }
    }
    // Close both files
    fclose(fp);
    fclose(tempFile);
    // Remove the original file
    remove("bookData.dat");
    // Rename the temporary file to the original file name
    if (rename("tempfile.dat", "bookData.dat") == 0) {
        if (deleted) {
            gotoxy(30, 22);
            printf("Book record(s) deleted successfully.\n");
        } else {
            gotoxy(30, 17);
            printf("No book record found with the specified name.\n");
        }
    } else {
        gotoxy(30, 17);
        printf("Error renaming the file.\n");
    }
    gotoxy(30, 25);
    printf("Press any key to continue.....");
    getch();
}

//a function that view book record from database
void viewBook(){
    system("cls");
    char header[][20] = {"SL NO.", "BOOK ID", "BOOK NAME", "AUTHOR NAME", "PRICE", "PUBL.YEAR"};
    int columnLen[] = {8,15,30,25,12,12};
    int columnNo = 6;
    char fileName[] = "bookData.dat";
    char fileMode[] = "rb";
    greetingMessage(26, 2, "~: Current Books :~");
    printBookTable(header, columnLen, columnNo, fileName, fileMode);
}

//a function that update book record of database
void updateBook(){
    system("cls");
    char temp[100];
    greetingMessage(25,3, "~: Update Books Record :~");
    gotoxy(30,10);
    printf("Enter Book ID or Name:- ");
    fflush(stdin);
    gets(temp);
    // Open the file for reading and writing
    FILE *fp = fopen("bookData.dat","rb+");
    FILE *tempFile = fopen("tempfile.dat", "wb"); // Open for writing
    if(fp==NULL){
        system("cls");
        fclose(fp);
        printf("File Not Found...\nEnter to continue...");
        getch();
        return;
    }
    // Find the book with the specified book ID or Name
    struct BOOK book, newData;
    int found = 0;
    while (fread(&book, sizeof(struct BOOK), 1, fp) == 1) {
        if (!strcmp(temp, book.id)||!strcmp(temp, book.title)) {
            found = 1;
        }else {
            // Write the book to the temporary file (not being deleted)
            fwrite(&book, sizeof(struct BOOK), 1, tempFile);
        }
    }
    if (found) {
        fclose(tempFile);
        fclose(fp);
        // Remove the original file
        remove("bookData.dat");

        rename("tempfile.dat", "bookData.dat");

        gotoxy(30,13);
        printf("Book Found...Press any key to continue.....");
        getch();
        system("cls");
        greetingMessage(25, 3, "~: Update Books Record :~");
        newData = inputBookData();
        FILE *fp = fopen("bookData.dat", "ab+");
        // Write the updated book data to the file
        fwrite(&newData, sizeof(struct BOOK), 1, fp);
        gotoxy(30,22);
        printf("Book data updated successfully...");
        // Close the file
        fclose(fp);
    } else {
        gotoxy(30,13);
        printf("Book with ID or Name %s not found.\n", temp);
    }
    gotoxy(30,25);
    printf("Press any key to continue.....");
    getch();
}
