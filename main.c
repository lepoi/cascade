#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "users.c"

int main() {
	if (init_user_db())
		exit(1);

	add_user("poi", "terminal", "terminallyquack@gmail.com");

	return 0;
}

