int	connect_server(t_client *cl)
{
  if ((cl->proto = getprotobyname(PROTO)) == NULL)
    return (error("getprotobyname"));
  if ((cl->sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    return (error("socket"));
  cl->sin.sin_family = AF_INET;
  cl->sin.sin_port = htons(cl->port);
  bcopy(cl->host->h_addr_list[0], &cl->sin.sin_addr.s_addr,
	sizeof(struct in_addr));
  cl->addrlen = sizeof(cl->sin);
  if (fprintf(stdout, "Initializing client: \033[32mOK\033[00m\n") == -1)
    return (error("fprintf"));
  printf("Try connecting... %s:%d\n", inet_ntoa(cl->sin.sin_addr), cl->port);
  if (connect(cl->sock, (struct sockaddr*)&cl->sin, cl->addrlen) == -1)
    return (error("connect"));
  printf("Client-fx connect successfullly\n\n");
  return (0);
}