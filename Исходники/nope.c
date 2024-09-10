void process(int fd,  fd_set *pMaster, struct sockaddr_in *clientaddr){
    printf("accept request, fd is %d, pid is %d\n", fd, getpid());

    int status = 200;

	char buf[1024];
	u_int numchars;
	char method[255];
	char url[1024];
	size_t i, j;
    int client=fd;

	numchars = getLine(client, buf, sizeof(buf));

	i = 0; j = 0;
	while (!ISspace(buf[j]) && (i < sizeof(method) - 1))
	{
		method[i] = buf[j];
		i++; j++;

	}
	method[i] = '\0';

	if (strcasecmp(method, "GET") && strcasecmp(method, "POST"))
	{
		unimplemented(client);
		return;
	}


	i = 0;
	while (ISspace(buf[j]) && (j < sizeof(buf)))
		j++;
	while (!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf)))
	{
		url[i] = buf[j];
		i++; j++;
	}
	url[i] = '\0';

	Request request;
	request.client=client;
	request.reqStr=url;
	request.method=method;

	/*server(client,url,method);*/

	server(request);

	close(client);

	http_request req;
	strncpy(req.filename, url, sizeof req.filename);
    log_access(status, clientaddr, &req);
}