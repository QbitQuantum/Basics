/* Make ospf6d's server socket. */
int
ospf6_serv_sock (uint64_t host_num)
{
  struct in6_addr * sv_addr;
  char  s_addr[INET6_ADDRSTRLEN+1];
  int status;
  
  if (ospf6d_privs.change (ZPRIVS_RAISE))
    zlog_err ("ospf6_serv_sock: could not raise privs");

  sv_addr = get_sv_addr(); 

  inet_ntop(AF_INET6, sv_addr, s_addr, INET6_ADDRSTRLEN+1);
  printf("done getting sv addr: %s\n", s_addr);

  // Set up socket address info
  struct addrinfo hints, *addr;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET6;     // IPv6
  hints.ai_socktype = SOCK_STREAM;  // TCP
  char port_str[8];
  sprintf(port_str, "%u", SV_SISIS_PORT);
  if((status = getaddrinfo(s_addr, port_str, &hints, &addr)) != 0)
  {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  ospf6_sock = socket (addr->ai_family, addr->ai_socktype, addr->ai_protocol);
  printf("creating socket %d\n", ospf6_sock);
  if (ospf6_sock < 0)
    {
      zlog_warn ("Network: can't create OSPF6 socket.");
      if (ospf6d_privs.change (ZPRIVS_LOWER))
        zlog_err ("ospf_sock_init: could not lower privs");
      return -1;
    }

  if (connect(ospf6_sock, addr->ai_addr, addr->ai_addrlen) == -1)
  {
    close(ospf6_sock);
    perror("connect");
  }

  if (ospf6d_privs.change (ZPRIVS_LOWER))
      zlog_err ("ospf_sock_init: could not lower privs");

  sleep(1);  // wait for all other processes to register

  /* set socket options */
//#if 1
//  sockopt_reuseaddr (ospf6_sock);
//#else
//  ospf6_set_reuseaddr ();
//#endif /*1*/
//  ospf6_reset_mcastloop ();
//  ospf6_set_pktinfo ();
//  ospf6_set_checksum ();

  /* setup global in6_addr, allspf6 and alldr6 for later use */
  inet_pton (AF_INET6, ALLSPFROUTERS6, &allspfrouters6);
  inet_pton (AF_INET6, ALLDROUTERS6, &alldrouters6);

  return 0;
}