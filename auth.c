char *DB = "clients";
const size_t USRLEN = 8, PASSLEN = 8, ADDRLEN = 15;
size_t CLIENTREGLEN = USRLEN + PASSLEN + 1, SESSIONREGLEN = USRLEN + ADDRLEN + 1;

char lookup_user(char *username, char *password) {
	FILE *db = fopen(DB, "r");
	char *buffer;

	if (!db) {
		printf("Error opening user database");
		return 1;
	}

	char *user = calloc(15, 1), *pass;

	if (password == NULL) {		
		while(getline(&buffer, &CLIENTREGLEN, db) != -1) {
			sscanf(buffer, "%s;", user);
			// printf("[user] \"%s\"\n", user);
			if (strcmp(username, user) == 0)
				return 0;
		}
	}
	else {
		pass = calloc(8, 1);
		while(getline(&buffer, &CLIENTREGLEN, db) != -1) {
			sscanf(buffer, "%s;%s", user, pass);
			// printf("[user] \"%s\", [pass] \"%s\"\n", user, pass);
			if (strcmp(username, user) == 0 && strcmp(password, pass) == 0)
				return 0;
		}
	}

	fclose(db);
	return 1;
}

char lookup_session(char *username, char *address) {
	FILE *db = fopen(DB, "r");
	char *buffer;

	if (!db) {
		printf("Error opening user database");
		return 1;
	}

	char *user = calloc(15, 1), *addr = calloc(8, 1);
	while(getline(&buffer, &SESSIONREGLEN, db) != -1) {
		sscanf(buffer, "%s;%s", user, addr);
		// printf("[user] \"%s\", [addr] \"%s\"\n", user, addr);
		if (strcmp(username, user) == 0 && strcmp(address, addr) == 0)
			return 0;

	}

	fclose(db);

	return 1;
}

char add_user(char *username, char *password) {
	return 0;
}

char rm_user() {
	return 0;
}

char add_session() {
	return 0;
}

char rm_session() {
	return 0;
}

char login(char *buffer, char *address) {
	char *user, *pass, error;
	sscanf(buffer, "%s;%s", user, pass);

	if (error = lookup_user(user, pass))
		return error;

	rm_session(address);
	add_session(user, address);
}

char login_session(char *username, char *address) {
	return lookup_session(username, address);
}

char logout(char *address) {
	return rm_session(address);
}

char signup(char *username) {
	return lookup_user(username, NULL);
}
