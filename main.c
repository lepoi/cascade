#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.c"
#include "state.c"
#include "users.c"

int main(int argc, char *args[]) {
    char error = 0;

    // check for init flag
    if (argc > 1 && strcmp(args[1], "init") == 0) {
	if (error = init_user_db()) {
	    printf("Error %u while initalizing user database, exiting...\n", error);
	    exit(1);
	}
	else
	    printf("Successfully initialized user databse\n");
    }

    // initialize user state
    init_user_state();

    // load users from disk to memory
    if (error = load_user_db()) {
	printf("Error %u loading user databse, exiting...\n", error);
	exit(1);
    }
    else
	printf("Successfully loaded user databse\n");

    // print error info
    //if (error = add_user("poi", "poi", "terminallyquack@gmail.com"))
    //if (error = add_user("magda", "magda", "edgarmv97@gmail.com"))
    if (error = add_user("alejanky", "janky", "alejanky@gmail.com"))
	printf("Error registering user: ");
    else
	printf("Registered user\n");

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
    };

    return 0;
};

