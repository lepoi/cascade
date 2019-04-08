#define USER_DB "./database/users.db"

#define INIT_USER_HEADER "\x00\x00"
#define USER_HEADER_SIZE 2
#define N_USERS_SIZE 2

#define USER_REGISTER_SIZE 100
#define ACTIVE_SIZE 1
// #define POINTER_SIZE 4
#define USERNAME_SIZE 20
#define PASSWORD_SIZE 20
#define EMAIL_SIZE 60

#include "./structs/user_trie.c"

// define structures used by this module
struct user_state {
    size_t n_users;
    struct user_trie *users;
};

// initialize state for this module
struct user_state u_state = { 0, new_user_node_empty() };

// initialize database file
char init_user_db();

// load existing databse file to memory
char load_user_db();

// save user tree to disk
char save_user_db();

// database operations
unsigned int add_user(char *username, char *password, char *email);
char rm_user(char *username);

