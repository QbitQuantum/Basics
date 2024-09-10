int
main(int argc, char *argv[])
{
  HANDLE thread;
  DWORD thread_id;
  CONTEXT context;

  context.ContextFlags=CONTEXT_CONTROL;

  z=0;
  thread=CreateThread(NULL,
                      0x1000,
                      (LPTHREAD_START_ROUTINE)thread_1,
                      NULL,
                      0,
                      &thread_id);

  if(!thread)
  {
    printf("Error: could not create thread ...\n");
    ExitProcess(0);
  }

  Sleep(1000);

  SuspendThread(thread);

  for(;;)
  {
    printf("%lx ", z);
    Sleep(100);x++;
    if(x>100 && GetThreadContext(thread, &context))
    {
#if defined(_M_IX86)
      printf("EIP: %lx\n", context.Eip);
#elif defined(_M_AMD64)
      printf("RIP: %p\n", context.Rip);
#endif
      printf("Calling resumethread ... \n");
      ResumeThread(thread);
    }
  }

  ExitProcess(0);
  return(0);
}