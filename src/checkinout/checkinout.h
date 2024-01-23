//create a check-in data representing structure
struct CHECKIN{
    char title[50];
    char bookId[15];
    char studentName[30];
    char studentClass[15];
    char studentPhone[12];
    char checkInDate[13];
    char checkOutDate[13];
};

//a function that check in books
void checkInBook(void);

//create a function to take input of checkIn data
struct CHECKIN inputCheckInData(void);

//a function that check in books
void checkInBook(void);

//a function that view current checked in books
void currentCheckInBook(void);

//a function that check out books
void checkOutBook(void);

//a function that view checked out books
void checkOutHistory(void);