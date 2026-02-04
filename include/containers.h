#ifndef CONTAINERS_H
#define CONTAINERS_H

#define BUFFER 512

typedef struct node *List;

void free_list(List containers);
List get_list(void);
void print_list(List containers);
List get_yml_path(List containers);
int compose_update(List containers);
void connect_network(List containers, char *network);
void prune(void);

#endif