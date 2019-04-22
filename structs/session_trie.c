#define SESSION_CHILDREN 256

#ifndef strcmp

#include <stdlib.h>

#endif

struct session_trie {
    unsigned char *ip;
    char *username;
    struct session_trie *children[SESSION_CHILDREN];
};

struct session_trie *new_session_node_empty() {
    struct session_trie *new_session = malloc(sizeof(struct session_trie));

    new_session->ip = NULL;
    new_session->username = NULL;

    for (unsigned char i = 0; i + 1 < SESSION_CHILDREN;)
	new_session->children[i++] = NULL;

    return new_session;
};

struct session_trie *new_session_node(unsigned char *ip, char *username) {
    struct session_trie *new_session = malloc(sizeof(struct session_trie));

    new_session->ip = malloc(ADDRESS_SIZE);
    new_session->username = malloc(USERNAME_SIZE);

    strcpy(new_session->ip, ip);
    strcpy(new_session->username, username);

    for (unsigned char i = 0; i + 1 < SESSION_CHILDREN;)
	new_session->children[i++] = NULL;

    return new_session;
};

struct session_trie *lookup_session(struct session_trie *root, unsigned char *ip, char depth) {
    if (!root || (depth == ADDRESS_SIZE && !root->username))
	return NULL;

    if (depth == ADDRESS_SIZE && root->username)
	return root;

    return lookup_session(root->children[*(ip + depth)], ip, depth + 1);
};

struct session_trie *add_session_node(struct session_trie *root, unsigned char *ip, char *username) {
    char len = 4;
    unsigned char index;

    for (char i = 0; i < len; ++i) {
	index = *(ip + i);

	if (!root->children[index])
	    root->children[index] = new_session_node_empty();

	if (i + 1 < len)
	    root = root->children[index];
    }

    root->children[index] = new_session_node(ip, username);
    root = root->children[index];

    return root;
};

void rm_session_node(struct user_trie *root, unsigned char *ip) {
    char len = 4;
    char index;

    for (char i = 0; i < len; ++i) {
	index = *(ip + i);

	if (!root->children[index])
	    return;

	root = root->children[index];
    }

    if (!root->username)
	return;

    root->username = NULL;
    free(root->username);
};

void session_trie_dump(struct session_trie *root, char *buffer, size_t *index) {
    if (!root)
	return;

    char *buf = buffer;
    buffer += SESSION_REGISTER_SIZE * (*index);

    // insert user
    if (root->username) {
	strdmps(buffer, root->ip, ADDRESS_SIZE);
	buffer += ADDRESS_SIZE;

	strdmps(buffer, root->username, strlen(root->username));
	buffer += USERNAME_SIZE;

	(*index)++;
    }

    for (unsigned char i = 0; i + 1 < SESSION_CHILDREN; ++i)
	if (root->children[i])
	    session_trie_dump(root->children[i], buf, index);
};

void print_session_nodes(struct user_trie *root) {
    if (!root)
	return;

    if (root->username)
	printf("S > %s\n", root->username);

    for (char i = 0; i < SESSION_CHILDREN; ++i)
	print_session_nodes(root->children[i]);
};

