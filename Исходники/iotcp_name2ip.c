char *iotcp_name2ip(char *name)
{
  struct   hostent 	host, *host_ptr;
  struct   in_addr 	inaddr;
  char     		local_name[80];
  char     		ip[16];

  SPRINTF(local_name, "%s", name);

  if (NULL == (host_ptr = GETHOSTBYNAME(local_name)))
      return NULL;

  host = *host_ptr;

  inaddr = *((struct in_addr *)host.h_addr_list[0]);

  return INET_NTOA(inaddr);
}