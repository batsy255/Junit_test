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

        int i = 0;
        char *token = strtok(input, ";");
        while (token != NULL) {
            args[i] = strtok(token, " ");
            int j = 1;
            while (args[i] != NULL) {
                args[i + j] = strtok(NULL, " ");
                j++;
            }
            i = i + j;

            pid_t pid = fork();
            if (pid < 0) {
                printf("Fork failed\n");
                exit(1);
            } else if (pid == 0) {
                if (execvp(args[0], args) < 0) {
                    printf("Error: command not found\n");
                    exit(1);
                }
            }

            token = strtok(NULL, ";");
        }

        // Wait for all child processes to finish
        int status;
        pid_t pid;
        while ((pid = wait(&status)) > 0);
    }

    return 0;
}
