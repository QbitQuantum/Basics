int main(int argc, char *argv[])
{
  Pipe p;
  char host[25];
  gethostname(host, 25);
  char* home=malloc(100);
  int fdin;
  backupIO();

  home = strdup(getenv("HOME"));
  strcat(home, "/.ushrc");

  if((fdin=open(home, O_RDONLY))==-1)
    perror("OPEN USHRC"); 
  else
  {
    dup2(fdin, 0);
    close(fdin);
    printf("%s%% ", host);
    fflush(stdout);
    p = parse();
    currPipe = 0;
    prPipe(p);
    //freePipe(p);
  }

  
  


  while ( 1 ) {

    restoreIO();
    flushall();
    printf("%s%% ", host);
    fflush(stdout);
    p = parse();
    currPipe = 0;
    prPipe(p);
    //freePipe(p);

  }
}