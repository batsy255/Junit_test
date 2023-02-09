#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

void run_command(char *command) {
    char *args[MAX_LINE/2 + 1]; /* command line arguments */

    int i = 0;
    args[i] = strtok(command, " ");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
    }

    if (strcmp(args[0], "quit") == 0) {
        exit(0);
    }

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        if (execvp(args[0], args) < 0) {
            fprintf(stderr, "Error: command not found\n");
            exit(1);
        }
    } else {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    char input[MAX_LINE];
    while (fgets(input, MAX_LINE, stdin) != NULL) {
        char *token = strtok(input, ";");
        while (token != NULL) {
            run_command(token);
            token = strtok(NULL, ";");
        }
        printf("SHELL$ ");
        fflush(stdout);
    }

    return 0;
}
