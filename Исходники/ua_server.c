/*
 * Handle Director User Agent commands
 */
static void *handle_UA_client_request(void *arg)
{
   int status;
   UAContext *ua;
   JCR *jcr;
   BSOCK *user = (BSOCK *)arg;

   pthread_detach(pthread_self());

   jcr = new_control_jcr("-Console-", JT_CONSOLE);

   ua = new_ua_context(jcr);
   ua->UA_sock = user;
   set_jcr_in_tsd(INVALID_JCR);

   user->recv();             /* Get first message */
   if (!authenticate_user_agent(ua)) {
      goto getout;
   }

   while (!ua->quit) {
      if (ua->api) {
         user->signal(BNET_MAIN_PROMPT);
      }

      status = user->recv();
      if (status >= 0) {
         pm_strcpy(ua->cmd, ua->UA_sock->msg);
         parse_ua_args(ua);

         if (ua->argc > 0 && ua->argk[0][0] == '.') {
            do_a_dot_command(ua);
         } else {
            do_a_command(ua);
         }

         dequeue_messages(ua->jcr);

         if (!ua->quit) {
            if (console_msg_pending && acl_access_ok(ua, Command_ACL, "messages")) {
               if (ua->auto_display_messages) {
                  pm_strcpy(ua->cmd, "messages");
                  qmessages_cmd(ua, ua->cmd);
                  ua->user_notified_msg_pending = false;
               } else if (!ua->gui && !ua->user_notified_msg_pending && console_msg_pending) {
                  if (ua->api) {
                     user->signal(BNET_MSGS_PENDING);
                  } else {
                     bsendmsg(ua, _("You have messages.\n"));
                  }
                  ua->user_notified_msg_pending = true;
               }
            }
            if (!ua->api) {
               user->signal(BNET_EOD); /* send end of command */
            }
         }
      } else if (is_bnet_stop(user)) {
         ua->quit = true;
      } else { /* signal */
         user->signal(BNET_POLL);
      }
   }

getout:
   close_db(ua);
   free_ua_context(ua);
   free_jcr(jcr);
   user->close();
   delete user;

   return NULL;
}