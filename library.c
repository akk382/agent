#include "library.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string char*

void execute_cmd(string, string);

int send_job(string jobname, string command) {
    if (command != NULL || command == "") {
        perror("Command not provided.\n");
        return -1;
    }

    // Search for the executable in the path.
    const string o_path = getenv("PATH");
    const string path = strdup(o_path);

    execute_cmd(command, path);
}

void execute_cmd(string command, string path) {
    string dup_cmd = strdup(command);
    string cmd_name = strtok(dup_cmd, " ");
    string path_x;
    do {
        path_x = strtok(path, NULL);
        if (path_x != NULL) {
            string full_path = malloc(100);
            strcat(full_path, path_x);
            strcat(full_path, cmd_name);
            free(full_path);
        }
    } while (path_x != NULL);
}
