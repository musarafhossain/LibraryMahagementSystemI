//include Header Files
#include<stdio.h>
#include<conio.h>
#include<windows.h>

#include "library.h"
#include "book.h"
#include "student.h"

//function declaration
void dashboard(void);
void checkIn(void);
void checkOut(void);
void booksInfo(void);
void studentsInfo(void);
void librarianInfo(void);
void help(void);

//define dashboard function
void dashboard(){
    system("cls");
    printf("Welcome to Dashboard...Enter to continue");
    getch();
}

//define checkIn function
void checkIn(){
    system("cls");
    printf("Welcome to CheckIn...Enter to continue");
    getch();
}

//define checkOut function
void checkOut(){
    system("cls");
    printf("Welcome to CheckOut...Enter to continue");
    getch();
}

//define booksInfo function
void booksInfo(){
    int ch;
    while(1){ //infinite loop
        system("cls");
        greetingMessage(6, 3, "~: BOOKS INFO :~");
        char itemsList[][25] = {"Back", "Add Book Record", "Delete Book Record","View Current Books", "Update Book Record", "Pending Books"};
        menu(15,9,6,itemsList);
        ch = choice(60,21,6);
        switch(ch){
            case 0: 
                return; //Exit the function
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                viewBook();
                break;
            case 4:
                updateBook();
                break;
            case 5:
                //pendingBook();
                break;
            default:
                errorMessage(60,23);
        }
    }
}

//define studentsInfo function
void studentsInfo(){
    int ch;
    while(1){ //infinite loop
        system("cls");
        greetingMessage(6, 3, "~: STUDENTS INFO :~");
        char itemsList[][25] = {"Back", "Add Student Record", "Delete Student Record","View Current Students", "Update Student Record"};
        menu(15,9,5,itemsList);
        ch = choice(60,21,5);
        switch(ch){
            case 0: 
                return; //Exit the function
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                viewStudent();
                break;
            case 4:
                updateStudent();
                break;
            default:
                errorMessage(60,23);
        }
    }
}

//define librarianInfo function
void librarianInfo(){
    system("cls");
    printf("Welcome to LibrarianInfo...Enter to continue");
    getch();
}

//define help function
void help(){
    system("cls");
    printf("Welcome to Help...Enter to continue");
    getch();
}

int main(){
    while (1){ // Infinite loop
        //clear console
        system("cls");
        //print greeting Message
        greetingMessage(6, 3, "~: Welcome to Book Heaven Library :~");
        //print menu
        menu(15,9,8,(char[][25]){"Exit", "Dashboard", "Check In", "Check Out", "Books Info", 
                                "Students Info", "Librarian Info", "Help"});
        //print date
        printDate(100,4);
        //get choice to complete specific task
        int ch = choice(60,21,8);
        // Define an array of function pointers
        void (*functions[])(void) = {NULL, dashboard, checkIn, checkOut, booksInfo, studentsInfo, librarianInfo, help};
        // Check if the choice is within a valid range and call the corresponding function
        if (ch == 0) {
            // Terminate the program when 0 is selected
            exit(0);
        } else if (ch >= 1 && ch <= 7 && functions[ch] != NULL) {
            // Call the corresponding function for valid choices
            functions[ch]();
        } else {
            errorMessage(60, 23);
        }                 
    }
}