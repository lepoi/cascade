#define CHILDREN 27

#ifndef strcmp

#include <stdlib.h>

#endif

struct user_trie {
    char *username;
    char *password;
    char *email;
    struct user_trie *children[CHILDREN];
};

struct user_trie *new_user_node_empty() {
    struct user_trie *new_user = malloc(sizeof(struct user_trie *));
    new_user->username = NULL;
    new_user->password = NULL;
    new_user->email = NULL;

    for (char i = 0; i < CHILDREN; ++i)
	new_user->children[i] = NULL;

    return new_user;
};

struct user_trie *new_user_node(char *username, char *password, char *email) {
    struct user_trie *new_user = malloc(sizeof(struct user_trie *));
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    strcpy(new_user->email, email);

    for (char i = 0; i < CHILDREN; ++i)
	new_user->children[i] = NULL;

    return new_user;
};

char is_user(struct user_trie *root, char *username) {
    if (!root)
	return 0;

    if (strcmp(root->username, username) == 0)
	return 1;

    return is_user(root->children[*username - 45], ++username);
};

struct user_trie *add_user_node(struct user_trie *root, char *username, char *password, char *email) {
    char len = strlen(username);
    char index;

    for (char i = 0; i < len; ++i) {
	index = *(username + i) - 45;

	if (!root->children[index])
	    root->children[index] = new_user_node_empty();

	root = root->children[index];
    }

    if (root->username)
	return NULL;

    root->username = username;
    root->password = password;
    root->email = email;

    return root;
};

void rm_user_node(struct user_trie *root, char *username) {
    char len = strlen(username);
    char index;

    for (char i = 0; i < len; ++i) {
	index = *(username + i) - 45;

	if (!root->children[index])
	    return;

	root = root->children[index];
    }

    if (!root->username)
	return;

    root->username = NULL;
    root->password = NULL;
    root->email = NULL;

    free(root->username);
    free(root->password);
    free(root->email);
};

void user_trie_dump(struct user_trie *root, char *buffer, size_t *index) {
    if (!root)
	return;

    buffer += USER_HEADER_SIZE + USER_REGISTER_SIZE * (*index);

    // insert user
    if (root->username) {
	strdmps(buffer, root->username, strlen(root->username));
	buffer += USERNAME_SIZE;

	strdmps(buffer, root->password, strlen(root->password));
	buffer += PASSWORD_SIZE;

	strdmps(buffer, root->email, strlen(root->email));
	*index++;
    }

    for (char i = 0; i < CHILDREN; ++i)
	if (root->children[i])
	    user_trie_dump(root->children[i], buffer, index);
};

void print_user_nodes(struct user_trie *root) {
    if (!root)
	return;

    if (root->username)
	printf("U > %s, %s, %s\n", root->username, root->password, root->email);

    for (char i = 0; i < CHILDREN; ++i)
	print_user_nodes(root->children[i]);
};

