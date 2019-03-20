#include "users.h"

// clear database, write header
char init_user_db() {
    FILE *user_db = fopen(USER_DB, "wb+");

    if (!user_db)
	return 1;

    // write empty file to storage
    fprintf(user_db, "%s", INIT_USER_HEADER);
    fclose(user_db);

    return 0;
}

// load into memory
char load_user_db() {
    FILE *user_db = fopen(USER_DB, "rb+");

    if (!user_db)
	return 1;

    // TODO: actually load into memory

    fclose(user_db);

    return 0;
}

// insert user register
unsigned int add_user(char *username, char *password, char *email) {
    char *u_reg = calloc(1, USER_REGISTER_SIZE);
    char *insert;
    size_t length;

    FILE *user_db = fopen(USER_DB, "ab+");

    if (!user_db)
	return 1;

    // insert active as 1
    strdmpc(u_reg, '\xff');
    unsigned char offset = 1;

    // insert previous and next user pointers
    insert = "\x0\x0\x0\x0";
    strdmps(u_reg + offset, insert, POINTER_SIZE);
    offset += POINTER_SIZE;

    strdmps(u_reg + offset, insert, POINTER_SIZE);
    offset += POINTER_SIZE;

    // insert user data
    length = min(strlen(username), USERNAME_SIZE);
    strdmps(u_reg + offset, username, length);
    offset += USERNAME_SIZE;

    length = min(strlen(password), PASSWORD_SIZE);
    strdmps(u_reg + offset, password, length);
    offset += PASSWORD_SIZE;

    length = min(strlen(email), EMAIL_SIZE);
    strdmps(u_reg + offset, email, length);

    fwrite(u_reg, USER_REGISTER_SIZE, 1, user_db) != 1;

    fclose(user_db);

    return 0;
}

// de-activate user register
char rm_user(unsigned int reg) {
    // TODO: update "hole"



    return 0;
}

