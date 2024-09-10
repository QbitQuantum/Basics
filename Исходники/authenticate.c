/*
 * Authenticate File daemon connection
 */
int authenticate_file_daemon(JCR *jcr)
{
   BSOCK *fd = jcr->file_bsock;
   CLIENTRES *client = jcr->res.client;
   char dirname[MAX_NAME_LENGTH];
   int tls_local_need = BNET_TLS_NONE;
   int tls_remote_need = BNET_TLS_NONE;
   int compatible = true;
   bool auth_success = false;

   /*
    * Send my name to the File daemon then do authentication
    */
   bstrncpy(dirname, director->name(), sizeof(dirname));
   bash_spaces(dirname);
   /* Timeout Hello after 1 min */
   btimer_t *tid = start_bsock_timer(fd, AUTH_TIMEOUT);
   if (!fd->fsend(hello, dirname)) {
      stop_bsock_timer(tid);
      Jmsg(jcr, M_FATAL, 0, _("Error sending Hello to File daemon at \"%s:%d\". ERR=%s\n"),
           fd->host(), fd->port(), fd->bstrerror());
      return 0;
   }
   Dmsg1(dbglvl, "Sent: %s", fd->msg);

   /* TLS Requirement */
   if (client->tls_enable) {
     if (client->tls_require) {
        tls_local_need = BNET_TLS_REQUIRED;
     } else {
        tls_local_need = BNET_TLS_OK;
     }
   }

   if (client->tls_authenticate) {
      tls_local_need = BNET_TLS_REQUIRED;
   }

   auth_success = cram_md5_respond(fd, client->password, &tls_remote_need, &compatible);
   if (auth_success) {
      auth_success = cram_md5_challenge(fd, client->password, tls_local_need, compatible);
      if (!auth_success) {
         Dmsg1(dbglvl, "cram_auth failed for %s\n", fd->who());
      }
   } else {
      Dmsg1(dbglvl, "cram_get_auth failed for %s\n", fd->who());
   }
   if (!auth_success) {
      stop_bsock_timer(tid);
      Dmsg0(dbglvl, _("Director and File daemon passwords or names not the same.\n"));
      Jmsg(jcr, M_FATAL, 0,
            _("Unable to authenticate with File daemon at \"%s:%d\". Possible causes:\n"
            "Passwords or names not the same or\n"
            "Maximum Concurrent Jobs exceeded on the FD or\n"
            "FD networking messed up (restart daemon).\n"
            "Please see " MANUAL_AUTH_URL " for help.\n"),
            fd->host(), fd->port());
      return 0;
   }

   /* Verify that the remote host is willing to meet our TLS requirements */
   if (tls_remote_need < tls_local_need && tls_local_need != BNET_TLS_OK && tls_remote_need != BNET_TLS_OK) {
      stop_bsock_timer(tid);
      Jmsg(jcr, M_FATAL, 0, _("Authorization problem: FD \"%s:%s\" did not advertise required TLS support.\n"),
           fd->who(), fd->host());
      return 0;
   }

   /* Verify that we are willing to meet the remote host's requirements */
   if (tls_remote_need > tls_local_need && tls_local_need != BNET_TLS_OK && tls_remote_need != BNET_TLS_OK) {
      stop_bsock_timer(tid);
      Jmsg(jcr, M_FATAL, 0, _("Authorization problem: FD at \"%s:%d\" requires TLS.\n"),
           fd->host(), fd->port());
      return 0;
   }

   /* Is TLS Enabled? */
   if (tls_local_need >= BNET_TLS_OK && tls_remote_need >= BNET_TLS_OK) {
      /* Engage TLS! Full Speed Ahead! */
      if (!bnet_tls_client(client->tls_ctx, fd, client->tls_allowed_cns)) {
         stop_bsock_timer(tid);
         Jmsg(jcr, M_FATAL, 0, _("TLS negotiation failed with FD at \"%s:%d\".\n"),
              fd->host(), fd->port());
         return 0;
      }
      if (client->tls_authenticate) {        /* tls authentication only? */
         fd->free_tls();                     /* yes, shutdown tls */
      }
   }

   Dmsg1(116, ">filed: %s", fd->msg);
   if (fd->recv() <= 0) {
      stop_bsock_timer(tid);
      Dmsg1(dbglvl, _("Bad response from File daemon to Hello command: ERR=%s\n"),
         bnet_strerror(fd));
      Jmsg(jcr, M_FATAL, 0, _("Bad response from File daemon at \"%s:%d\" to Hello command: ERR=%s\n"),
         fd->host(), fd->port(), fd->bstrerror());
      return 0;
   }
   Dmsg1(110, "<filed: %s", fd->msg);
   stop_bsock_timer(tid);
   jcr->FDVersion = 0;
   if (!bstrncmp(fd->msg, FDOKhello, sizeof(FDOKhello)) &&
       sscanf(fd->msg, FDOKnewHello, &jcr->FDVersion) != 1) {
      Dmsg0(dbglvl, _("File daemon rejected Hello command\n"));
      Jmsg(jcr, M_FATAL, 0, _("File daemon at \"%s:%d\" rejected Hello command\n"),
           fd->host(), fd->port());
      return 0;
   }
   return 1;
}