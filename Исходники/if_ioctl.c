/* Interface looking up using infamous SIOCGIFCONF. */
static int
interface_list_ioctl (void)
{
  int ret;
  int sock;
#define IFNUM_BASE 32
  int ifnum;
  struct ifreq *ifreq;
  struct ifconf ifconf;
  struct interface_FOO *ifp;
  int n;
  int lastlen;

  /* Normally SIOCGIFCONF works with AF_INET socket. */
  sock = socket (AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) 
    {
      zlog_warn ("Can't make AF_INET socket stream: %s", safe_strerror (errno));
      return -1;
    }

  /* Set initial ifreq count.  This will be double when SIOCGIFCONF
     fail.  Solaris has SIOCGIFNUM. */
#ifdef SIOCGIFNUM
  ret = ioctl (sock, SIOCGIFNUM, &ifnum);
  if (ret < 0)
    ifnum = IFNUM_BASE;
  else
    ifnum++;
#else
  ifnum = IFNUM_BASE;
#endif /* SIOCGIFNUM */

  ifconf.ifc_buf = NULL;

  lastlen = 0;
  /* Loop until SIOCGIFCONF success. */
  for (;;) 
    {
      ifconf.ifc_len = sizeof (struct ifreq) * ifnum;
      ifconf.ifc_buf = XREALLOC(MTYPE_TMP, ifconf.ifc_buf, ifconf.ifc_len);

      ret = ioctl(sock, SIOCGIFCONF, &ifconf);

      if (ret < 0) 
	{
	  zlog_warn ("SIOCGIFCONF: %s", safe_strerror(errno));
	  goto end;
	}
      /* Repeatedly get info til buffer fails to grow. */
      if (ifconf.ifc_len > lastlen)
	{
          lastlen = ifconf.ifc_len;
	  ifnum += 10;
	  continue;
	}
      /* Success. */
      break;
    }

  /* Allocate interface. */
  ifreq = ifconf.ifc_req;

#ifdef OPEN_BSD
  for (n = 0; n < ifconf.ifc_len; )
    {
      int size;

      ifreq = (struct ifreq *)((caddr_t) ifconf.ifc_req + n);
      ifp = if_get_by_name_len(ifreq->ifr_name,
			       strnlen(ifreq->ifr_name,
				       sizeof(ifreq->ifr_name)));
      if_add_update (ifp);
      size = ifreq->ifr_addr.sa_len;
      if (size < sizeof (ifreq->ifr_addr))
	size = sizeof (ifreq->ifr_addr);
      size += sizeof (ifreq->ifr_name);
      n += size;
    }
#else
  for (n = 0; n < ifconf.ifc_len; n += sizeof(struct ifreq))
    {
      ifp = if_get_by_name_len(ifreq->ifr_name,
			       strnlen(ifreq->ifr_name,
				       sizeof(ifreq->ifr_name)));
      if_add_update (ifp);
      ifreq++;
    }
#endif /* OPEN_BSD */

 end:
  close (sock);
  XFREE (MTYPE_TMP, ifconf.ifc_buf);

  return ret;
}