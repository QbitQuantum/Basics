/***********************************************************************
 *
 get_dns_info: Get the search list or the domain name
	       and the dns server addresses in Network Byte Order
	       Set statp->os_query if DnsQuery is available.

***********************************************************************/
void get_dns_info(res_state statp)
{
#if MAX_HOSTNAME_LEN > MAXHOSTNAMELEN
#define MAX_HOSTNAME_SIZE (MAX_HOSTNAME_LEN + 1)
#else
#define MAX_HOSTNAME_SIZE (MAXHOSTNAMELEN + 1)
#endif
#if MAX_HOSTNAME_SIZE > 256 /* sizeof(defdname) */
#error stap->defdname too short
#endif

  int res, debug = statp->options & RES_DEBUG;

  ULONG ulOutBufLen = 0;
  DWORD dwRetVal;
  IP_ADDR_STRING * pIPAddr;
  FIXED_INFO * pFixedInfo;
  int numAddresses = 0;

  if (statp->use_os
      && ((dwRetVal = DnsQuery_A(NULL, 0, 0, NULL, NULL, NULL)) != ERROR_PROC_NOT_FOUND))
  {
    DPRINTF(debug, "using dnsapi.dll %d\n", dwRetVal);
    statp->os_query = (typeof(statp->os_query)) cygwin_query;
    /* We just need the search list. Avoid loading iphlpapi. */
    statp->nscount = -1;
  }

  if (statp->nscount != 0)
    goto use_registry;

  /* First call to get the buffer length we need */
  dwRetVal = GetNetworkParams((FIXED_INFO *) 0, &ulOutBufLen);
  if (dwRetVal != ERROR_BUFFER_OVERFLOW) {
    DPRINTF(debug, "GetNetworkParams: error %lu (Windows)\n", dwRetVal);
    goto use_registry;
  }
  if ((pFixedInfo = (FIXED_INFO *) alloca(ulOutBufLen)) == 0) {
    DPRINTF(debug, "alloca: %s\n", strerror(errno));
    goto use_registry;
  }
  if ((dwRetVal = GetNetworkParams(pFixedInfo, & ulOutBufLen))) {
    DPRINTF(debug, "GetNetworkParams: error %lu (Windows)\n", dwRetVal);
    goto use_registry;
  }

  DPRINTF(debug, "GetNetworkParams: OK\n");
  /* Record server addresses, up to array size */
  for (pIPAddr = &(pFixedInfo->DnsServerList), numAddresses = 0;
       pIPAddr;
       pIPAddr = pIPAddr->Next) {
    if (numAddresses < DIM(statp->nsaddr_list)) {
	DPRINTF(debug, "server \"%s\"\n", pIPAddr->IpAddress.String);
      statp->nsaddr_list[numAddresses].sin_addr.s_addr = cygwin_inet_addr(pIPAddr->IpAddress.String);
      if (statp->nsaddr_list[numAddresses].sin_addr.s_addr != 0) {
	numAddresses++;
	statp->nscount++;
      }
    }
    else
      DPRINTF(debug, "no space for server \"%s\"\n", pIPAddr->IpAddress.String);
  }

 use_registry:
  get_registry_dns(statp);

  if (!statp->dnsrch[0]) {
    statp->defdname[sizeof(statp->defdname) - 1] = 0;
    if (!(res = getdomainname(statp->defdname, sizeof(statp->defdname)))) {
      if (statp->defdname[0] && !statp->defdname[sizeof(statp->defdname) - 1])
	statp->dnsrch[0] = statp->defdname;
    }
    DPRINTF(debug, "getdomainname \"%s\"\n",
	    (res)? strerror(errno) : statp->defdname);
  }
}