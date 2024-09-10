void
tcp_echo_recv(void)
{
   int   len;        /* length of recv data */
   int   e;          /* error holder */
   unsigned i;       /* generic index */
   int   count;      /* select return */
   fd_set fd_recv;   /* fd for recv */
   fd_set fd_accept; /* fd for accept */
   TCPCLIENT tmpclient = tcpq;
   struct sockaddr_in client;
   SOCKTYPE tmpsock; /* scratch socket */

   if (elisten_sock == INVALID_SOCKET && tcpq == NULL)
      return;  /* Echo not set up, don't bother */

#ifdef USE_FDS
   FD_ZERO(&fd_recv);
   FD_ZERO(&fd_accept);
#endif

   /* select on all open data sockets */
   i = 0;
   count = 0;
#ifdef USE_FDS
   while (tmpclient)
   {
      if (tmpclient->sock != INVALID_SOCKET)
      {
         FD_SET(tmpclient->sock, &fd_recv);
         i++;
      }
      tmpclient=tmpclient->next;
   }
#else
   while (tmpclient)
   {
      if (tmpclient->sock != INVALID_SOCKET)
         fd_recv.fd_array[i++] = tmpclient->sock ;
      tmpclient=tmpclient->next;
   }
#endif  /* USE_FDS */

#ifndef TCP_ZEROCOPY
   /* if we need to listen for server receives too */
#ifdef USE_FDS
   if (tcpecho_server && (esvr_sock != INVALID_SOCKET))
   {
      FD_SET(esvr_sock, &fd_recv);
   }
#else
   if (tcpecho_server)
   {
      if (esvr_sock != INVALID_SOCKET)
         fd_recv.fd_array[i++] = esvr_sock;
   }
#endif  /* USE_FDS */
#else
   /* if we need to close the server's active socket */
   if (esvr_sock_close != FALSE)
   {
      if (esvr_sock != INVALID_SOCKET)
      {
         socketclose(esvr_sock);
         esvr_sock = INVALID_SOCKET;
      }
      esvr_sock_close = FALSE;
   }
#endif   /* TCP_ZEROCOPY */

#ifndef USE_FDS
   fd_recv.fd_count = i;
#endif

   /* make this a short timeout since elisten may create soon */
   if (elisten_sock != INVALID_SOCKET)
   {
#ifdef USE_FDS
      FD_SET(elisten_sock, &fd_accept);
#else
      fd_accept.fd_array[0] = elisten_sock;
      fd_accept.fd_count = 1;
#endif  /* USE_FDS */
      count = t_select(&fd_recv, NULL, &fd_accept, 1);
   }
   else 
   {
      if (i)   /* if no fd_set sockets filled in, don't bother */
         count = t_select(&fd_recv, NULL, NULL, 1);
   }

   /* While the t_select() was executing, commands can be 
    * executed from cmd-prompt and sockets can be cleaned up. 
    * Check for that. 
    */
   if (elisten_sock == INVALID_SOCKET && tcpq == NULL)
      return;  /* Echo not set up, don't bother */

   for (i = 0; i < fd_recv.fd_count; i++)
   {
#ifdef USE_FDS
      tmpsock = FD_GET(i, &fd_recv);
      if (tmpsock == INVALID_SOCKET)
         continue;
#else
      tmpsock = fd_recv.fd_array[i];
#endif  /* USE_FDS */

      /* Find out the client connection corresponding to this socket */
      tmpclient = tcp_client_from_sock(tmpsock);

      /* try a receive. Pick buffer according to client or server */
      if (tmpclient)    /* found a client for this one */
         len = recv(tmpsock, tmpclient->inbuf, ECHOBUFSIZE, 0);
#ifndef TCP_ZEROCOPY
      else if (tmpsock == esvr_sock)
         len = recv(tmpsock, srv_inbuf, ECHOBUFSIZE, 0);
#endif   /* TCP_ZEROCOPY */
      else
      {
         continue;
      }

      if (len < 0)
      {
         e = t_errno(tmpsock);
         if (e != EWOULDBLOCK)
         {
            if (tmpsock != esvr_sock)
               ns_printf(tmpclient->pio,"TCP echo recv error %d\n", e);
            else
               ns_printf(NULL,"TCP echo recv error %d\n", e);
         }
      }
      else if (len == 0)
      {
         ns_printf(NULL,"TCPECHO:socket closed by other side\n");
         if (tmpsock == esvr_sock)
         {
            socketclose (tmpsock);
            esvr_sock = INVALID_SOCKET;
         }
         else
         {
            if (tmpclient == NULL)
            {
               dtrap();
            }          
            else
            {
               tmpclient->sock = INVALID_SOCKET ;
               tcp_client_del(tmpclient);
            }
         }
      }
      else  /* if (len > 0) - got some echo data */
      {
#ifndef TCP_ZEROCOPY
         if (tmpsock == esvr_sock)
         {
            /* we must be server, send echo reply */
            if (tcpecho_server)
            {
               e = send(esvr_sock, srv_inbuf, len, 0);
               if (e < 0)
               {
                  /* Print the error to console */
                  e = t_errno(esvr_sock);
                  ns_printf(NULL,
                   "TCP echo server, error %d sending reply\n", e);
               }
            }
         }
         else     /* not the server socket, must be client */
#endif   /* TCP_ZEROCOPY */
         {
            /* If not a bulk test, print info */
            if (tmpclient->len <= ECHOBUFSIZE)
            {
               ns_printf(tmpclient->pio,"TCP echo reply from:%s, len:%d, reply:%lu", 
                print_ipad(tmpclient->rhost), len, tmpclient->replies);
               ns_printf(tmpclient->pio,"\n%s",prompt);
            }
            else
            {
               u_long   dataval;
               u_long * rxbuf =  (u_long*)(tmpclient->inbuf);
               u_long * rxend =  (u_long*)(tmpclient->inbuf +  (len  &  ~3));

               dataval = tmpclient->tot_rcvd/4;

               /* adjust for odd sized previous receives */
               if (tmpclient->tot_rcvd & 3)
               {
                  MEMMOVE(rxbuf, tmpclient->inbuf + (len & 3), len);
                  rxend--;
                  dataval++;     /* ignore sliced word */
               }

               while (rxbuf < rxend)
               {
                  if (*rxbuf != dataval)
                  {
                     ns_printf(tmpclient->pio,
                      "tcp_echo data error; got %lu, expected %lu\n",
                      *rxbuf, dataval);
                  }
                  rxbuf++;
                  dataval++;
               }
            }
            tmpclient->replies++;
            tmpclient->tot_rcvd += len;
         }
      }
   }

   /* if no server listen to poll, return now */
   if (elisten_sock == INVALID_SOCKET)
      return;

#ifdef NOTDEF
   MEMSET(&client, 0, sizeof(client));
   client.sin_family = AF_INET;
   client.sin_addr.s_addr = INADDR_ANY;
   client.sin_port = htons(ECHO_PORT);
#endif

   /* check for received echo connection on server */
   len = sizeof(client);
   tmpsock = accept(elisten_sock, (struct sockaddr*)&client, &len);
   if (tmpsock != INVALID_SOCKET)
   {
      if (esvr_sock == INVALID_SOCKET)
      {
         esvr_sock = tmpsock;
#ifdef TCP_ZEROCOPY
         t_setsockopt(esvr_sock, SOL_SOCKET, SO_CALLBACK, (void*)echo_svr_upcall, 0);
#endif   /* TCP_ZEROCOPY */
      }
      else  /* we already have a connection */
      {
         dprintf("tcpecho: rejected extra connection\n");
         socketclose(tmpsock);   /* refuse to serve another */
      }
   }
}