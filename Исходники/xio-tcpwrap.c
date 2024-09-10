/* returns -1 if forbidden, 0 if no tcpwrap check, or 1 if explicitely allowed
   */
int xio_tcpwrap_check(xiosingle_t *xfd, union sockaddr_union *us,
		      union sockaddr_union *them) {
   char *save_hosts_allow_table, *save_hosts_deny_table;
   struct request_info ri;
#if WITH_IP6
   char clientaddr[INET6_ADDRSTRLEN] = "", serveraddr[INET6_ADDRSTRLEN] = "";
#else
   char clientaddr[INET_ADDRSTRLEN] = "", serveraddr[INET_ADDRSTRLEN] = "";
#endif
   int allow;

   if (!xfd->para.socket.ip.dolibwrap) {
      return 0;
   }
   if (us == NULL || them == NULL)  { return -1; }

#if defined(HAVE_HOSTS_ALLOW_TABLE)
   save_hosts_allow_table = hosts_allow_table;
   if (xfd->para.socket.ip.hosts_allow_table) {
      Debug1("hosts_allow_table = \"%s\"",
	     xfd->para.socket.ip.hosts_allow_table);
      hosts_allow_table = xfd->para.socket.ip.hosts_allow_table;
   }
#endif /* defined(HAVE_HOSTS_ALLOW_TABLE) */
#if defined(HAVE_HOSTS_DENY_TABLE)
   save_hosts_deny_table  = hosts_deny_table;
   if (xfd->para.socket.ip.hosts_deny_table) {
      Debug1("hosts_deny_table = \"%s\"",
	     xfd->para.socket.ip.hosts_deny_table);
      hosts_deny_table  = xfd->para.socket.ip.hosts_deny_table;
   }
#endif /* defined(HAVE_HOSTS_DENY_TABLE) */

   hosts_access_verbose = 32767;
   if (inet_ntop(them->soa.sa_family,
#if WITH_IP6
		 them->soa.sa_family==PF_INET6 ?
		 (void *)&them->ip6.sin6_addr :
#endif
		 (void *)&them->ip4.sin_addr,
		 clientaddr, sizeof(clientaddr)) == NULL) {
      Warn1("inet_ntop(): %s", strerror(errno));
   }
   if (inet_ntop(us->soa.sa_family,
#if WITH_IP6
		 us->soa.sa_family==PF_INET6 ?
		 (void *)&us->ip6.sin6_addr : 
#endif
		 (void *)&us->ip4.sin_addr,
		 serveraddr, sizeof(serveraddr)) == NULL) {
      Warn1("inet_ntop(): %s", strerror(errno));
   }
   Debug7("request_init(%p, RQ_FILE, %d, RQ_CLIENT_SIN, {%s:%u}, RQ_SERVER_SIN, {%s:%u}, RQ_DAEMON, \"%s\", 0",
	   &ri, xfd->fd, clientaddr,
	   ntohs(((struct sockaddr_in *)them)->sin_port),
	   serveraddr, ntohs(us->ip4.sin_port),
	   xfd->para.socket.ip.libwrapname?xfd->para.socket.ip.libwrapname:(char *)diag_get_string('p'));
   request_init(&ri, RQ_FILE, xfd->fd,
		RQ_CLIENT_SIN, them,
		RQ_SERVER_SIN, &us->soa,
		RQ_DAEMON, xfd->para.socket.ip.libwrapname?xfd->para.socket.ip.libwrapname:(char *)diag_get_string('p'), 0);
   Debug("request_init() ->");

   Debug1("sock_methods(%p)", &ri);
   sock_methods(&ri);
   Debug("sock_methods() ->");

   Debug1("hosts_access(%p)", &ri);
   allow = hosts_access(&ri);
   Debug1("hosts_access() -> %d", allow);

#if defined(HAVE_HOSTS_ALLOW_TABLE)
   hosts_allow_table = save_hosts_allow_table;
#endif
#if defined(HAVE_HOSTS_DENY_TABLE)
   hosts_deny_table  = save_hosts_deny_table;
#endif
   if (allow == 0) {
      return -1;
   }
   return 1;
}