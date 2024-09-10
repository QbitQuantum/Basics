/*
 * Now talk to the FD and do what he says
 */
void do_fd_commands(JCR *jcr)
{
   int i;
   bool found, quit;
   BSOCK *fd = jcr->file_bsock;

   fd->set_jcr(jcr);
   for (quit=false; !quit;) {
      int status;

      /* Read command coming from the File daemon */
      status = fd->recv();
      if (is_bnet_stop(fd)) {         /* hardeof or error */
         break;                       /* connection terminated */
      }
      if (status <= 0) {
         continue;                    /* ignore signals and zero length msgs */
      }
      Dmsg1(110, "<filed: %s", fd->msg);
      found = false;
      for (i=0; fd_cmds[i].cmd; i++) {
         if (bstrncmp(fd_cmds[i].cmd, fd->msg, strlen(fd_cmds[i].cmd))) {
            found = true;               /* indicate command found */
            jcr->errmsg[0] = 0;
            if (!fd_cmds[i].func(jcr)) {    /* do command */
               /* Note fd->msg command may be destroyed by comm activity */
               if (!job_canceled(jcr)) {
                  if (jcr->errmsg[0]) {
                     Jmsg1(jcr, M_FATAL, 0, _("Command error with FD, hanging up. %s\n"),
                           jcr->errmsg);
                  } else {
                     Jmsg0(jcr, M_FATAL, 0, _("Command error with FD, hanging up.\n"));
                  }
                  jcr->setJobStatus(JS_ErrorTerminated);
               }
               quit = true;
            }
            break;
         }
      }
      if (!found) {                   /* command not found */
         if (!job_canceled(jcr)) {
            Jmsg1(jcr, M_FATAL, 0, _("FD command not found: %s\n"), fd->msg);
            Dmsg1(110, "<filed: Command not found: %s\n", fd->msg);
         }
         fd->fsend(ferrmsg);
         break;
      }
   }
   fd->signal(BNET_TERMINATE);        /* signal to FD job is done */
}