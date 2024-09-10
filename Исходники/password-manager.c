static void
set_protocol_by_port(char **protocol, int port)
{
  struct servent *srv;
  srv = getservbyport(htons(port), NULL);
  if (srv) *protocol = srv->s_name;
}