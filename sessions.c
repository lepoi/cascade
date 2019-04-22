#include "sessions.h"

void init_session_state() {
    s_state.n_sessions = 0;
    s_state.sessions = new_session_node_empty();
};

// clear database, write header
char init_session_db() {
    FILE *session_db = fopen(SESSION_DB, "wb+");

    if (!session_db)
	return 1;

    // write empty file to storage
    fwrite(INIT_SESSION_HEADER, SESSION_HEADER_SIZE, 1, session_db);
    fclose(session_db);

    return 0;
};

// load into memory
char load_session_db() {
    size_t len;
    int i = 0;
    unsigned char *pointer, *ip;
    char *buffer, *username;
    FILE *session_db = fopen(SESSION_DB, "rb+");

    ip = malloc(ADDRESS_SIZE);
    username = malloc(USERNAME_SIZE);

    init_session_state();

    if (!session_db)
	return 1;

    // TODO: free session tree

    buffer = (char *) malloc(N_SESSIONS_SIZE);
    pointer = buffer;

    if (fgets(buffer, N_SESSIONS_SIZE + 1, session_db) == NULL)
	return 1;

    if (!(len = *buffer))
	return 0;

    if (fgets(buffer, SESSION_REGISTER_SIZE * len + 1, session_db) == NULL)
	return 1;

    while (i++ < len) {
	strcpy(ip, buffer);
	buffer += ADDRESS_SIZE;

	strcpy(username, buffer);
	buffer += USERNAME_SIZE;

	if (add_session_node(s_state.sessions, ip, username))
	    ++s_state.n_sessions;
    }

    free(ip);
    free(username);

    //fclose(session_db);

    return 0;
};

// save sessions to disk
char save_session_db() {
    char *s_buffer = calloc(1, SESSION_HEADER_SIZE + SESSION_REGISTER_SIZE * s_state.n_sessions);
    size_t *n_sessions = (size_t *) s_buffer, index = 0;
    char error, offset = 0;
    FILE *session_db = fopen(SESSION_DB, "wb+");

    if (!session_db)
	return 1;

    // write header to buffer
    *n_sessions = s_state.n_sessions;

    // iterate over trie and insert session data
    session_trie_dump(s_state.sessions, s_buffer + SESSION_HEADER_SIZE, &index);

    fwrite(s_buffer, SESSION_HEADER_SIZE + SESSION_REGISTER_SIZE * s_state.n_sessions, 1, session_db);

    free(n_sessions);
    free(s_buffer);

    error = ferror(session_db);
    fclose(session_db);

    return error;
};

// insert session register
char add_session(unsigned char *ip, char *username) {
    struct session_trie *node;
    char overwrite = 0;

    // if session already exists, change username
    if (node = lookup_session(s_state.sessions, ip, 0)) {
	strcpy(node->username, username);
	overwrite = 1;
    }
    // else, create new node
    else
	node = add_session_node(s_state.sessions, ip, username);

    // error adding session
    if (!node)
	return 1;

    if (!overwrite)
	s_state.n_sessions++;

    // error saving database
    if (save_session_db())
	return 2;

    return 0;
}

// de-activate session register
char rm_session(unsigned char *ip) {
    // TODO:
    //	change user list in memory
    //	write to disk

    return 0;
}

