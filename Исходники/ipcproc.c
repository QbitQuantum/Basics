/*
  PROGRAM: fibo_task

  This program will repeatedly receive synchronously a positive value k and compute 
  the k-th fibonacci number. Each computed fibonacci number is sent to the "printer"
  message queue. It exits if it receives k==-1
*/
int fibo_task(int argl, void* args)
{
  unsigned int k,f;
  long msg;
  char *prbuf = malloc(1024);
  Pid_t pid;

  sprintf(prbuf,"Hello from fibo_task process %d.\n",GetPid());
  print_string(prbuf);

  while(1) {
    // Wait for a request to compute a Fibonacci number.
    pid = ReceivePort(&msg, 1);
    assert(pid == GetPPid());
    if(msg<0) {
      sprintf(prbuf, "fibo_task exiting (pid = %d). Bye!\n", GetPid());
      print_string(prbuf);
      free(prbuf);
      Exit(0);			/* Test Exit! */
    }

    k = msg;
    sprintf(prbuf,"I will compute the %d-th Fibonacci number\n",k);
    print_string(prbuf);
    f = fibo(k);
    sprintf(prbuf,"The %d-th Fibonacci number is %d.\n",k,f);
    print_string(prbuf);
  }
  return 0;
}