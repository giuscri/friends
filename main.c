// Crino' Giuseppe, 794281, 21 Gennaio 2016
//
// Build via `cc -m32 -std=c11 -g -O0 main.c -o main`

# define _GNU_SOURCE
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <assert.h>

struct node_int32 {
    int32_t data;
    struct node_int32 * next;
};

struct queue_int32 {
    struct node_int32 * head;
    struct node_int32 * tail;
    size_t len;
};

// Create a new queue_int32 in memory,
// return a reference to it.
struct queue_int32 *
new_queue_int32 () {
    return calloc(1, sizeof(struct queue_int32));
}

// Append a new int32_t at the end
// of the queue passed as a parameter.
// Return the updated queue of int32_t's.
struct queue_int32 *
append_queue_int32 (struct queue_int32 * q, int32_t data) {
    struct node_int32 * nd = calloc(1, sizeof(struct node_int32));
    nd->data = data;
    if (q->len == 0) {
        q->head = q->tail = nd;
    }
    else {
        q->tail->next = nd;
        q->tail = nd;
    }
    q->len += 1;
    return q;
}

// Pop the element at position 0
// from the queue of int32_t's.
// Update the queue, return
// the integer popped.
int32_t
pop0_queue_int32 (struct queue_int32 * q) {
    assert(q->len > 0);
    int32_t ret = q->head->data;
    struct node_int32 * next = q->head->next;
    free(q->head);
    q->head = next;
    q->len -= 1;
    return ret;
}

// Print the queue of int32_t's.
void
print_queue_int32 (struct queue_int32 * q) {
    struct node_int32 * p = q->head;
    printf("[ ");
    for (; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }
    puts("]");
}

// Free memory for a no longer-used
// queue of int32_t's.
void
del_queue_int32 (struct queue_int32 * q) {
    if (q->len > 0) {
        do {
            pop0_queue_int32(q);
        } while (q->len > 0);
    }
    assert(q->len == 0);
    free(q);
}

struct node_queue_int32 {
    struct queue_int32 * q;
    struct node_queue_int32 * next;
};

struct queue_queues_int32 {
    struct node_queue_int32 * head;
    struct node_queue_int32 * tail;
    size_t len;
};

// Return a queue of queues of int32_t's.
struct queue_queues_int32 *
new_queue_queues_int32 () {
    return calloc(1, sizeof(struct queue_queues_int32));
}

// Append a queue at the end
// of the queue of queues `qq`
// passed as a parameter.
// Return the updated version of `qq``.
struct queue_queues_int32 *
append_queue_queues_int32 (struct queue_queues_int32 * qq, struct queue_int32 * q) {
    struct node_queue_int32 * nd = calloc(1, sizeof(struct node_queue_int32));
    nd->q = q;
    if (qq->len == 0) {
        qq->head = qq->tail = nd;
    }
    else {
        qq->tail->next = nd;
        qq->tail = nd;
    }
    qq->len += 1;
    return qq;
}

// Free memory for a no longer-used
// queue of queues of int32_t's.
void
del_queue_queues_int32 (struct queue_queues_int32 * qq) {
    if (qq->len == 0) { return; }
    struct node_queue_int32 * p = NULL;
    struct node_queue_int32 * q = NULL;
    for (p = qq->head->next, q = qq->head; p != NULL; /* See below */) {
        del_queue_int32(q->q);
        free(q);
        qq->len -= 1;
        q = p;
        p = p->next;
    }
    del_queue_int32(q->q);
    free(q);
    qq->len -= 1;
    assert(qq->len == 0);
    free(qq);
}

// Print the queue of queues passed as a parameter.
void
print_queue_queues_int32 (struct queue_queues_int32 * qq) {
    struct node_queue_int32 * p = qq->head;
    puts("[");
    for (; p != NULL; p = p->next) {
        printf("\t");
        print_queue_int32(p->q);
    }
    puts("]");
}

struct node_friendship {
    int32_t year_of_start;
    int32_t id;
    struct node_friendship * next;
};

// Create a new node_friendships
// with id and year_of_start taken
// from the parameter list.
// Return the new node.
struct node_friendship *
new_node_friendship (size_t id, int32_t year_of_start) {
    struct node_friendship * nd = calloc(1, sizeof(struct node_friendship));
    nd->year_of_start = year_of_start;
    nd->id = id;
    return nd;
}

struct linkedlist_friendship {
    struct node_friendship * head;
    size_t len;
};

// Create a new linkedlist
// of node_friendship's,
// and return it.
struct linkedlist_friendship *
new_linkedlist_friendship () {
    return calloc(1, sizeof(struct linkedlist_friendship));
}

// Create a new node_relationship
// with year_of_start and id specified
// as a parameter, prepend it to
// the linkedlist passed as a parameter,
// then return the updated version of
// the linkedlist `lst`.
struct linkedlist_friendship *
prepend_linkedlist_friendship (struct linkedlist_friendship * lst, \
                                    int32_t year_of_start, size_t id)
{
    struct node_friendship * nd = calloc(1, sizeof(struct node_friendship));
    nd->year_of_start = year_of_start;
    nd->id = id;
    nd->next = lst->head;
    lst->head = nd;
    lst->len += 1;
    return lst;
}

bool
in_linkedlist_friendship (struct linkedlist_friendship * lst, int32_t x) {
    for (struct node_friendship * it = lst->head; it != NULL; it = it->next) {
        if (it->id == x) {
            return true;
        }
    }
    return false;
}

// Free memory for a no longer-used linkedlist.
void
del_linkedlist_friendship (struct linkedlist_friendship * lst) {
    if (lst->len == 0) { return; }
    struct node_friendship * p = NULL;
    struct node_friendship * q = NULL;
    for (p = lst->head->next, q = lst->head; p != NULL; /* See below */) {
        free(q);
        lst->len -= 1;
        q = p;
        p = p->next;
    }
    free(q);
    lst->len -= 1;
    assert(lst->len == 0);
    free(lst);
}

struct user {
    int32_t id;
    char * first_name;
    char * last_name;
    struct linkedlist_friendship * friendships;
    bool _flag;
};

// Create a new user, with id, first_name, last_name
// specified by the argument list.
// Return the `struct user` just allocated.
struct user *
new_user (size_t id, char * first_name, char * last_name) {
    struct user * u = calloc(1, sizeof(struct user));
    u->id = id;
    u->first_name = strndup(first_name, 32);
    u->last_name = strndup(last_name, 32);
    u->friendships = new_linkedlist_friendship();
    u->_flag = false;
    return u;
}

// Pretty print the user specified as parameter.
void
print_user (struct user * u) {
    printf("%s, %s (%d)\n", u->last_name, u->first_name, u->id);
}

// Free memory for a no longer-used user.
void
del_user (struct user * u) {
    free(u->first_name);
    free(u->last_name);
    del_linkedlist_friendship(u->friendships);
    //free(u->friendships);
    free(u);
}

struct graph {
    struct user ** users;
    size_t nusers;
};

// Create a new graph and return it.
struct graph *
new_graph (size_t nusers) {
    struct graph * g = calloc(1, sizeof(struct graph));
    g->nusers = nusers;
    g->users = calloc(nusers, sizeof(struct user *));
    return g;
}

// Free memory for the graph.
void
del_graph (struct graph * G) {
    for (size_t i = 0; i < G->nusers; ++i) {
        if (G->users[i] == NULL) { continue; }
        del_user(G->users[i]);
    }
    free(G->users);
    free(G);
}

// Explore the graph specified as a parameter,
// using breadth-first search, and return
// the list of user's id sorted by the order
// in which they were explored.
struct queue_int32 *
bfs (struct graph * G, int32_t id, bool (*cb) (int32_t x)) {
    assert(G->users[id] != NULL);
    struct queue_int32 * q = new_queue_int32();
    append_queue_int32(q, id);
    struct queue_int32 * visited = new_queue_int32();
    append_queue_int32(visited, id);

    G->users[id]->_flag = true;
    while (q->len > 0) {
        int32_t ppd = pop0_queue_int32(q);
        struct node_friendship * ad = G->users[ppd]->friendships->head;
        for (; ad != NULL; ad = ad->next) {
            if (G->users[ad->id]->_flag) {
                continue;
            }
            if (cb && !cb(ad->year_of_start)) {
                continue;
            }
            append_queue_int32(visited, ad->id);
            G->users[ad->id]->_flag = true;
            append_queue_int32(q, ad->id);
        }
    }

    del_queue_int32(q);
    return visited;
}

// Return a list of queues, where each queue
// represents a connected component of
// the graph G specified as a parameter.
// Take a callback `cb` that can be NULL too
// applied to the data cointed in every
// vertex of the graph -- in our very
// specific implementation, only int32_t.
struct queue_queues_int32 *
connected_components (struct graph * G, bool (*cb) (int32_t x)) {
    // Reset to `false` all the nodes
    for (size_t i = 0; i < G->nusers; ++i) {
        if (G->users[i] == NULL) { continue; }
        G->users[i]->_flag = false;
    }

    struct queue_queues_int32 * ret = new_queue_queues_int32();
    for (size_t i = 0; i < G->nusers; ++i) {
        if (G->users[i] == NULL) {
            continue;
        }
        if (G->users[i]->_flag) {
            continue;
        }
        append_queue_queues_int32(ret, bfs(G, i, cb));
    }
    return ret;
}

// Run some instructions to test
// the various data structures implemented.
void
run_tests () {
    // Testing queue_int32
    struct queue_int32 * q = new_queue_int32();
    assert(q->len == 0);
    assert(q->head == 0);
    assert(q->tail == 0);
    for (size_t i = 0; i < 100; ++i) {
        append_queue_int32(q, i);
    }
    for (size_t i = 0; i < 50; ++i) {
        int32_t ppd = pop0_queue_int32(q);
        assert(ppd == i);
    }
    del_queue_int32(q);

    // Testing queue_queues_int32
    struct queue_int32 * qs[100] = { 0 };
    for (size_t i = 0; i < 100; ++i) {
        qs[i] = new_queue_int32();
    }
    for (size_t i = 0; i < 100; ++i) {
        for (size_t j = 0; j < 100; ++j) {
            append_queue_int32(qs[i], j);
        }
        assert(qs[i]->len == 100);
    }
    struct queue_queues_int32 * qq = new_queue_queues_int32();
    for (size_t i = 0; i < 100; ++i) {
        append_queue_queues_int32(qq, qs[i]);
    }
    assert(qq->len == 100);

    for (struct node_queue_int32 * it = qq->head; it != NULL; it = it->next) {
        assert(it->q->len == 100);
    }

    del_queue_queues_int32(qq);

    // Testing user
    struct user ** us = calloc(100, sizeof(struct user *));
    for (size_t i = 0; i < 100; ++i) {
        us[i] = new_user(i, "David", "Bowie");
    }
    for (size_t i = 0; i < 100; ++i) {
        assert(strcmp(us[i]->first_name, "David") == 0);
        assert(strcmp(us[i]->last_name, "Bowie") == 0);
    }
    for (size_t i = 0; i < 100; ++i) {
        del_user(us[i]);
    }
    free(us);

    // Testing linkedlist_friendship
    struct linkedlist_friendship * lfs = new_linkedlist_friendship();
    for (size_t i = 0; i < 100; ++i) {
        prepend_linkedlist_friendship(lfs, 1916 + i, i);
    }
    size_t ix = 0;
    for (struct node_friendship * it = lfs->head; it != NULL; it = it->next) {
        assert(it->year_of_start == 1916 + 99 - ix);
        assert(it->id == 99 - ix);
        ix += 1;
    }
    assert(lfs->len == 100);
    del_linkedlist_friendship(lfs);
}

int
main (int argc, char ** argv) {
    run_tests();

    if (argc < 2) {
        puts("Usage: main <max users allowed>");
        return -1;
    }

    size_t at_most = atoi(argv[1]);
    struct graph * G = new_graph(at_most);

    char * cmd = calloc(32, sizeof(char));
    size_t len_cmd = 32;
    while (getline(&cmd, &len_cmd, stdin) > 0) {
        // Ignore comment
        if (strncmp(cmd, "#", 1) == 0) {
            continue;
        }
        // add <first_name> <last_name> <id>
        else if (strncmp(cmd, "add", strlen("add")) == 0) {
            char * first_name = calloc(32, sizeof(char));
            char * last_name = calloc(32, sizeof(char));
            int32_t id = 0;
            sscanf(cmd, " %*s %s %s %d", first_name, last_name, &id);
            if (G->users[id] != NULL) {
                printf("#%d already exists.\n", id);
                continue;
            }
            G->users[id] = new_user(id, first_name, last_name);
            free(last_name);
            free(first_name);
        }
        // find <id>
        else if (strncmp(cmd, "find", strlen("find")) == 0) {
            int32_t id = 0;
            sscanf(cmd, " %*s %d", &id);
            if (G->users[id] == NULL) {
                printf("#%d does not exist yet.\n", id);
                continue;
            }
            print_user(G->users[id]);
        }
        // mfriends <id0> <id1>
        else if (strncmp(cmd, "mfriends", strlen("mfriends")) == 0) {
            int32_t i = 0;
            int32_t j = 0;
            int32_t year_of_start = 0;
            sscanf(cmd, " %*s %d %d %d", &i, &j, &year_of_start);
            if (G->users[i] == NULL) {
                printf("#%d does not exist yet.\n", i);
                continue;
            }
            if (G->users[j] == NULL) {
                printf("#%d does not exist yet.\n", j);
                continue;
            }
            if (G->users[i]->friendships == NULL) {
                G->users[i]->friendships = new_linkedlist_friendship();
            }
            if (G->users[j]->friendships == NULL) {
                G->users[j]->friendships = new_linkedlist_friendship();
            }
            int32_t other_ix = 0;
            struct linkedlist_friendship * shyest_friendships = 0;
            if (G->users[i]->friendships->len < G->users[j]->friendships->len) {
                shyest_friendships = G->users[i]->friendships;
                other_ix = j;
            }
            else {
                shyest_friendships = G->users[j]->friendships;
                other_ix = i;
            }
            if (in_linkedlist_friendship(shyest_friendships, other_ix)) {
                printf("#%d and #%d are already friends.\n", i, j);
                continue;
            }
            prepend_linkedlist_friendship(G->users[i]->friendships, \
                                             year_of_start, j);
            prepend_linkedlist_friendship(G->users[j]->friendships, \
                                             year_of_start, i);
        }
        // extract_groups [since <year>]
        else if (strncmp(cmd, "extract_groups", strlen("extract_groups")) == 0) {
            struct queue_queues_int32 * qq = 0;
            int32_t year_of_start = 0;
            if (sscanf(cmd, "%*s %*s %d", &year_of_start) > 0) {
                bool cb (int32_t x) {
                    return x >= year_of_start;
                }
                qq = connected_components(G, cb);
            }
            else {
               qq = connected_components(G, NULL);
            }
            size_t group_ix = 0;
            for (struct node_queue_int32 * it = qq->head; it != NULL; it = it->next) {
                printf("\nGroup #%d:\n", group_ix);
                for (struct node_int32 * _it = it->q->head; _it != NULL; _it = _it->next) {
                    printf("\t");
                    print_user(G->users[_it->data]);
                }
                group_ix += 1;
            }
            del_queue_queues_int32(qq);
        }
    }
    free(cmd);
    del_graph(G);
    return 0;
}
