//create a BOOK stucture to represent a book information
struct BOOK{
    char title[42];
    char author[27];
    char id[10];
    char price[12];
    char publicationYear[12];
};

//a function that take input book information from user
struct BOOK inputBookData(void);

//create a function that show book information in tabular form
//5 argument receives (header file names-2D aray, column length in array form, column number, book data file name, file openning mode)
void printBookTable(char (*)[20], int[], int, char[], char[]);

//a function that add book record in database
void addBook(void);

//a function that delete book record from database
void deleteBook(void);

//a function that view book record from database
void viewBook(void);

//a function that update book record of database
void updateBook(void);