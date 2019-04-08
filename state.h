#include "structs/node_d.c"

#define u_short unsigned short

struct state_users {
    u_short n_users;
    u_short f_available;
    struct node_d *db_holes;
};

struct state {
    struct state_users *users;
};

struct state g_state = { u_state };

