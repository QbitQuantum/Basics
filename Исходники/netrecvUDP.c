void err_exit(char *message)
 {
  perror(message);
  exit(1);
 }