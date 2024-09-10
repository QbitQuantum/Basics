/* wait waits for a process started by fork_exec.
 * In general, this is called after the complete IO to the called process but
 * it isn't guaranteed. Never call if you don't expect a sudden death of the
 * subprocess.
 * Returns the exit status of the subprocess under normal circumstances. If
 * the subprocess has died by a signal, the return value is -signalnumber.
 */
static int Os2_wait(int process)
{
   int rc, retval, status;

#ifdef __WATCOMC__
   /*
    * Watcom is strange. EINTR isn't an indicator for a retry of the call.
    */
   status = -1;
   rc = cwait(&status, process, WAIT_CHILD);
   if (rc == -1)
   {
      if ((status != -1) && (errno == EINTR))
         retval = -status; /* Exception reason in lower byte */
      else
         retval = -errno;  /* I don't have a better idea */
   }
   else
   {
      if (status & 0xFF)
         retval = -status; /* Exception reason in lower byte */
      else
         retval = status >> 8;
   }
#else
   do {
      rc = waitpid(process, &status, 0);
   } while ((rc == -1) && (errno == EINTR));

   if (WIFEXITED(status))
   {
      retval = (int) WEXITSTATUS(status);
      if ( retval < 0 )
         retval = -retval;
   }
   else if (WIFSIGNALED(status))
   {
      retval = -WTERMSIG(status);
      if ( retval > 0 )
         retval = -retval;
      else if ( retval == 0 )
         retval = -1;
   }
   else
   {
      retval = -WSTOPSIG(status);
      if ( retval > 0 )
         retval = -retval;
      else if ( retval == 0 )
         retval = -1;
   }
#endif

   return(retval);
}