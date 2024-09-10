int xioparsenetwork_ip4(const char *rangename, struct xiorange *range) {
   struct hostent *maskaddr;
   struct in_addr *netaddr_in = &range->netaddr.ip4.sin_addr;
   struct in_addr *netmask_in = &range->netmask.ip4.sin_addr;
   char *rangename1;	/* a copy of rangename with writing allowed */
   char *delimpos;	/* absolute address of delimiter */
   int bits;

   if ((rangename1 = strdup(rangename)) == NULL) {
      Error1("strdup(\"%s\"): out of memory", rangename);
      return STAT_RETRYLATER;
   }

   if (delimpos = strchr(rangename1, '/')) {
      bits = strtoul(delimpos+1, NULL, 10);
      netmask_in->s_addr = htonl((0xffffffff << (32-bits)));
   } else if (delimpos = strchr(rangename1, ':')) {
      if ((maskaddr = Gethostbyname(delimpos+1)) == NULL) {
	 /* note: cast is req on AIX: */
	 Error2("gethostbyname(\"%s\"): %s", delimpos+1,
		h_errno == NETDB_INTERNAL ? strerror(errno) :
		(char *)hstrerror(h_errno));
	 return STAT_NORETRY;
      }
      netmask_in->s_addr = *(uint32_t *)maskaddr->h_addr_list[0];
   } else {
      Error1("xioparsenetwork_ip4(\"%s\",,): missing netmask delimiter", rangename);
      free(rangename1);
      return STAT_NORETRY;
   }
   {
      struct hostent *nameaddr;
      *delimpos = 0;
      if ((nameaddr = Gethostbyname(rangename1)) == NULL) {
	 /* note: cast is req on AIX: */
	 Error2("gethostbyname(\"%s\"): %s", rangename1,
		h_errno == NETDB_INTERNAL ? strerror(errno) :
		(char *)hstrerror(h_errno));
	    free(rangename1);
	 return STAT_NORETRY;
      }
      netaddr_in->s_addr = *(unsigned long *)nameaddr->h_addr_list[0];
   }
   free(rangename1);
   return STAT_OK;
}