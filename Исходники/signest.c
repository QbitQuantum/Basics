static int interfere_main(int argc, char *argv[])
{
  /* Now just loop staying in the way as much as possible */

  printf("interfere_main: Waiting on semaphore\n" );
  FFLUSH();

  g_interferer_running = true;
  while (!g_done)
    {
      (void)sem_wait(&g_interferer_sem);
    }

  /* Just exit, the system should clean up the signal handlers */

  g_interferer_running = false;
  return EXIT_SUCCESS;
}