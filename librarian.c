//include header files
#include<stdio.h>
#include<conio.h>
#include<windows.h>

#include "library.h"
#include "librarian.h"

//create a function to take input of librarian data
struct LIBRARIAN inputLibrarianData(){
    struct LIBRARIAN librarian;
    gotoxy(30,10);
    printf("Enter Librarian Name : ");
    fflush(stdin);
    gets(librarian.name);
    gotoxy(30,12);
    printf("Enter appoinment date : ");
    fflush(stdin);
    gets(librarian.appDate);
    gotoxy(30,14);
    printf("Enter Address : ");
    fflush(stdin);
    gets(librarian.address);
    gotoxy(30,16);
    printf("Enter phone Number : ");
    fflush(stdin);
    gets(librarian.phone);
    return librarian;
}

//create a function that show librarian information in tabular form
//5 argument receives (header file names-2D aray, column length in array form, column number, librarian data file name, file openning mode)
void printLibrarianTable(char (*header)[20], int columnLength[], int columnNo, char fileName[], char fileMode[]){
    
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
    struct LIBRARIAN librarian;
    // Read and print each record with dynamic column lengths
    while (fread(&librarian, sizeof(librarian), 1, fp) > 0) {
        for (int i = 0; i < columnNo; i++) {
            printf("|%-*s", columnLength[i], i == 0 ? librarian.name : (i == 1 ? librarian.appDate : (i == 2 ? librarian.address : librarian.phone)));
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

//create a function that add librarian data
void addLibrarian(){
    system("cls");
    struct LIBRARIAN librarian;
    FILE *fp = fopen("librarianData.dat","ab+");
    greetingMessage(25, 3, "~: ADD LIBRARIAN INFO :~");
    librarian = inputLibrarianData();
    gotoxy(30,22);
    printf("Press enter to add Librarian record.....");
    getch();
    fwrite(&librarian, sizeof(librarian), 1, fp);
    fclose(fp);
    gotoxy(30,24);
    printf("Librarian record is successfully added.....");
    gotoxy(30,25);
    printf("Press any key to continue.....");
    getch();
}

//create a function that delete librarian data
void deleteLibrarian(){
    system("cls");
    char name[100];
    greetingMessage(25,3, "~: Delete Librarian Record :~");
    gotoxy(30,10);
    printf("Enter Librarian Name : ");
    fflush(stdin);
    gets(name);
    FILE *fp = fopen("librarianData.dat", "rb+");
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
    struct LIBRARIAN librarian;
    int deleted = 0;
    // Read and process each book record
    while (fread(&librarian, sizeof(librarian), 1, fp) > 0) {
        // Check if the book name matches the name to be deleted
        if (!strcmp(librarian.name, name)) {
            // Book to be deleted - skip it
            deleted = 1;
        } else {
            // Write the book to the temporary file (not being deleted)
            fwrite(&librarian, sizeof(librarian), 1, tempFile);
        }
    }
    // Close both files
    fclose(fp);
    fclose(tempFile);
    // Remove the original file
    remove("librarianData.dat");
    // Rename the temporary file to the original file name
    if (rename("tempfile.dat", "librarianData.dat") == 0) {
        if (deleted) {
            gotoxy(30, 22);
            printf("Librarian record(s) deleted successfully.\n");
        } else {
            gotoxy(30, 17);
            printf("No librarian record found with the specified name.\n");
        }
    } else {
        gotoxy(30, 17);
        printf("Error renaming the file.\n");
    }
    gotoxy(30, 25);
    printf("Press any key to continue.....");
    getch();
}

//a function that view librarian record from database
void viewLibrarian(){
    system("cls");
    char header[][20]={"Name", "Apt. Date", "Address", "Phone"};
    int colLen[] = {20,13,70,12};
    int colNo = 4;
    char fileName[] = "librarianData.dat";
    char fileMode[] = "rb+";
    greetingMessage(26, 2, "~: Librarian Info :~");
    printLibrarianTable(header, colLen, colNo, fileName, fileMode);
}

//create a function that edit librarian data
void editLibrarianInfo(){
    int ch;
    while(1){
        system("cls");
        greetingMessage(6, 3, "~: LIBRARIAN INFO :~");
        char itemsList[][25] = {"Back", "Add Librarian Record", "Delete Librarian Record"};
        menu(15,9,3,itemsList);
        ch = choice(60,21,3);
        switch(ch){
            case 0:
                return;
            case 1:
                addLibrarian();
                break;
            case 2:
                deleteLibrarian();
                break;
            default:
                errorMessage(60,23);
        }
    }
}
