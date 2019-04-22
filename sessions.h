#define SESSION_DB "./database/sessions.db"

#define INIT_SESSION_HEADER "\x00\x00\x00\x00"
#define SESSION_HEADER_SIZE 4
#define N_SESSIONS_SIZE 4

#define SESSION_REGISTER_SIZE 24
#define ADDRESS_SIZE 4

#include "./structs/session_trie.c"

// define structures used by this module
struct session_state {
    size_t n_sessions;
    struct session_trie *sessions;
};

struct session_state s_state;

// initialize state for this module
void init_session_state();

// initialize database file
char init_session_db();

// load existing database file to memory
char load_session_db();

// save session tree to disk
char save_session_db();

// database operations
char add_session(unsigned char *ip, char *username);
char rm_session(unsigned char *ip);

