int start3(char *arg)
{
    int pid;

   printf("start3(): started.  Calling Spawn for Child1\n");
   Spawn("Child1", Child1, NULL, USLOSS_MIN_STACK, 2, &pid);
   printf("start3(): after spawn of %d\n", pid);
   printf("start3(): Parent done. Calling Terminate.\n");
   Terminate(8);

   return 0;
} /* start3 */