int main(int argc,char *argv[])
{
	int listenfd,optval;
	struct sockaddr_in servaddr;

	if(argc != 2)
		err_quit("usage:tcpsrvipv4 <IPAddress>");

	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);

	Inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

	optval = 1;
	Setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));

	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));

	Listen(listenfd,LISTENQ);

	pause();
}