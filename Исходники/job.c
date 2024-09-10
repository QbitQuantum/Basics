bool run_cmd(JCR *jcr)
{
   struct timeval tv;
   struct timezone tz;
   struct timespec timeout;
   int errstat = 0;
   BSOCK *cl;
   int fd_version = 0;
   int sd_version = 0;
   char job_name[500];
   int i;
   int stat;

   Dsm_check(200);
   Dmsg1(200, "Run_cmd: %s\n", jcr->dir_bsock->msg);

   /* If we do not need the FD, we are doing a virtual backup. */
   if (jcr->no_client_used()) {
      do_vbackup(jcr);
      return false;
   }

   jcr->sendJobStatus(JS_WaitFD);          /* wait for FD to connect */

   Dmsg2(050, "sd_calls_client=%d sd_client=%d\n", jcr->sd_calls_client, jcr->sd_client);
   if (jcr->sd_calls_client) {
      /* We connected to Client, so finish work */
      cl = jcr->file_bsock;
      if (!cl) {
         Jmsg0(jcr, M_FATAL, 0, _("Client socket not open. Could not connect to Client.\n"));
         Dmsg0(050, "Client socket not open. Could not connect to Client.\n");
         return false;
      }
      /* Get response to Hello command sent earlier */
      Dmsg0(050, "Read Hello command from Client\n");
      for (i=0; i<60; i++) {
         stat = cl->recv();
         if (stat <= 0) {
            bmicrosleep(1, 0);
         } else {
            break;
         }
      }
      if (stat <= 0) {
         berrno be;
         Jmsg1(jcr, M_FATAL, 0, _("Recv request to Client failed. ERR=%s\n"),
            be.bstrerror());
         Dmsg1(050, _("Recv request to Client failed. ERR=%s\n"), be.bstrerror());
         return false;
      }
      Dmsg1(050, "Got from FD: %s\n", cl->msg);
      if (sscanf(cl->msg, "Hello Bacula SD: Start Job %127s %d %d", job_name, &fd_version, &sd_version) != 3) {
         Jmsg1(jcr, M_FATAL, 0, _("Bad Hello from Client: %s.\n"), cl->msg);
         Dmsg1(050, _("Bad Hello from Client: %s.\n"), cl->msg);
         return false;
      }
      unbash_spaces(job_name);
      jcr->FDVersion = fd_version;
      jcr->SDVersion = sd_version;
      Dmsg1(050, "FDVersion=%d\n", fd_version);

      /*
       * Authenticate the File daemon
       */
      Dmsg0(050, "=== Authenticate FD\n");
      if (jcr->authenticated || !authenticate_filed(jcr)) {
         Dmsg1(050, "Authentication failed Job %s\n", jcr->Job);
         Jmsg(jcr, M_FATAL, 0, _("Unable to authenticate File daemon\n"));
      } else {
         jcr->authenticated = true;
      }
   } else if (!jcr->sd_client) {
      /* We wait to receive connection from Client */
      gettimeofday(&tv, &tz);
      timeout.tv_nsec = tv.tv_usec * 1000;
      timeout.tv_sec = tv.tv_sec + me->client_wait;

      Dmsg3(050, "%s waiting %d sec for FD to contact SD key=%s\n",
            jcr->Job, (int)(timeout.tv_sec-time(NULL)), jcr->sd_auth_key);

      Dmsg3(800, "=== Block Job=%s jid=%d %p\n", jcr->Job, jcr->JobId, jcr);

      /*
       * Wait for the File daemon to contact us to start the Job,
       *  when he does, we will be released, unless the 30 minutes
       *  expires.
       */
      P(mutex);
      while ( !jcr->authenticated && !job_canceled(jcr) ) {
         errstat = pthread_cond_timedwait(&jcr->job_start_wait, &mutex, &timeout);
         if (errstat == ETIMEDOUT || errstat == EINVAL || errstat == EPERM) {
            break;
         }
         Dmsg1(800, "=== Auth cond errstat=%d\n", errstat);
      }
      Dmsg4(050, "=== Auth=%d jid=%d canceled=%d errstat=%d\n",
         jcr->JobId, jcr->authenticated, job_canceled(jcr), errstat);
      V(mutex);
      Dmsg2(800, "Auth fail or cancel for jid=%d %p\n", jcr->JobId, jcr);
   }

   memset(jcr->sd_auth_key, 0, strlen(jcr->sd_auth_key));

   if (jcr->authenticated && !job_canceled(jcr)) {
      Dmsg2(800, "Running jid=%d %p\n", jcr->JobId, jcr);
      run_job(jcr);                   /* Run the job */
   }
   Dmsg2(800, "Done jid=%d %p\n", jcr->JobId, jcr);
   return false;
}