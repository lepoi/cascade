#define USER_DB "./database/users.db"

#define INIT_USER_HEADER "\x00\x00"
#define USER_HEADER_SIZE 2
#define N_USERS_SIZE 2

#define USER_REGISTER_SIZE 100
#define USERNAME_SIZE 20
#define PASSWORD_SIZE 20
#define EMAIL_SIZE 60

#include "./structs/user_trie.c"

// define structures used by this module
struct user_state {
    size_t n_users;
    struct user_trie *users;
};

struct user_state u_state;

// initialize state for this module
void init_user_state();

// initialize database file
char init_user_db();

// load existing database file to memory
char load_user_db();

// save user tree to disk
char save_user_db();

// database operations
char add_user(char *username, char *password, char *email);
char rm_user(char *username);

