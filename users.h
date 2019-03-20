#define USER_DB "./database/users.db"

#define USER_HEADER_SIZE 100
#define USER_REGISTER_SIZE 100

#define ACTIVE_SIZE 1
#define POINTER_SIZE 4
#define USERNAME_SIZE 20
#define PASSWORD_SIZE 20
#define EMAIL_SIZE 51

#define INIT_USER_HEADER "0.........1,,,,,,,,,2.........3,,,,,,,,,4.........5,,,,,,,,6.........7,,,,,,,,,8.........9,,,,,,,,,"

// initialize database file
char init_user_db();

// load existing databse file to memory
char load_user_db();

// database operations
unsigned int add_user(char *username, char *password, char *email);
char rm_user(unsigned int reg);

