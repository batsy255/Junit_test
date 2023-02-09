#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 512 /* The maximum length command */
#define MAX_ARGS 10 /* The maximum number of arguments */

void error_message(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int main(int argc, char *argv[])
{
    char input[MAX_LINE];
    char *args[MAX_ARGS];

    if (argc > 2) {
        error_message("Error: incorrect number of command line arguments");
    }

    FILE *fp;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            error_message("Error: batch file does not exist or cannot be opened");
        }
    }

    while (1) {
        int background = 0;
        int i;
        int should_run = 1;

        if (argc == 1) {
            printf("SHELL$ ");
            fflush(stdout);
            if (fgets(input, MAX_LINE, stdin) == NULL) {
                break;
            }
        } else {
            if (fgets(input, MAX_LINE, fp) == NULL) {
                break;
            }
        }

        int length = strlen(input);
        if (length > MAX_LINE) {
            error_message("Error: very long command line");
        } else if (length == 1) {
            continue;
        }

        // remove trailing newline character
        input[strcspn(input, "\n")] = 0;

        // check for '&' at the end of the line
        if (input[length - 1] == '&') {
            background = 1;
            input[length - 1] = 0;
        }

        // tokenize the input into arguments
        args[0] = strtok(input, " ");
        for (i = 1; i < MAX_ARGS; i++) {
            args[i] = strtok(NULL, " ");
            if (args[i] == NULL) {
                break;
            }
        }

        if (strcmp(args[0], "quit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid < 0) {
            error_message("Error: fork failed");
        } else if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                fprintf(stderr, "Error: command not found or cannot be executed\n");
                exit(1);
            }
        } else {
            if (!background) {
                wait(NULL);
            }
        }
    }

    return 0;
}
