/*
signal occur must in recvfrom ,or it must be a dead cycle
*/
void dg_cli(FILE *fp,int sockfd,const SA *pservaddr,socklen_t servlen){
	int n;
	const in on = 1;
	char sendline[MAXLINE+1],recvline[MAXLINE+1];
	socklen_t len;
	struct sockaddr_in *preply_addr;
	preply_addr = malloc(sizeof(struct sockaddr_in));
	bzero(preply_addr);
	SetSockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));
	Signal(SIGALAM,recvfrom_alarm);
	len = servlen;
	while(Fgets(sendline,MAXLINE,fp) != NULL){
		sendto(sockfd,sendline,strlen(sendline),0,pservaddr,len);
		alarm(5);
		for(;;){
			len=servlen;
			n = recvfrom(sockfd,recvlien,MAXLINE,0,preply_addr,&len);
			if(n < 0){
				if(errno == EINTR)
					break;
				else
					err_quit("recvfrom error!");
			}else{
				recvfrom[n] = 0;
				printf("from %s : %s",inet_ntop(preply_addr->sin_family,preply_addr->sin_addr.s_addr,preply_addr->sin_len),recvfrom);
			}
		}
	}
}