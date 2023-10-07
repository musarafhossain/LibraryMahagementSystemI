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
        int ch; 
        ch = choice(60,21,8);
        //switch case to perform specific task
        switch (ch){
            case 0:
                exit(1);
            case 1:
                //dashboard();
                break;
            case 2:
                //checkIn();
                break;
            case 3:
                //checkOut();
                break;
            case 4:
                //booksInfo();
                break;
            case 5:
                //studentsInfo();
                break;
            case 6:
                //LibrarianInfo();
                break;
            case 7:
                //help();
                break;
            default:
                errorMessage(60,23);
        }                 
    }
}