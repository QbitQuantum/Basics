/*
  Add a new collector

  Return the collector id, or -1 if not found
*/
int do_add_collector(char* host_and_port /* Format host:port */) {
  struct hostent *h;
  char *host = NULL, *port = NULL;
  int idx, rc;
  struct in_addr addr;

  host = strtok(host_and_port, ":");
  if(host) port = strtok(NULL, ":");

  if((!host) || (!port)) {
    traceEvent(TRACE_ERROR, "Invalid host:port format. Skipped.");
    return(-1);
  }

  h = gethostbyname(host);
  if(h == NULL) {
    traceEvent(TRACE_ERROR, "Unknown host '%s'", host);
    return(-1);
  } else
    memcpy((char*)&addr, h->h_addr_list[0], sizeof(addr));

  if(num_nf_collectors >= MAX_NUM_COLLECTORS) {
    traceEvent(TRACE_ERROR, "Too many nf_collectors defined (%d)", num_nf_collectors);
    return(-1);
  }

  if((rc = do_find_collector(addr, atoi(port))) != -1) {
    traceEvent(TRACE_INFO, "Collector %s:%s has been defined multiple times: duplicates are discarded",
	       host, port);
    return(rc);
  }

  idx = num_nf_collectors;
  memset(&nf_collectors[idx], 0, sizeof(nf_collectors[idx]));
  nf_collectors[idx].addr.sin_family = h->h_addrtype;
  memcpy((char *)&nf_collectors[idx].addr.sin_addr.s_addr, &addr, sizeof(addr));
  nf_collectors[idx].addr.sin_port = htons(atoi(port));

#ifndef linux
  nf_collectors[idx].addr.sin_len = sizeof(struct sockaddr_in);
#endif
  num_nf_collectors++;

  traceEvent(TRACE_NORMAL, "Added new collector %s:%d [total: %d]",
	     host, atoi(port), num_nf_collectors);

  return(idx);
}