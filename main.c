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

    // open database and load into memory
    if (error = load_user_db())
	printf("Error %u while loading user databse, initializing DB...\n");
    else
	printf("Successfully loaded user databse\n");

    // anything else
    // unsigned int a = add_user("poi??", "terminal??", "terminallyquack@gmail.com??", 0);

    return 0;
}

