int main(int argc, char **argv){
	if(argc==1){ fprintf(stderr, "Error- Usage: %s <Port #>\n",argv[0]); return -1;}
        int s,s2,port;
        struct sockaddr_in sin, from;
        int len = sizeof from;

        sin.sin_family = AF_INET;
	if((port=atoi(argv[1]))<1025){
		fprintf(stderr, "Error- Invalid Port #: %s\n", argv[1]);
		return -1;
	}
        sin.sin_port = htons(port);
        sin.sin_addr.s_addr=INADDR_ANY;

        if((s=socket(AF_INET, SOCK_STREAM,0))==-1){perror("Error creating socket."); return -1;}
        if(bind(s, (struct sockaddr *)&sin, sizeof sin)<0){
                perror("Error binding socket to sockaddr.");
                close(s);
                return -1;
        }
	if(listen(s,128)<0){ perror("Error Listening for TCP Connections."); close(s); return -1; }
        if((s2=accept(s, (struct sockaddr *)&from,&len))<0){
                perror("Error Accepting TCP Connection"); close(s); return -1;
        }

	int r,r_full,n;
        int bsize = 4096;
        int bytes = 0;
        char *buf = malloc(bsize);
        if(buf==NULL){perror("Error Allocating Memory for buffer"); close(s); return -1;}
        char *buf_tmp;
        struct timeval begin,end;
        if(gettimeofday(&begin,NULL)==-1){ perror("Error recording begin-time of read from socket"); close(s); return -1; }
        while((r = read(s2,buf,bsize))!=0){
                if(r==-1){ perror("Error reading from socket"); close(s); return -1; }
                buf_tmp = buf; r_full = r;
                while((n=write(1,buf_tmp,r))!=r && n!=-1){
                        buf_tmp = buf_tmp+n;
                        r-=n;
                }
                if(n==-1){ perror("Error writing to output"); close(s); return -1; }
                bytes+=r_full;
        }
	close(s);close(s2);
        if(gettimeofday(&end,NULL)==-1){ perror("Error recording end-time of read from socket"); close(s); return -1; }

        double secs = difftime(end.tv_sec,begin.tv_sec);
        double usecs = difftime(end.tv_usec,begin.tv_usec)/1000000;
        secs += usecs;
        double rate = bytes/secs/1048576;

	struct hostent *he;
	if(!(he=gethostbyaddr((char *)&from.sin_addr, sizeof from.sin_addr, AF_INET))){
		fprintf(stderr, "Error retrieving information on TCP sender\n");
		herror(" ");
                close(s);
		return -1;
	}
	char *ip = inet_ntoa(from.sin_addr);
	fprintf(stderr, "Remote Endpoint:\n\tIP address: %s\n",ip);
	if(he->h_name) fprintf(stderr, "\tName: %s\n", he->h_name);
	fprintf(stderr, "\tPort: %d\n", ntohs(from.sin_port));
        fprintf(stderr, "Bytes Sent:\t%d\nTransfer Rate:\t%f MB/s\n",bytes,rate);
        close(s); free(buf);
        return 0;
}