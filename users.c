#include "users.h"

char init_user_db() {
	user_db = fopen(USER_DB, "wb+");

	if (!user_db)
		return 1;

	// write empty file to storage
	fprintf(user_db, "%s", INIT_USER_HEADER);
	fclose(user_db);

	return 0;
}

FILE *open_user_db() {
	return fopen(USER_DB, "rb+");
}

char load_user_db() {

}

unsigned int add_user(char *username, char *password, char *email) {
	char *u_user = calloc(1, USERNAME_SIZE);
	char *u_pass = calloc(1, PASSWORD_SIZE);
	char *u_mail = calloc(1, EMAIL_SIZE);
	char *u_reg = calloc(1, USER_REGISTER_SIZE);

	strcpy(u_user, username);
	strcpy(u_pass, password);
	strcpy(u_mail, email);

	// printf("\xFF\x00\x00%X%X%X", u_user, u_pass, u_mail);
	printf("%X", 255);
	printf("%X%X%X%X", 0, 0, 0, 0);
	printf("%X%X%X%X", 0, 0, 0, 0);
	for (char i = 0; i < USERNAME_SIZE; i++)
		printf("%X", u_user[i]);
	for (char i = 0; i < PASSWORD_SIZE; i++)
		printf("%X", u_pass[i]);
	for (char i = 0; i < EMAIL_SIZE; i++)
		printf("%X", u_mail[i]);
	printf("\n");
}

char rm_user(unsigned int reg) {

}

