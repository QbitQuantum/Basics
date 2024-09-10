void *socks_connector_sel(void *p)
{
   fd_set rset, wset;
   int maxfd = 0, len, so_err;
   SocksQueue_t *squeue, sq;
   time_t t;
   struct timeval tv;
   socklen_t err_len;

   for (;;)
   {
      if (term_req())
         return NULL;

      FD_ZERO(&rset);
      FD_ZERO(&wset);
      MFD_SET(CNF(socksfd[0]), &rset, maxfd);
      t = time(NULL);

      for (squeue = socks_queue_; squeue; squeue = squeue->next)
      {
         switch (squeue->state)
         {
            case SOCKS_NEW:
               /*if (!squeue->fd)
               {
                  log_msg(LOG_CRIT, "SOCKS_NEW and fd = %d, but should be 0", squeue->fd);
                  squeue->state = SOCKS_DELETE;
                  continue;
               }*/

               if (t < squeue->restart_time)
               {
                  log_debug("SOCKS request is scheduled for connection not before %ds", squeue->restart_time - t);
                  continue;
               }

               // check and increase retry counter
               squeue->retry++;
               if (!squeue->perm && (squeue->retry > SOCKS_MAX_RETRY))
               {
                  log_msg(LOG_NOTICE, "temporary request failed %d times and will be removed", squeue->retry - 1);
                  squeue->state = SOCKS_DELETE;
                  continue;
               }

               log_debug("creating socket for unconnected SOCKS request");
               if ((squeue->fd = socket(CNF(socks_dst)->sin_family == AF_INET ? PF_INET : PF_INET6, SOCK_STREAM, 0)) == -1)
               {
                  log_msg(LOG_ERR, "cannot create socket for new SOCKS request: \"%s\"", strerror(errno));
                  continue;
               }

               set_nonblock(squeue->fd);
               log_debug("queueing fd %d for connect", squeue->fd);
               squeue->connect_time = t;
               if (socks_tcp_connect(squeue->fd, (struct sockaddr*) CNF(socks_dst), SOCKADDR_SIZE(CNF(socks_dst))) == -1)
               {
                  socks_reschedule(squeue);
                  continue;
               }

               squeue->state = SOCKS_CONNECTING;
               MFD_SET(squeue->fd, &wset, maxfd);

               break;

            case SOCKS_4AREQ_SENT:
               MFD_SET(squeue->fd, &rset, maxfd);
               break;
         }
      }

      // select all file descriptors
      set_select_timeout(&tv);
      log_debug("selecting (maxfd = %d)", maxfd);
      if ((maxfd = select(maxfd + 1, &rset, &wset, NULL, &tv)) == -1)
      {
         log_msg(LOG_EMERG, "select encountered error: \"%s\", restarting", strerror(errno));
         continue;
      }
      log_debug("select returned %d", maxfd);

      // check socks request pipe
      if (FD_ISSET(CNF(socksfd[0]), &rset))
      {
         maxfd--;
         if ((len = read(CNF(socksfd[0]), &sq, sizeof(sq))) == -1)
            log_msg(LOG_ERR, "failed to read from SOCKS request pipe, fd = %d: \"%s\"", 
                  CNF(socksfd[0]), strerror(errno));
         if (len < sizeof(sq))
            log_msg(LOG_ERR, "read from SOCKS request pipe truncated to %d of %d bytes, ignoring.", 
                  len, sizeof(sq));
         else
         {
            log_debug("received %d bytes on SOCKS request pipe fd %d", len, CNF(socksfd[0]));
            if (sq.next)
            {
               log_debug("output of SOCKS request queue triggered");
               socks_output_queue((FILE*) sq.next);
            }
            else if (IN6_IS_ADDR_UNSPECIFIED(&sq.addr))
            {
               log_debug("termination request on SOCKS request queue received");
            }
            else
            {
               log_debug("SOCKS queuing request received");
               socks_enqueue(&sq);
            }
         }
      }

      // handle all other file descriptors
      t = time(NULL);
      for (squeue = socks_queue_; maxfd && squeue; squeue = squeue->next)
      {
         // check write set, this is valid after connect()
         if (FD_ISSET(squeue->fd, &wset))
         {
            maxfd--;
            if (squeue->state == SOCKS_CONNECTING)
            {
               // test if connect() worked
               log_debug("check socket error");
               err_len = sizeof(so_err);
               if (getsockopt(squeue->fd, SOL_SOCKET, SO_ERROR, &so_err, &err_len) == -1)
               {
                  log_msg(LOG_ERR, "getsockopt failed: \"%s\", rescheduling request", strerror(errno));
                  socks_reschedule(squeue);
                  continue;
               }
               if (so_err)
               {
                  log_msg(LOG_ERR, "getsockopt returned %d (\"%s\")", so_err, strerror(so_err));
                  socks_reschedule(squeue);
                  continue;
               }
               // everything seems to be ok, now check request status
               if (socks_send_request(squeue) == -1)
               {
                  log_msg(LOG_ERR, "SOCKS request failed");
                  socks_reschedule(squeue);
                  continue;
               }
               // request successfully sent, advance state machine
               squeue->state = SOCKS_4AREQ_SENT;
            }
            else
               log_debug("unknown state %d in write set", squeue->state);
         }

         // check read set, this is valid after write, i.e. receiving SOCKS response
         if (FD_ISSET(squeue->fd, &rset))
         {
            maxfd--;
            if (squeue->state == SOCKS_4AREQ_SENT)
            {
               if (socks_rec_response(squeue) == -1)
               {
                  socks_reschedule(squeue);
                  continue;
               }
               // success
               log_debug("activating peer fd %d", squeue->fd);
               socks_activate_peer(squeue);
               squeue->state = SOCKS_DELETE;
            }
            else
               log_debug("unknown state %d in read set", squeue->state);
         }
      }

      // delete requests from queue which are marked for deletion
      for (squeue = socks_queue_; squeue; squeue = squeue->next)
         if (squeue->state == SOCKS_DELETE)
         {
            socks_unqueue(squeue);
            // restart loop
            squeue = socks_queue_;
            if (!squeue)
            {
               log_debug("last entry deleted, breaking loop");
               break;
            }
         }
   }
}