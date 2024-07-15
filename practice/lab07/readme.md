Readme
Opening a file
  FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }
    https://www.reddit.com/r/C_Programming/comments/9zcinw/fopen_question/

to read contents of individual lines of the file
    while (fgets(command, sizeof(command), file)) 
    https://stackoverflow.com/questions/38976582/reading-text-file-until-eof-using-fgets-in-c

Use fork-exec to create a new process that executes the program specified in the input file along with the arguments provided
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
            exit(EXIT_FAILURE)
    https://stackoverflow.com/questions/39882573/if-pid-fork-0-why-is-fork-returning-pid-1-systemd

time indicator to indicate start and end time
      time_t start_time = time(NULL);
            int status;
            wait(&status);
            time_t end_time = time(NULL);
    https://en.cppreference.com/w/cpp/chrono/c/time_t

