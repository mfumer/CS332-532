#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

void log_execution(const char *command, time_t start_time, time_t end_time) {
    FILE *log_file = fopen("output.log", "a");
    if (!log_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(log_file, "%s\t%s\t%s", command, ctime(&start_time), ctime(&end_time));
    fclose(log_file);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char command[256];
    while (fgets(command, sizeof(command), file)) {
        command[strcspn(command, "\n")] = 0;  
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            char *args[10];
            char *token = strtok(command, " ");
            int i = 0;
            while (token != NULL && i < 9) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Parent process
            time_t start_time = time(NULL);
            int status;
            wait(&status);
            time_t end_time = time(NULL);

            log_execution(command, start_time, end_time);

            if (WIFEXITED(status)) {
                printf("Child process exited with status = %d\n", WEXITSTATUS(status));
            } else {
                printf("Child process did not terminate normally!\n");
            }
        } else {
            perror("fork");
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}
