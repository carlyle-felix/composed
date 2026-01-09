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
        // get list of containers
        containers = get_list();
        if (!containers) {
            return 1;
        }

        // get path of yml
        containers = get_yml_path(containers);
        if (!containers) {
            return 1;
        }

        print_list(containers);
        free_list(containers);
    }
    
    // check which containers arent up-to-date
    // print list of containers with current and update version
    // update containers

}