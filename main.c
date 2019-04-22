#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.c"
#include "state.c"
#include "users.c"

// environment setup
void init_databases() {
    char error;

    // initialize user database
    printf("Initializing user databse...");
    if (error = init_user_db()) {
	printf("ERROR %u, exiting...\n", error);
        exit(1);
    }
    else
        printf("DONE\n");

    // initialize session database
    printf("Initializing session databse...");
    if (error = init_session_db()) {
        printf("ERROR %u, exiting...\n", error);
        exit(1);
    }
    else
        printf("DONE\n");
};

void load_databases() {
    char error;

    // load users from disk
    printf("Loading user database...");
    if (error = load_user_db()) {
	printf("ERROR %u\n", error);
	exit(1);
    }
    else
	printf("DONE\n");

    // load sessions from disk
    printf("Loading session database...");
    if (error = load_session_db()) {
	printf("ERROR %u\n", error);
	exit(1);
    }
    else
	printf("DONE\n");
};

// database manipulation
void register_user(char *username, char *password, char *email) {
    char error;

    printf("Registering user with username \"%s\"...", username);
    if (error = add_user(username, password, email))
	printf("ERROR: ");
    else
	printf("DONE\n");

    // print error info
    switch (error) {
	case 1:
		printf("Username already exists\n");
		break;
	case 2:
		printf("Error adding user node\n");
		break;
	case 3:
		printf("Error saving user database\n");
		break;
	default: break;
    }
};

void register_session(unsigned char *ip, char *username) {
    char error;

    printf("Registering session with IP ");
    for (char i = 0; i < ADDRESS_SIZE;)
	printf("%u.", *(ip + i++));
    printf("..");

    if (error = add_session(ip, username))
	printf("ERROR: ");
    else
	printf("DONE\n");

    // print error info
    switch (error) {
	case 1:
		printf("Error adding session node\n");
		break;
	case 2:
		printf("Error saving session database\n");
		break;
	default: break;
    };
};

// testing
int main(int argc, char *args[]) {
    char error = 0;

    // check for init flag
    if (argc > 1 && strcmp(args[1], "init") == 0)
	init_databases();

    // load users from disk
    load_databases();

    // testing
    unsigned char *ip = "\xc0\xa8\x00\x00";
    register_session(ip, "poi3");

    return 0;
};

