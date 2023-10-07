//function declaration

//a function that print greeting message in a box at any position
//3 argument receives (x-distance, y-distance, message to print[max char- 43])
void greetingMessage(int, int, char[]);

//a function that print anything at any position in console
//2 argument receives (x-distance, y-distance)
void gotoxy(int, int);

//a function that print a menu box at any position
//4 argument receives (x-distance, y-distance, number of items, itemList[][25])
void menu(int, int, int, char[][25]);

//a function that print current date at any position
//2 argument receives (x-distance, y-distance)
void printDate(int, int);

//a function that takes input a choice number and return it
//3 argument receive (x-distance, y-distance, how many choice items)
int choice(int, int, int);

//a function that print a error message at any position 
//2 argument receives (x-distance, y-distance)
void errorMessage(int, int);