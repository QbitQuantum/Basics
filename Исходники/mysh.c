void execute(char **argv){
  execvp(argv[0], argv);
  perror(SHELL_ERROR_IDENTIFIER);
  exit(EXIT_FAILURE);
}