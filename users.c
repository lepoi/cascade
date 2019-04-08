#include "users.h"

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
    char *buffer, active, *username, *password, *email;
    FILE *user_db = fopen(USER_DB, "rb+");

    if (!user_db)
	return 1;

    // TODO: free current user tree

    u_state.users = NULL;
    u_state.n_users = 0;

    len = *((ushort *) fgets(buffer, N_USERS_SIZE, user_db));
    buffer = fgets(buffer, USER_HEADER_SIZE + USER_REGISTER_SIZE * len, user_db);

    // seek first user register
    buffer += USER_HEADER_SIZE;

    while (user_db) {
	active = *buffer == 0 ? 0 : 1;

	// if user is active, load it to memory
	// only happens if last operation was a deletion
	if (active) {
	    buffer += ACTIVE_SIZE;

	    strcpy(username, buffer);
	    buffer += USERNAME_SIZE;

	    strcpy(password, buffer);
	    buffer += PASSWORD_SIZE;

	    strcpy(email, buffer);
	    buffer += EMAIL_SIZE;

	    if (add_user_node(u_state.users,username, password, email))
		++u_state.n_users;
	}
	// move pointer one whole register
	else
	    buffer += USER_REGISTER_SIZE;
    }

    fclose(user_db);

    return 0;
}

// save users to disk
char save_user_db() {
    char *u_buffer = calloc(1, USER_HEADER_SIZE + USER_REGISTER_SIZE * u_state.n_users);
    char *len_users = malloc(2);
    unsigned char offset = 0;
    size_t index = 0;

    // write header to buffer
    sprintf(len_users, "%u", u_state.n_users);
    strdmps(u_buffer, len_users, N_USERS_SIZE);

    // iterate over suffix tree and insert user data
    user_trie_dump(u_state.users, u_buffer, &index);

    FILE *user_db = fopen(USER_DB, "wb+");

    if (!user_db)
	return 1;

    fwrite(u_buffer, USER_HEADER_SIZE + USER_REGISTER_SIZE * u_state.n_users, 1, user_db);

    return 0;
};

// insert user register
unsigned int add_user(char *username, char *password, char *email) {
    // user already exists
    if (is_user(u_state.users, username))
	return 1;

    // error adding user
    if (!add_user_node(u_state.users, username, password, email))
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

