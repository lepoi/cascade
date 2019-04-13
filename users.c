#include "users.h"

void init_user_state() {
    u_state.n_users = 0;
    u_state.users = new_user_node_empty();
};

// clear database, write header
char init_user_db() {
    FILE *user_db = fopen(USER_DB, "wb+");

    if (!user_db)
	return 1;

    // write empty file to storage
    fwrite(INIT_USER_HEADER, USER_HEADER_SIZE, 1, user_db);
    fclose(user_db);

    return 0;
}

// load into memory
char load_user_db() {
    ushort len;
    int i = 0;
    char *pointer;
    char *buffer, *username, *password, *email;
    FILE *user_db = fopen(USER_DB, "rb+");

    username = calloc(1, USERNAME_SIZE);
    password = calloc(1, PASSWORD_SIZE);
    email = calloc(1, EMAIL_SIZE);

    init_user_state();

    if (!user_db)
	return 1;

    // TODO: free current user tree

    buffer = (char *) malloc(N_USERS_SIZE);
    pointer = buffer;

    if (fgets(buffer, N_USERS_SIZE + 1, user_db) == NULL)
	return 1;

    if (!(len = *buffer))
	return 0;

    // TODO: test with registered users
    if (fgets(buffer, USER_REGISTER_SIZE * len + 1, user_db) == NULL)
	return 1;

    while (i++ < len) {
	strcpy(username, buffer);
	buffer += USERNAME_SIZE;

	strcpy(password, buffer);
	buffer += PASSWORD_SIZE;

	strcpy(email, buffer);
	buffer += EMAIL_SIZE;

	if (add_user_node(u_state.users, username, password, email))
	    ++u_state.n_users;
    }

    free(username);
    free(password);
    free(email);

    //fclose(user_db);

    return 0;
}

// save users to disk
char save_user_db() {
    printf("save_user_db 0 (len: %u)\n", u_state.n_users);

    char *u_buffer = calloc(1, USER_HEADER_SIZE + USER_REGISTER_SIZE * u_state.n_users);
    ushort *n_users = (ushort *) u_buffer;
    char error, offset = 0;
    size_t index = 0;
    FILE *user_db = fopen(USER_DB, "wb+");

    if (!user_db)
	return 1;

    // write header to buffer
    *n_users = u_state.n_users;

    // iterate over suffix tree and insert user data
    user_trie_dump(u_state.users, u_buffer + USER_HEADER_SIZE, &index);

    printf("save_user_db 1\n");

    stddmpx(u_buffer, USER_HEADER_SIZE + USER_REGISTER_SIZE * u_state.n_users);
    fwrite(u_buffer, USER_HEADER_SIZE + USER_REGISTER_SIZE * u_state.n_users, 1, user_db);

    printf("save_user_db 2\n");

    free(n_users);
    free(u_buffer);

    error = ferror(user_db);
    fclose(user_db);

    printf("save_user_db 3\n");

    return error;
};

// insert user register
char add_user(char *username, char *password, char *email) {
    // user already exists
    if (is_user(u_state.users, username))
	return 1;

    struct user_trie *node = add_user_node(u_state.users, username, password, email);

    // error adding user
    if (!node)
	return 2;

    u_state.n_users++;

    // error saving database
    if (save_user_db())
	return 3;

    return 0;
}

// de-activate user register
char rm_user(char *username) {
    // TODO:
    //	change user list in memory
    //	write to disk

    return 0;
}

