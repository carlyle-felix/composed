#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/containers.h"

struct node {
    char *name;
    char *image;
    char *local;
    char *remote;
    char *path;
    struct node *next;
};

void *new_container(void);

void *new_container(void)
{
    List temp = malloc(sizeof(struct node));
    if (!temp) {
        printf("error: unable to allocate memory for container list.\n");
    }
    temp->name = NULL;
    temp->image = NULL;
    temp->next = NULL;
    temp->local = NULL;
    temp->remote = NULL;
    temp->path = NULL;

    return temp;
}

void free_list(List containers)
{
    List temp;
    
    while (containers) {
        temp = containers;
        containers = containers->next;

        free(temp->name);
        free(temp->image);
        free(temp->local);
        free(temp->remote);
        free(temp->path);
        free(temp);
    }
}

void *mem_alloc(int n)
{
    void *temp = malloc(n);
    if (!temp) {
        printf("error: unable to allocate memory.\n");
    }
    
    return temp;
}

List get_list(void)
{
    int i;
    char line[BUFFER], token[BUFFER/2];
    FILE *fp;
    List temp, containers = NULL;

    fp = popen("docker ps --format {{.Names}}\"\t\"{{.Image}}", "r");
    if (!fp) {
        printf("error: unable to get list of containers\n");
        return NULL;
    }

    while (fgets(line, BUFFER, fp)) {
        temp = new_container();

        strcpy(token, strtok(line, "\t"));
        temp->name = mem_alloc(strlen(token) + 1);
        if (!temp->name) {
            fclose(fp);
            free_list(containers);
            return NULL;
        }
        strcpy(temp->name, token);

        strcpy(token, strtok(NULL, "\n"));
        temp->image = mem_alloc(strlen(token) + 1);
        if (!temp->image) {
            fclose(fp);
            free_list(containers);
            return NULL;
        }
        strcpy(temp->image, token);

        temp->next = containers;
        containers = temp;
    }

    fclose(fp);
    return containers;
}

List get_yml_path(List containers) 
{
    char cmd[BUFFER], str[BUFFER], path[BUFFER];
    FILE *fp;
    int count, i, j;
    List temp;
    
    for (temp = containers; temp; temp = temp->next) {

        cmd[0] = '\0';
        snprintf(cmd, BUFFER, "docker inspect %s | grep -Po \'\"com.docker.compose.project.working_dir\": \\K.*\'", temp->name);
        
        fp = popen(cmd, "r");
        if (!fp) {
            printf("error: unable to get yml path.\n");
            return NULL;
        }
    
        fgets(str, BUFFER, fp);
        if (!str) {
            printf("error: failed to copy from pipe.\n");
            fclose(fp);
            return NULL;
        }
        fclose(fp);

        for (count = 0, i = 0, j = 0; *str && (count < 2); i++) {
            if (str[i] == '\"') {
                count++;
                continue;
            }
            path[j++] = str[i];
        }
        path[j] = '\0';
        
        temp->path = mem_alloc(strlen(path) + 1);
        if (!temp->path) {
            return NULL;
        }
        strcpy(temp->path, path);
    }

    return containers;
}

void print_list(List containers)
{
    List temp;
    int i;

    printf("    container\t\timage\n\n");
    for (i = 1, temp = containers; temp; temp = temp->next, i++) {
        printf("%-4d%-30s%s\n", i, temp->name, temp->image);
    }
}
