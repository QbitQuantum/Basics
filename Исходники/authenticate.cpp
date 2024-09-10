/*
 * Authenticate Storage daemon connection
 */
int authenticate_storage_daemon(JCR *jcr, MONITOR *monitor, STORE* store)
{
   BSOCK *sd = jcr->store_bsock;
   char dirname[MAX_NAME_LENGTH];
   int tls_local_need = BNET_TLS_NONE;
   int tls_remote_need = BNET_TLS_NONE;
   int compatible = true;

   /*
    * Send my name to the Storage daemon then do authentication
    */
   bstrncpy(dirname, monitor->hdr.name, sizeof(dirname));
   bash_spaces(dirname);
   /* Timeout Hello after 5 mins */
   btimer_t *tid = start_bsock_timer(sd, 60 * 5);
   if (!sd->fsend(SDFDhello, dirname)) {
      stop_bsock_timer(tid);
      Jmsg(jcr, M_FATAL, 0, _("Error sending Hello to Storage daemon. ERR=%s\n"), sd->bstrerror());
      return 0;
   }
   if (!cram_md5_respond(sd, store->password, &tls_remote_need, &compatible) ||
       !cram_md5_challenge(sd, store->password, tls_local_need, compatible)) {
      stop_bsock_timer(tid);
      Jmsg0(jcr, M_FATAL, 0, _("Director and Storage daemon passwords or names not the same.\n"
       "Please see " MANUAL_AUTH_URL " for help.\n"));
      return 0;
   }
   Dmsg1(116, ">stored: %s", sd->msg);
   if (sd->recv() <= 0) {
      stop_bsock_timer(tid);
      Jmsg1(jcr, M_FATAL, 0, _("bdird<stored: bad response to Hello command: ERR=%s\n"),
         sd->bstrerror());
      return 0;
   }
   Dmsg1(110, "<stored: %s", sd->msg);
   stop_bsock_timer(tid);
   if (strncmp(sd->msg, SDOKhello, sizeof(SDOKhello)) != 0) {
      Jmsg0(jcr, M_FATAL, 0, _("Storage daemon rejected Hello command\n"));
      return 0;
   }
   return 1;
}