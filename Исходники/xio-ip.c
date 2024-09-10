/* the ultimate(?) socat resolver function
 node: the address to be resolved; supported forms:
   1.2.3.4 (IPv4 address)
   [::2]   (IPv6 address)
   hostname (hostname resolving to IPv4 or IPv6 address)
   hostname.domain (fq hostname resolving to IPv4 or IPv6 address)
 service: the port specification; may be numeric or symbolic
 family: PF_INET, PF_INET6, or PF_UNSPEC permitting both
 socktype: SOCK_STREAM, SOCK_DGRAM
 protocol: IPPROTO_UDP, IPPROTO_TCP
 sau: an uninitialized storage for the resulting socket address
 returns: STAT_OK, STAT_RETRYLATER
*/
int xiogetaddrinfo(const char *node, const char *service,
		   int family, int socktype, int protocol,
		   union sockaddr_union *sau, socklen_t *socklen,
		   unsigned long res_opts0, unsigned long res_opts1) {
   int port = -1;	/* port number in network byte order */
   char *numnode = NULL;
   size_t nodelen;
   unsigned long save_res_opts = 0;
#if HAVE_GETADDRINFO
   struct addrinfo hints = {0};
   struct addrinfo *res = NULL;
#else /* HAVE_GETIPNODEBYNAME || nothing */
   struct hostent *host;
#endif
   int error_num;

#if HAVE_RESOLV_H
   if (res_opts0 | res_opts1) {
      if (!(_res.options & RES_INIT)) {
         Res_init();	/*!!! returns -1 on error */
      }
      save_res_opts = _res.options;
      _res.options &= ~res_opts0;
      _res.options |= res_opts1;
      Debug2("changed _res.options from 0x%lx to 0x%lx",
	     save_res_opts, _res.options);
   }
#endif /* HAVE_RESOLV_H */
   memset(sau, 0, *socklen);
   sau->soa.sa_family = family;

   /* if service is numeric we don't want to have a lookup (might take long
      with NIS), so we handle this specially */
   if (service && isdigit(service[0]&0xff)) {
      char *extra;
      port = htons(strtoul(service, &extra, 0));
      if (*extra != '\0') {
	 Warn2("xiogetaddrinfo(, \"%s\", ...): extra trailing data \"%s\"",
	       service, extra);
      }
      service = NULL; 
   }

   /* the resolver functions might handle numeric forms of node names by
      reverse lookup, that's not what we want.
      So we detect these and handle them specially */
   if (node && isdigit(node[0]&0xff)) {
#if HAVE_GETADDRINFO
      hints.ai_flags |= AI_NUMERICHOST;
#endif /* HAVE_GETADDRINFO */
      if (family == PF_UNSPEC) {
	 family = PF_INET;
#if HAVE_GETADDRINFO
      } else if (family == PF_INET6) {
	 /* map "explicitely" into IPv6 address space; getipnodebyname() does
	    this with AI_V4MAPPED, but not getaddrinfo() */
	 if ((numnode = Malloc(strlen(node)+7+1)) == NULL) {
#if HAVE_RESOLV_H
	    if (res_opts0 | res_opts1) {
	       _res.options = (_res.options & (~res_opts0&~res_opts1) |
			       save_res_opts& ( res_opts0| res_opts1));
	    }
#endif
	    return STAT_NORETRY;
	 }
	 sprintf(numnode, "::ffff:%s", node);
	 node = numnode;
	 hints.ai_flags |= AI_NUMERICHOST;
#endif /* HAVE_GETADDRINFO */
      }
#if WITH_IP6
   } else if (node && node[0] == '[' && node[(nodelen=strlen(node))-1]==']') {
      if ((numnode = Malloc(nodelen-1)) == NULL) {
#if HAVE_RESOLV_H
	 if (res_opts0 | res_opts1) {
	    _res.options = (_res.options & (~res_opts0&~res_opts1) |
			    save_res_opts& ( res_opts0| res_opts1));
	 }
#endif
	 return STAT_NORETRY;
      }
      strncpy(numnode, node+1, nodelen-2);
      numnode[nodelen-2] = '\0';
      node = numnode;
#if HAVE_GETADDRINFO
      hints.ai_flags |= AI_NUMERICHOST;
#endif /* HAVE_GETADDRINFO */
      if (family == PF_UNSPEC)  family = PF_INET6;
#endif /* WITH_IP6 */
   }

#if HAVE_GETADDRINFO
   if (node != NULL || service != NULL) {
      struct addrinfo *record;

      if (socktype != SOCK_STREAM && socktype != SOCK_DGRAM) {
	 /* actual socket type value is not supported - fallback to a good one */
	 socktype = SOCK_DGRAM;
      }
      if (protocol != IPPROTO_TCP && protocol != IPPROTO_UDP) {
	 /* actual protocol value is not supported - fallback to a good one */
	 if (socktype == SOCK_DGRAM) {
	    protocol = IPPROTO_UDP;
	 } else {
	    protocol = IPPROTO_TCP;
	 }
      }
      hints.ai_flags |= AI_PASSIVE;
      hints.ai_family = family;
      hints.ai_socktype = socktype;
      hints.ai_protocol = protocol;
      hints.ai_addrlen = 0;
      hints.ai_addr = NULL;
      hints.ai_canonname = NULL;
      hints.ai_next = NULL;

      if ((error_num = Getaddrinfo(node, service, &hints, &res)) != 0) {
	 Error7("getaddrinfo(\"%s\", \"%s\", {%d,%d,%d,%d}, {}): %s",
		node, service, hints.ai_flags, hints.ai_family,
		hints.ai_socktype, hints.ai_protocol,
		(error_num == EAI_SYSTEM)?
		strerror(errno):gai_strerror(error_num));
	 if (res != NULL)  freeaddrinfo(res);
	 if (numnode)  free(numnode);

#if HAVE_RESOLV_H
	 if (res_opts0 | res_opts1) {
	    _res.options = (_res.options & (~res_opts0&~res_opts1) |
			    save_res_opts& ( res_opts0| res_opts1));
	 }
#endif
	 return STAT_RETRYLATER;
      }
      service = NULL;	/* do not resolve later again */

      record = res;
      if (family == PF_UNSPEC && xioopts.preferred_ip == '0') {
	 /* we just take the first result */
	 family = res[0].ai_addr->sa_family;
      }
      if (family == PF_UNSPEC) {
	 int trypf;
	 trypf = (xioopts.preferred_ip=='6'?PF_INET6:PF_INET);
	 /* we must look for a matching entry */
	 while (record != NULL) {
	    if (record->ai_family == trypf) {
	       family = trypf;
	       break;	/* family and record set accordingly */
	    }
	    record = record->ai_next;
	 }
	 if (record == NULL) {
	    /* we did not find a "preferred" entry, take the first */
	    record = res;
	    family = res[0].ai_addr->sa_family;
	 }
      }

      switch (family) {
#if WITH_IP4
      case PF_INET:
	 if (*socklen > record->ai_addrlen) {
	    *socklen = record->ai_addrlen;
	 }
	 memcpy(&sau->ip4, record->ai_addr, *socklen);
	 break;
#endif /* WITH_IP4 */
#if WITH_IP6
      case PF_INET6:
#if _AIX
	 /* older AIX versions pass wrong length, so we correct it */
	 record->ai_addr->sa_len = sizeof(struct sockaddr_in6);
#endif
	 if (*socklen > record->ai_addrlen) {
	    *socklen = record->ai_addrlen;
	 }
	 memcpy(&sau->ip6, record->ai_addr, *socklen);
	 break;
#endif /* WITH_IP6 */
      default:
	 Error1("address resolved to unknown protocol family %d",
		record->ai_addr->sa_family);
	 break;
      }
      freeaddrinfo(res);
   } else {
      switch (family) {
#if WITH_IP4
      case PF_INET:  *socklen = sizeof(sau->ip4); break;
#endif /* WITH_IP4 */
#if WITH_IP6
      case PF_INET6: *socklen = sizeof(sau->ip6); break;
#endif /* WITH_IP6 */
      }
   }

#elif HAVE_GETIPNODEBYNAME /* !HAVE_GETADDRINFO */

   if (node != NULL) {
      /* first fallback is getipnodebyname() */
      if (family == PF_UNSPEC) {
#if WITH_IP4 && WITH_IP6
	 family = xioopts.default_ip=='6'?PF_INET6:PF_INET;
#elif WITH_IP6
	 family = PF_INET6;
#else
	 family = PF_INET;
#endif
      }
      host = Getipnodebyname(node, family, AI_V4MAPPED, &error_num);
      if (host == NULL) {
	 const static char ai_host_not_found[] = "Host not found";
	 const static char ai_no_address[]     = "No address";
	 const static char ai_no_recovery[]    = "No recovery";
	 const static char ai_try_again[]      = "Try again";
	 const char *error_msg = "Unknown error";
	 switch (error_num) {
	 case HOST_NOT_FOUND: error_msg = ai_host_not_found; break;
	 case NO_ADDRESS:     error_msg = ai_no_address;
	 case NO_RECOVERY:    error_msg = ai_no_recovery;
	 case TRY_AGAIN:      error_msg = ai_try_again;
	 }
	 Error2("getipnodebyname(\"%s\", ...): %s", node, error_msg);
      } else {
	 switch (family) {
#if WITH_IP4
	 case PF_INET:
	    *socklen = sizeof(sau->ip4);
	    sau->soa.sa_family = PF_INET;
	    memcpy(&sau->ip4.sin_addr, host->h_addr_list[0], 4);
	    break;
#endif
#if WITH_IP6
	 case PF_INET6:
	    *socklen = sizeof(sau->ip6);
	    sau->soa.sa_family = PF_INET6;
	    memcpy(&sau->ip6.sin6_addr, host->h_addr_list[0], 16);
	    break;
#endif
	 }
      }
      freehostent(host);
   }

#else /* !HAVE_GETIPNODEBYNAME */

   if (node != NULL) {
      /* this is not a typical IP6 resolver function - but Linux
	 "man gethostbyname" says that the only supported address type with
	 this function is AF_INET _at present_, so maybe this fallback will
	 be useful somewhere sometimesin a future even for IP6 */
      if (family == PF_UNSPEC) {
#if WITH_IP4 && WITH_IP6
	 family = xioopts.default_ip=='6'?PF_INET6:PF_INET;
#elif WITH_IP6
	 family = PF_INET6;
#else
	 family = PF_INET;
#endif
      }
      /*!!! try gethostbyname2 for IP6 */
      if ((host = Gethostbyname(node)) == NULL) {
	 Error2("gethostbyname(\"%s\"): %s", node,
		h_errno == NETDB_INTERNAL ? strerror(errno) :
		hstrerror(h_errno));
#if HAVE_RESOLV_H
	 if (res_opts0 | res_opts1) {
	    _res.options = (_res.options & (~res_opts0&~res_opts1) |
			    save_res_opts& ( res_opts0| res_opts1));
	 }
#endif
	 return STAT_RETRYLATER;
      }
      if (host->h_addrtype != family) {
	 Error2("xioaddrinfo(): \"%s\" does not resolve to %s",
		node, family==PF_INET?"IP4":"IP6");
      } else {
	 switch (family) {
#if WITH_IP4
	 case PF_INET:
	    *socklen = sizeof(sau->ip4);
	    sau->soa.sa_family = PF_INET;
	    memcpy(&sau->ip4.sin_addr, host->h_addr_list[0], 4);
	    break;
#endif /* WITH_IP4 */
#if WITH_IP6
	 case PF_INET6:
	    *socklen = sizeof(sau->ip6);
	    sau->soa.sa_family = PF_INET6;
	    memcpy(&sau->ip6.sin6_addr, host->h_addr_list[0], 16);
	    break;
#endif /* WITH_IP6 */
	 }
      }
   }

#endif

#if WITH_TCP || WITH_UDP
   if (service) {
      port = parseport(service, protocol);
   }
   if (port >= 0) {
      switch (family) {
#if WITH_IP4
      case PF_INET:  sau->ip4.sin_port  = port; break;
#endif /* WITH_IP4 */
#if WITH_IP6
      case PF_INET6: sau->ip6.sin6_port = port; break;
#endif /* WITH_IP6 */
      }
   }      
#endif /* WITH_TCP || WITH_UDP */

   if (numnode)  free(numnode);

#if HAVE_RESOLV_H
   if (res_opts0 | res_opts1) {
      _res.options = (_res.options & (~res_opts0&~res_opts1) |
		      save_res_opts& ( res_opts0| res_opts1));
   }
#endif /* HAVE_RESOLV_H */
   return STAT_OK;
}