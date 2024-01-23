//create a STUDENT stucture to represent a student information
struct STUDENT{
    char student_name[32];
    char roll_no[12];
    char student_class[17];
    char stream[12];
    char subject[22];
    char phone[12];

};

//a function that take input student information from user
struct STUDENT inputStudentData(void);

//create a function that show student information in tabular form
//5 argument receives (header file names-2D aray, column length in array form, column number, student data file name, file openning mode)
void printBookTable(char (*)[20], int[], int, char[], char[]);

//a function that add student record in database
void addStudent(void);

//a function that delete student record from database
void deleteStudent(void);

//a function that view student record from database
void viewStudent(void);

//a function that update student record of database
void updateStudent(void);