void *ioc_alive_listen(void *data)
{
  aliveRecord *prec = (aliveRecord *) data;
  struct rpvtStruct *prpvt;

  SOCKET tcp_sockfd;
  int sflag;

  SOCKET client_sockfd;

  struct sockaddr_in l_addr;

  osiSocklen_t socklen;

  char *q;
  
  // key and value lengths, key length of zero means it doesn't exist
  int env_len[ENV_CNT][2]; 

  uint32_t msg32;
  uint16_t msg16, len16;
  uint8_t  len8;

  int length;
  int number;
  int type;

#if defined (vxWorks)
  BOOT_PARAMS bootparams;
#endif
#if defined (linux) || defined (darwin)
  char *user;
  char *group;
  char *hostname;
  char hostname_buffer[129];
#endif
#if defined (_WIN32)
  char *user;
  char user_buffer[80];
  char *machine;
  char machine_buffer[20];
#endif

  int i;

  prpvt = prec->rpvt;

#if defined (vxWorks)
  type = 1;
#elif defined (linux)
  type = 2;
#elif defined (darwin)
  type = 3;
#elif defined (_WIN32)
  type = 4;
#else
  type = 0;
#endif
  
#ifdef vxWorks
  bzero( (char *) &l_addr, sizeof( struct sockaddr_in) );
  l_addr.sin_len = sizeof( struct sockaddr_in);
#else
  memset( &l_addr, 0, sizeof( struct sockaddr_in) );
#endif
  l_addr.sin_family = AF_INET;
  l_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  l_addr.sin_port = htons(prpvt->orig_port);

  if( (tcp_sockfd = epicsSocketCreate(AF_INET, SOCK_STREAM, 0))
      == INVALID_SOCKET )
    {
      perror("socket");
      prec->ipsts = aliveIPSTS_INOPERABLE;
      monitor_field(prec, (void *) &prec->ipsts);
      return NULL;
    }

  sflag = 1;
  // not the end of the world if this option doesn't work
  setsockopt(tcp_sockfd, SOL_SOCKET, SO_REUSEADDR, (void *) &sflag,
             sizeof(sflag));


  if( bind(tcp_sockfd, (struct sockaddr *) &l_addr, 
           sizeof(struct sockaddr_in)) )
    {
      perror("TCP bind");
      prec->ipsts = aliveIPSTS_INOPERABLE;
      monitor_field(prec, (void *) &prec->ipsts);
      return NULL;
    }
  
  socklen = sizeof(struct sockaddr_in);
  if( getsockname( tcp_sockfd, (struct sockaddr *) &l_addr, &socklen) )
    {
      perror("TCP getsockname");
      prec->ipsts = aliveIPSTS_INOPERABLE;
      monitor_field(prec, (void *) &prec->ipsts);
      return NULL;
    }    
  // wait to use result until we know listen() works

  if( listen(tcp_sockfd, 5) )
    {
      perror("TCP listen");
      prec->ipsts = aliveIPSTS_INOPERABLE;
      monitor_field(prec, (void *) &prec->ipsts);
      return NULL;
    }

  prec->iport = ntohs(l_addr.sin_port);
  monitor_field(prec, (void *) &prec->iport);
  prec->ipsts = aliveIPSTS_OPERABLE;
  monitor_field(prec, (void *) &prec->ipsts);

  // request remote read
  prpvt->flags |= ((uint16_t) 1);
  
  while(1)
    {
      struct sockaddr r_addr;
      osiSocklen_t r_len = sizeof( r_addr);

      client_sockfd = epicsSocketAccept( tcp_sockfd, &r_addr, &r_len);
      if (client_sockfd == INVALID_SOCKET)
        continue;

      // fault flag can't happen, but just in case
      if( prec->isup || prpvt->fault_flag || !prpvt->ready_flag || 
          ( ((struct sockaddr_in *)&r_addr)->sin_addr.s_addr != prpvt->h_addr.sin_addr.s_addr) )
        {
          epicsSocketDestroy(client_sockfd);
          continue;
        }

      // TCP protocol version
      msg16 = htons(PROTOCOL_VERSION);
      send( client_sockfd, (void *) &msg16, sizeof(uint16_t), 0);

      // IOC type, currently 1 = vxworks, 2 = linux, 3 = darwin
      msg16 = htons(type);
      send( client_sockfd, (void *) &msg16, sizeof(uint16_t), 0);

      number = 0;
      length = 10;  // from version + type + number + length
#if defined (vxWorks)
      memset( &bootparams, 0, sizeof( BOOT_PARAMS) );
      bootStringToStruct( sysBootLine, &bootparams);
      // don't check to see if it returns EOS, as it's zeroed out

      length += 12; // bootparams.unitNum, bootparams.procNum, bootparams.flags
      length += 12; // 8-bit lengths below
      length += ((uint8_t) strlen(bootparams.bootDev) );
      length += ((uint8_t) strlen(bootparams.hostName) );
      length += ((uint8_t) strlen(bootparams.bootFile) );
      length += ((uint8_t) strlen(bootparams.ead) );
      length += ((uint8_t) strlen(bootparams.bad) );
      length += ((uint8_t) strlen(bootparams.had) );
      length += ((uint8_t) strlen(bootparams.gad) );
      length += ((uint8_t) strlen(bootparams.usr) );
      length += ((uint8_t) strlen(bootparams.passwd) );
      length += ((uint8_t) strlen(bootparams.targetName) );
      length += ((uint8_t) strlen(bootparams.startupScript) );
      length += ((uint8_t) strlen(bootparams.other) );
#endif
#if defined (linux) || defined (darwin)
      {
        uid_t user_id;
        gid_t group_id;
        struct passwd *passwd_entry;
        struct group *group_entry;

        user_id = getuid();
        passwd_entry = getpwuid(user_id);
        if( passwd_entry != NULL)
          user = passwd_entry->pw_name;
        else
          user = NULL;

        group_id = getgid();
        group_entry = getgrgid(group_id);
        if( group_entry != NULL)
          group = group_entry->gr_name;
        else
          group = NULL;

        if( gethostname( hostname_buffer, 128) )
          hostname = NULL;
        else
          {
            hostname_buffer[128] = '\0';
            hostname = hostname_buffer;
          }
      }

      //      flag == 2 or 3
      length += 1; // 8-bit string length
      if( user != NULL)
        length += ((uint8_t) strlen(user) );
      length += 1; // 8-bit string length
      if( group != NULL)
        length += ((uint8_t) strlen(group) );
      length += 1; // 8-bit string length
      if( hostname != NULL)
        length += ((uint8_t) strlen(hostname) );
#endif
#if defined (_WIN32)
      {
        uint32_t size;

        length += 2; // two variable lengths

        size = 80;
        if (GetUserNameA(user_buffer, &size))
          {
            user = user_buffer;
            length += ((uint8_t)strlen(user));
          }
        else
          user = NULL;

        size = 20;
        if (GetComputerNameA(machine_buffer, &size))
          {
            machine = machine_buffer;
            length += ((uint8_t)strlen(machine));
          }
        else
          machine = NULL;
      }
#endif
      for( i = 0; i < ENV_CNT; i++)
        {
          if( prpvt->env[i][0] == '\0')
            env_len[i][0] = 0;
          else
            {
              number++;
              length += 3; // 8-bit key & 16-bit value string lengths
              env_len[i][0] = strlen(prpvt->env[i]);
              length += env_len[i][0];
              q = getenv(prpvt->env[i]);
              if( q == NULL)
                env_len[i][1] = 0;
              else
                {
                  env_len[i][1] = strlen(q);
                  // if size is greater that 16-bit max, truncate to zero
                  if( env_len[i][1] > 65535)
                    env_len[i][1] = 0;
                  length += env_len[i][1];
                }
            }
        }

      /* printf("%d\n", length); fflush(stdout); */

      msg32 = htonl( length);
      send( client_sockfd, (void *) &msg32, sizeof(uint32_t), 0);
      msg16 = htons( number);
      send( client_sockfd, (void *) &msg16, sizeof(uint16_t), 0);

      for( i = 0; i < ENV_CNT; i++)
        {
          if( env_len[i][0] == 0)
            continue;

          len8 = env_len[i][0];
          send( client_sockfd, (void *) &len8, sizeof(uint8_t), 0);
          send( client_sockfd, prpvt->env[i], len8, 0);

          q = getenv(prpvt->env[i]);
          len16 = env_len[i][1];
          msg16 = htons( len16);
          send( client_sockfd, (void *) &msg16, sizeof(uint16_t), 0);
          if( len16)
            send( client_sockfd, q, len16, 0);
        }

#ifdef vxWorks
      bootparam_send( client_sockfd, bootparams.bootDev);
      msg32 = htonl(bootparams.unitNum);
      send( client_sockfd, (void *) &msg32, sizeof(uint32_t), 0);
      msg32 = htonl(bootparams.procNum);
      send( client_sockfd, (void *) &msg32, sizeof(uint32_t), 0);
      bootparam_send( client_sockfd, bootparams.hostName);
      bootparam_send( client_sockfd, bootparams.bootFile);
      bootparam_send( client_sockfd, bootparams.ead);
      bootparam_send( client_sockfd, bootparams.bad);
      bootparam_send( client_sockfd, bootparams.had);
      bootparam_send( client_sockfd, bootparams.gad);
      bootparam_send( client_sockfd, bootparams.usr);
      bootparam_send( client_sockfd, bootparams.passwd);
      msg32 = htonl( bootparams.flags);
      send( client_sockfd, (void *) &msg32, sizeof(uint32_t), 0);
      bootparam_send( client_sockfd, bootparams.targetName);
      bootparam_send( client_sockfd, bootparams.startupScript);
      bootparam_send( client_sockfd, bootparams.other);
#endif
#if defined (linux) || defined (darwin)
      if( user == NULL)
        len8 = 0;
      else
        len8 = strlen( user);
      send( client_sockfd, (void *) &len8, sizeof(uint8_t), 0);
      if( user != NULL)
        send( client_sockfd, user, len8, 0);

      if( group == NULL)
        len8 = 0;
      else
        len8 = strlen( group);
      send( client_sockfd, (void *) &len8, sizeof(uint8_t), 0);
      if( group != NULL)
        send( client_sockfd, group, len8, 0);

      if( hostname == NULL)
        len8 = 0;
      else
        len8 = strlen( hostname);
      send( client_sockfd, (void *) &len8, sizeof(uint8_t), 0);
      if( hostname != NULL)
        send( client_sockfd, hostname, len8, 0);
#endif
#if defined (_WIN32)
	  if (user == NULL)
		  len8 = 0;
	  else
		  len8 = strlen(user);
	  send(client_sockfd, (void *)&len8, sizeof(uint8_t), 0);
	  if (user != NULL)
		  send(client_sockfd, user, len8, 0);

	  if (machine == NULL)
		  len8 = 0;
	  else
		  len8 = strlen(machine);
	  send(client_sockfd, (void *)&len8, sizeof(uint8_t), 0);
	  if (machine != NULL)
		  send(client_sockfd, machine, len8, 0);
#endif
      epicsSocketDestroy( client_sockfd);

      // turn off request flag
      prpvt->flags &= ~((uint16_t) 1);
      // if itrigger was set, unset it
      if( prec->itrig)
        {
          prec->itrig = 0; 

          monitor_field(prec, (void *) &prec->itrig);
        }
    }

  return NULL;
}