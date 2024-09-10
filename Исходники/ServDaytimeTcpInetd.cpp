int main(int argc, char const *argv[])
{
	socklen_t len;
	struct sockaddr *cliaddr;
	char buff[MAXLINE];
	time_t ticks;
	daemon_inetd(argv[0],LOG_LOCAL2);
	cliaddr=(struct sockaddr *)Malloc(sizeof(struct sockaddr_storage));
	len=sizeof(struct sockaddr_storage);
	Getpeername(0,cliaddr,&len);
	err_msg("connection from %s",Sock_ntop(cliaddr,len));

	ticks=time(NULL);
	snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
	Write(0,buff,strlen(buff));
	Close(0);//close TCP connection
	return 0;
}