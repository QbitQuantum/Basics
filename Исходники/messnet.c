int connect_server(clientchan **sc,const char *addr,int port)
{
  unsigned int a;
  sock_size_t addrlength;
  mestyp b;
  int timeout;
  struct hostent *hpke;

  *sc = (clientchan *) malloc (sizeof (clientchan));
  if (!*sc) return -1;
  
  (*sc)->fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if ((*sc)->fd<0) {
   free((*sc));
   return -2;
  }

  a=1;
  if (ioctl ((*sc)->fd, FIONBIO, &a)) {
    close ((*sc)->fd);
    free((*sc));
    return -3;
  }

  hpke = gethostbyname ( addr );

  if ( hpke == NULL ) {
      return -4;
  }

  (*sc)->my_addr.sin_family      = AF_INET;
  (*sc)->my_addr.sin_port        = htons(0);
  (*sc)->my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  (*sc)->serv_addr.sin_family	 = AF_INET;
  (*sc)->serv_addr.sin_port	 = htons(port);
  (*sc)->serv_addr.sin_addr.s_addr = ((struct in_addr *)hpke->h_addr)->s_addr;

  addrlength = sizeof ((*sc)->my_addr);

  if (bind ((*sc)->fd, (struct sockaddr *)&((*sc)->my_addr), addrlength)) {
    close ((*sc)->fd);
    free((*sc));
    return -5;
  }

  // Set Vars
  (*sc)->qpos=0;
  (*sc)->buf=(char *) malloc(MAXBUF);
  (*sc)->bufpos=0;
  (*sc)->status=0;
  (*sc)->rest=0;
  (*sc)->aktion=0;

#ifdef PAS_RECV
  (*sc)->rcvmsg=NULL;
  (*sc)->rcvmsgs=NULL;
  (*sc)->rcvmsgd=NULL;
#endif

  // Validate Server...
  for (timeout=10;timeout>0;timeout--) {
        b=MESNEWCLIENT;
	if (sendto ( (*sc)->fd,&b ,sizeof(mestyp), 0, (struct sockaddr *) &((*sc)->serv_addr),
				sizeof(struct sockaddr_in) ) < 0) {
		close((*sc)->fd);
                free(*sc);
		return -6;
	}
  	/* Matze: Funktioniert nicht auf allen Rechnern... */
	#ifdef WITH_ALLEGRO
	rest(1000);
	#else
  	usleep(1000);
	#endif
      
	  addrlength=sizeof(struct sockaddr_in);
        if (recvfrom ( (*sc)->fd, (char *)&b, sizeof(mestyp), 0, (struct sockaddr *) &((*sc)->serv_addr),
            			&addrlength ) > 0) {
         if (b==MESACPTCLIENT) {
          debug_print ("Server response!\n");
          return 0;
         }
         if (b==MESDENYCLIENT) {
          debug_print ("Server denied acces!\n");
          close ((*sc)->fd);
          free (*sc);
          return -7;
         }
        }
  }

  close ((*sc)->fd);
  free (*sc);
  return -8;
}