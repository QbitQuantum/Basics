/* Incomming string format: host[:port][,host[:port]]... */
int ares_set_servers_csv(ares_channel channel,
                         const char* _csv)
{
  int i;
  char* csv = NULL;
  char* ptr;
  char* start_host;
  long port;
  bool found_port;
  int rv = ARES_SUCCESS;
  struct ares_addr_node *servers = NULL;
  struct ares_addr_node *last = NULL;

  if (ares_library_initialized() != ARES_SUCCESS)
    return ARES_ENOTINITIALIZED;

  if (!channel)
    return ARES_ENODATA;

  ares__destroy_servers_state(channel);

  i = strlen(_csv);
  if (i == 0)
     return ARES_SUCCESS; /* blank all servers */

  csv = malloc(i + 2);
  strcpy(csv, _csv);
  if (csv[i-1] != ',') { /* make parsing easier by ensuring ending ',' */
    csv[i] = ',';
    csv[i+1] = 0;
  }

  start_host = csv;
  found_port = false;
  for (ptr = csv; *ptr; ptr++) {
    if (*ptr == ',') {
      char* pp = ptr - 1;
      struct in_addr in4;
      struct ares_in6_addr in6;
      struct ares_addr_node *s = NULL;

      *ptr = 0; /* null terminate host:port string */
      /* Got an entry..see if port was specified. */
      while (pp > start_host) {
        if (*pp == ':')
          break; /* yes */
        if (!ISDIGIT(*pp)) {
          /* Found end of digits before we found :, so wasn't a port */
          pp = ptr;
          break;
        }
        pp--;
      }
      if ((pp != start_host) && ((pp + 1) < ptr)) {
        /* Found it. */
        found_port = true;
        port = strtol(pp + 1, NULL, 10);
        *pp = 0; /* null terminate host */
      }
      /* resolve host, try ipv4 first, rslt is in network byte order */
      rv = ares_inet_pton(AF_INET, start_host, &in4);
      if (!rv) {
        /* Ok, try IPv6 then */
        rv = ares_inet_pton(AF_INET6, start_host, &in6);
        if (!rv) {
          rv = ARES_EBADSTR;
          goto out;
        }
        /* was ipv6, add new server */
        s = malloc(sizeof(*s));
        if (!s) {
          rv = ARES_ENOMEM;
          goto out;
        }
        s->family = AF_INET6;
        memcpy(&s->addr, &in6, sizeof(struct ares_in6_addr));
      }
      else {
        /* was ipv4, add new server */
        s = malloc(sizeof(*s));
        if (!s) {
          rv = ARES_ENOMEM;
          goto out;
        }
        s->family = AF_INET;
        memcpy(&s->addr, &in4, sizeof(struct in_addr));
      }
      if (s) {
        /* TODO:  Add port to ares_addr_node and assign it here. */

        s->next = NULL;
        if (last) {
          last->next = s;
        }
        else {
          servers = s;
          last = s;
        }
      }

      /* Set up for next one */
      found_port = false;
      start_host = ptr + 1;
    }
  }

  rv = ares_set_servers(channel, servers);

  out:
  if (csv)
    free(csv);
  while (servers) {
    struct ares_addr_node *s = servers;
    servers = servers->next;
    free(s);
  }

  return rv;
}