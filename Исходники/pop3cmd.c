/*############################# pop3_quit() #############################*/
int
pop3_quit(void)
{
   int reply;

   if (pop3_fd != -1)
   {
      (void)command(pop3_fd, "QUIT");
      if (timeout_flag == OFF)
      {
         if ((reply = get_reply()) == INCORRECT)
         {
            (void)close(pop3_fd);
            return(INCORRECT);
         }

#ifdef _WITH_SHUTDOWN
         if (shutdown(pop3_fd, 1) < 0)
         {
            trans_log(DEBUG_SIGN, __FILE__, __LINE__, "pop3_quit", NULL,
                      _("shutdown() error : %s"), strerror(errno));
         }
         else
         {
            int    status;
            char   buffer[32];
            fd_set rset;

            /* Initialise descriptor set */
            FD_ZERO(&rset);
            FD_SET(pop3_fd, &rset);
            timeout.tv_usec = 0L;
            timeout.tv_sec = transfer_timeout;

            /* Wait for message x seconds and then continue. */
            status = select(pop3_fd + 1, &rset, NULL, NULL, &timeout);

            if (status > 0)
            {
               if (FD_ISSET(pop3_fd, &rset))
               {
                  if ((status = read(pop3_fd, buffer, 32)) < 0)
                  {
                     trans_log(ERROR_SIGN, __FILE__, __LINE__, "pop3_quit", NULL,
                               _("read() error (%d) : %s"),
                               status, strerror(errno));
                     reply = INCORRECT;
                  }
               }
            }
            else if (status == 0)
                 {
                    /* Timeout has arrived. */
                    timeout_flag = ON;
                    reply = INCORRECT;
                 }
                 else
                 {
                    trans_log(ERROR_SIGN, __FILE__, __LINE__, "pop3_quit", NULL,
                              _("select() error : %s"), strerror(errno));
                    reply = INCORRECT;
                 }
         }
#endif
      }
      else
      {
         reply = SUCCESS;
      }

#ifdef WITH_SSL
      if (ssl_con != NULL)
      {
         SSL_free(ssl_con);
         ssl_con = NULL;
      }
#endif
      if (close(pop3_fd) == -1)
      {
         trans_log(DEBUG_SIGN, __FILE__, __LINE__, "pop3_quit", NULL,
                   _("close() error : %s"), strerror(errno));
      }
      pop3_fd = -1;
   }
   else
   {
      reply = SUCCESS;
   }

   return(reply);
}