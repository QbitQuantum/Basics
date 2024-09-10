/****** uti/stdio/sge_peclose() ***********************************************
*  NAME
*     sge_peclose() -- pclose() call which is suitable for sge_peopen()
*
*  SYNOPSIS
*     int sge_peclose(pid_t pid, FILE *fp_in, FILE *fp_out, 
*                     FILE *fp_err, struct timeval *timeout)
*
*  FUNCTION
*     ???
*
*  INPUTS
*     pid_t pid               - pid returned by peopen()
*     FILE *fp_in
*     FILE *fp_out
*     FILE *fp_err
*     struct timeval *timeout
*
*  RESULT
*     int - exit code of command or -1 in case of errors
*
*  SEE ALSO
*     uti/stdio/peopen()
*
*  NOTES
*     MT-NOTE: sge_peclose() is MT safe
******************************************************************************/
int sge_peclose(pid_t pid, FILE *fp_in, FILE *fp_out, FILE *fp_err,
                struct timeval *timeout)
{
   int i, status;
 
   DENTER(TOP_LAYER, "sge_peclose");
 
   if (fp_in != NULL) {
      FCLOSE(fp_in);
   }
   if (fp_out != NULL) {
      FCLOSE(fp_out);
   }
   if (fp_err != NULL) {
      FCLOSE(fp_err);
   }  

   do {
      i = waitpid(pid, &status, timeout?WNOHANG:0);
      if (i==-1) {
         DEXIT;
         return -1;
      }
      if (i==0) { /* not yet exited */
         if (timeout->tv_sec == 0) {
#ifdef WIN32 /* kill not called */
            /* CygWin has no kill command */
            DPRINTF(("killing not yet implemented\n"));
            timeout = NULL;
            /* kill(pid, SIGKILL); */
#else
            DPRINTF(("killing\n"));
            timeout = NULL;
            kill(pid, SIGKILL);
#endif /* WIN32 */
         } else {
            DPRINTF(("%d seconds waiting for exit\n", timeout->tv_sec));
            sleep(1);
            timeout->tv_sec -= 1;
         }
      }
   } while (i != pid);
 
   if (status & 0xff) {    /* terminated by signal */
      DEXIT;
      return -1;
   }
 
   DEXIT;
   return (status&0xff00) >> 8;  /* return exitcode */
FCLOSE_ERROR:
   return -1;
}