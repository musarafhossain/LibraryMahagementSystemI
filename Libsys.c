//include Header Files
#include<stdio.h>
#include<conio.h>
#include<windows.h>

#include "library.h"

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
        void (*functions[])(void) = {NULL, /*dashboard, checkIn, checkOut, booksInfo, studentsInfo, librarianInfo, help*/};
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