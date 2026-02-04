#include <stdio.h>
#include <string.h>

#include "../include/containers.h"

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("no argument.\n");
        return 1;
    }

    if (!strcmp(argv[1], "list")) {
        List containers;

        containers = get_list();
        if (!containers) {
            free_list(containers);
            return 1;
        }
        print_list(containers);

        free_list(containers);
    } else if (!strcmp(argv[1], "update")) {
        List containers;

        containers = get_list();
        if (!containers) {
            free_list(containers);
            return 1;
        }
        containers = get_yml_path(containers);
        if (!containers) {
            free_list(containers);
            return 1;
        }
        compose_update(containers);

        if (!strcmp(argv[2], "--network")) {
            connect_network(containers, argv[3]);
        }

        free_list(containers);
    } else if (!strcmp(argv[1], "prune")) {
        prune();
    }

    return 0;
}