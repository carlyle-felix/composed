#include <stdio.h>
#include <string.h>

#include "../include/containers.h"

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("no argument.\n");
        return 1;
    }

    List containers;

    if (!strcmp(argv[1], "list")) {
        containers = get_list();
        if (!containers) {
            return 1;
        }
        print_list(containers);

    } else if (!strcmp(argv[1], "update")) {
        containers = get_list();
        if (!containers) {
            return 1;
        }
        containers = get_yml_path(containers);
        if (!containers) {
            return 1;
        }
        compose_update(containers);

        if (!strcmp(argv[2], "--network")) {
            connect_network(containers, argv[3]);
        }
    }
    
    free_list(containers);

    return 0;
}