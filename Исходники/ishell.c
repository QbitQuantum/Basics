void cmd_exe(char **args){

  int pid;
  int status;

  if((pid = Fork()) == 0){
    Execvp(args[0], args);
  }

  else {
    wait(&status);
    if (status == 0){
      printf("[ishell: program terminated successfully]\n");
    }
  }
}