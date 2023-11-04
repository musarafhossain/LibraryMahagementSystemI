//include header files
#include<stdio.h>
#include<conio.h>
#include<windows.h>

#include "library.h"
#include "student.h"

//create a function to take input of book data
struct STUDENT inputStudentData(){
    struct STUDENT student;
    gotoxy(30,10);
    printf("Enter Student Name :- ");
    fflush(stdin);
    gets(student.student_name);
    gotoxy(30,12);
    printf("Enter Roll No. :- ");
    fflush(stdin);
    gets(student.roll_no);
    gotoxy(30,14);
    printf("Enter Class :- ");
    fflush(stdin);
    gets(student.student_class);
    gotoxy(30,16);
    printf("Enter Stream (Science/Arts/Commers) :- ");
    fflush(stdin);
    gets(student.stream);
    gotoxy(30,18);
    printf("Enter Subject :- ");
    fflush(stdin);
    gets(student.subject);
    gotoxy(30,20);
    printf("Enter Phone number (+91) :- ");
    fflush(stdin);
    gets(student.phone);
    return student;
}

//create a function that show book information in tabular form
//5 argument receives (header file names-2D aray, column length in array form, column number, book data file name, file openning mode)
void printStudentTable(char (*header)[20], int columnLength[], int columnNo, char fileName[], char fileMode[]){
    
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
    struct STUDENT student;
    //serial number of each student data
    int temp=1;
    // Read and print each record with dynamic column lengths
    while (fread(&student, sizeof(student), 1, fp) > 0) {
        char serial[8];
        //serial number of each student data
        sprintf(serial, " %d", temp);
        temp++;
        for (int i = 0; i < columnNo; i++) {
            printf("|%-*s", columnLength[i], i ==0 ? serial : (i == 1 ? student.student_name : (i == 2 ? student.roll_no : (i == 3 ? student.student_class : (i == 4 ? student.stream : (i ==5 ? student.subject : student.phone))))));
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

//a function that add book record in database
void addStudent(){
    system("cls");
    FILE *fp;
    struct STUDENT student;
    fp = fopen("studentData.dat","ab+");
    if(fp==NULL){
        system("cls");
        fclose(fp);
        printf("File Not Found...\nEnter to continue...");
        getch();
        return;
    }
    greetingMessage(25, 3, "~: Add New Student Record :~");
    student = inputStudentData();
    gotoxy(30,22);
    printf("Press enter to add student record.....");
    getch();
    fwrite(&student, sizeof(student), 1, fp);
    fclose(fp);
    gotoxy(30,24);
    printf("Student record is successfully added.....");
    gotoxy(30,25);
    printf("Press any key to continue.....");
    getch();

}

//a function that delete student record from database
void deleteStudent(){
    system("cls");
    char temp[100];
    greetingMessage(25,3, "~: Delete Student Record :~");
    gotoxy(30,10);
    printf("Enter Student Name or Roll : ");
    fflush(stdin);
    gets(temp);
    FILE *fp = fopen("studentData.dat", "rb+");
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
    struct STUDENT student;
    int deleted = 0;
    // Read and process each book record
    while (fread(&student, sizeof(student), 1, fp) > 0) {
        // Check if the book name matches the name to be deleted
        if (!strcmp(student.student_name, temp) || !strcmp(student.roll_no, temp)) {
            // Book to be deleted - skip it
            deleted = 1;
        } else {
            // Write the book to the temporary file (not being deleted)
            fwrite(&student, sizeof(student), 1, tempFile);
        }
    }
    // Close both files
    fclose(fp);
    fclose(tempFile);
    // Remove the original file
    remove("studentData.dat");
    // Rename the temporary file to the original file name
    if (rename("tempfile.dat", "studentData.dat") == 0) {
        if (deleted) {
            gotoxy(30, 22);
            printf("Student record(s) deleted successfully.\n");
        } else {
            gotoxy(30, 17);
            printf("No student record found with the specified name.\n");
        }
    } else {
        gotoxy(30, 17);
        printf("Error renaming the file.\n");
    }
    gotoxy(30, 25);
    printf("Press any key to continue.....");
    getch();
}

//a function that view student record from database
void viewStudent(){
    system("cls");
    char header[][20] = {"SL N0.", "NAME", "ROLL", "CLASS", "STREAM", "SUBJECT", "PHONE"};
    int columnLen[] = {8,30,10,15,10,20,12};
    int columnNo = 7;
    char fileName[] = "studentData.dat";
    char fileMode[] = "rb";
    greetingMessage(26, 2, "~: Current Students :~");
    printStudentTable(header, columnLen, columnNo, fileName, fileMode);
}

//a function that update student record of database
void updateStudent(){
    system("cls");
    char temp[100];
    greetingMessage(25,3, "~: Update Students Record :~");
    gotoxy(30,10);
    printf("Enter Student Name or Roll:- ");
    fflush(stdin);
    gets(temp);
    // Open the file for reading and writing
    FILE *fp = fopen("studentData.dat","rb+");
    FILE *tempFile = fopen("tempfile.dat", "wb");
    if(fp==NULL){
        system("cls");
        fclose(fp);
        printf("File Not Found...\nEnter to continue...");
        getch();
        return;
    }
    // Find the book with the specified book ID or Name
    struct STUDENT student, newData;
    int found = 0;
    while (fread(&student, sizeof(student), 1, fp) == 1) {
        if (!strcmp(temp, student.student_name)||!strcmp(temp, student.roll_no)) {
            found = 1;
        }else {
            // Write the book to the temporary file (not being deleted)
            fwrite(&student, sizeof(student), 1, tempFile);
        }
    }
    if (found) {
        fclose(tempFile);
        fclose(fp);
        // Remove the original file
        remove("studentData.dat");

        rename("tempfile.dat", "studentData.dat");
        gotoxy(30,13);
        printf("Student Found...Press any key to continue.....");
        getch();
        // Move the file pointer back to the beginning of the found book
        fseek(fp, sizeof(student), SEEK_SET);
        system("cls");
        greetingMessage(25, 3, "~: Update Students Record :~");
        newData = inputStudentData();
        FILE *fp = fopen("studentData.dat", "ab+");
        // Write the updated book data to the file
        fwrite(&newData, sizeof(student), 1, fp);
        gotoxy(30,22);
        printf("Student data updated successfully...");
        // Close the file
        fclose(fp);
    } else {
        gotoxy(30,13);
        printf("Student with Name or Roll %s not found.\n", temp);
    }
    gotoxy(30,25);
    printf("Press any key to continue.....");
    getch();
}



