void dg_echo(int fd,struct sockaddr_in *pcliaddr,socklen_t socklen)
{
	socklen_t len;
	char line[MAXLINE];
	for(;;)
	{
		len = socklen;
		n = Recvfrom(fd,line,MAXLINE,0,pcliaddr,&len);
		Sendto(fd,line,strlen(line),0,pcliaddr,len);
	}
}