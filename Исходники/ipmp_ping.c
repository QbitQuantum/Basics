static int open_ipmp_sockets4()
{
  char      addr[128];
  struct    sockaddr_in *sin;

#if defined(__FreeBSD__)
  int    mib[]  = {CTL_NET, PF_INET, IPPROTO_IP, IPCTL_DEFTTL};
  u_int  miblen = 4;
  size_t len    = sizeof(ipv4_ttl);
#elif defined(__linux__)
  int    mib[]  = {CTL_NET, NET_IPV4, NET_IPV4_DEFAULT_TTL};
  u_int  miblen = 3;
  size_t len    = sizeof(ipv4_ttl);
#endif

  ipmp_sock = socket(AF_INET, SOCK_RAW, IPPROTO_IPMP);
  if(ipmp_sock == -1)
    {
      printerror(errno, strerror, "could not open IPMP IPv4 raw socket");
      return 0;
    }

  if((options & OPT_SRCADDR) && source->sa_family == AF_INET)
    {
      if(bind(ipmp_sock, source, sizeof(struct sockaddr_in)) == -1)
	{
	  sin = (struct sockaddr_in *)source;
	  inet_ntop(AF_INET, &sin->sin_addr, addr, sizeof(addr));

	  printerror(errno, strerror, "could not bind to %s", addr);
	  return 0;
	}
    }

#if defined(__NetBSD__)
  ipv4_ttl = 255;
#else
  if(sysctl(mib, miblen, &ipv4_ttl, &len, NULL, 0) == -1)
    {
      printerror(errno, strerror, "could not find out default ipv4 ttl");
      return 0;
    }
#endif

  return 1;
}