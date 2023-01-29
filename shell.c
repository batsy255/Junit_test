#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

int main(int argc, char *argv[])
{
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */

    while (should_run) {
        printf("osh> ");
        fflush(stdout);

        char input[MAX_LINE];
        fgets(input, MAX_LINE, stdin);
        input[strcspn(input, "\n")] = 0; // remove newline character

        int background = 0;
        if (input[strlen(input) - 1] == '&') {
            background = 1;
            input[strlen(input) - 1] = 0; // remove '&'
        }

        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if (strcmp(args[0], "exit") == 0) {
            should_run = 0;
        } else {
            pid_t pid = fork();
            if (pid < 0) {
                printf("Fork failed\n");
                exit(1);
            } else if (pid == 0) {
                if (execvp(args[0], args) < 0) {
                    printf("Error: command not found\n");
                    exit(1);
                }
            } else {
                if (!background) {
                    wait(NULL);
                }
            }
        }
    }

    return 0;
}
