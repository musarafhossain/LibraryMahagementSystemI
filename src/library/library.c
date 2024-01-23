//include header files
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

#include "library.h"

//function define

//a function that print anything at any position in console
//2 argument receives (x-distance, y-distance)
void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//a function that print greeting message in a box at any position
//3 argument receives (x-distance, y-distance, message to print[max char- 43])
void greetingMessage(int x, int y, char msg[]){
    int msgX = x+((45-strlen(msg))/2); //calculate x-distance to set the messsage at the centre of the box
    gotoxy(x, y);
    printf("+=============================================+\n");
    gotoxy(x, y += 1);
    printf("| %-43s |\n", ""); // Empty space for alignment
    gotoxy(x, y += 1);
    printf("| %-43s |\n", ""); // Empty space for alignment
    gotoxy(msgX, y);
    printf("%s\n", msg);
    gotoxy(x, y += 1);
    printf("| %-43s |\n", ""); // Empty space for alignment
    gotoxy(x, y += 1);
    printf("+=============================================+\n");
}

//a function that print a menu box at any position
//4 argument receives (x-distance, y-distance, number of items, itemList[][25])
void menu(int x, int y,int items, char itemsList[][25]) {
    int i;
    items--;
    char data[30];
    gotoxy(x, y);
    printf("+-----------------------------+\n");
    gotoxy(x, y += 1);
    printf("| %-27s |\n", "Menu");
    gotoxy(x, y += 1);
    printf("+-----------------------------+\n");
    for (i = 0; i <= items; i++) {
        sprintf(data, "%d. %s", i, itemsList[i]); //storing data for temporary
        gotoxy(x, y += 1);
        printf("| %-27s |", data);
    }
    gotoxy(x, y += 1);
    printf("+-----------------------------+\n");
}

//a function that print current date at any position
//2 argument receives (x-distance, y-distance)
void printDate(int x, int y){
    // Declare a tm structure to store the current date and time
    struct tm *current_time;
    time_t t;
    // Get the current time
    t = time(NULL);
    current_time = localtime(&t);
    // Extract the components of the date
    int year = current_time->tm_year + 1900; // Years since 1900
    int month = current_time->tm_mon + 1;    // Months (0-11, so add 1)
    int day = current_time->tm_mday;         // Day of the month
    // Print the current date
    gotoxy(x,y);
    printf("Date: %02d-%02d-%04d\n", day, month, year);
}

//a function that takes input a choice number and return it
//3 argument receive (x-distance, y-distance, how many choice items)
int choice(int x,int y, int a){
    int ch;
    a--;
    gotoxy(x,y);
    printf("Enter your choice (0-%d):- ",a);
     do {
        ch = _getch();
    } while (ch < '0' || ch > '0' + a);
    return ch - '0';
}

//a function that print a error message at any position 
//2 argument receives (x-distance, y-distance)
void errorMessage(int x, int y){
    gotoxy(x,y);
    printf("Something went wrong...");
    gotoxy(x,y+=1);
    printf("Press any key to continue.....");
    getch();
}
