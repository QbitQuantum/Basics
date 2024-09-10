main(int argc, char *argv[])
{
 int sockfd, newsockfd, clilen, childpid;
 struct sockaddr_in cli_addr, serv_addr;
 int fd, orbfd;
 time_t cur_time;
 int PORT;
 int con, c;
 in_addr_t lna;
 int val, lcv, lcv2, lcv3=0, high_fd;
 struct timeval timeout;
 char buffer[10002];
 fd_set read_fds, except_fds;

 for (lcv=0;lcv<NUM_CLIENTS;lcv++)
   local_data.connected[lcv]=local_data.ipaddr[lcv]=local_data.used[lcv]=0;

  strt.msgID = 2;
  strt.msgSize = 8;

 if (argc != 3) {
   fprintf(stderr, "usage: %s port sourcename\n", argv[0]);
   exit(1);
 }

 PORT=atoi(argv[1]);

 printf("source name: %s\nport: %d\n",argv[2],PORT);

 *((short int *)buffer)=htons(100);

 if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
     perror("revelle_data: can't open stream socket");
     exit(-1);
   }

 bzero((char *) &serv_addr, sizeof(serv_addr));

 if (-1 != (lna=inet_addr("198.202.124.8")))
   memcpy(&(serv_addr.sin_addr), &lna, 
	  min(sizeof(serv_addr.sin_addr), sizeof(lna)));
 else
   {
     perror("host lookup failed");
     exit(-1);
   }

 serv_addr.sin_family      = AF_INET;
 serv_addr.sin_port        = htons(PORT);

 if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
   {
     perror("connect failed!");
     exit(-1);
   }

 while(1)
   {
     FD_ZERO(&read_fds);
     FD_SET(sockfd,&read_fds);
     high_fd=sockfd+1;

     timeout.tv_sec=10;
     timeout.tv_usec=0;
     lcv=select(high_fd,&read_fds,0,0,&timeout);
     if (lcv<0)
       {
	 perror("select");
	 exit(-1);
       }
     else if (FD_ISSET(sockfd,&read_fds))
       {
	
	 if (read(sockfd,buffer,2)<=0)
	   {
	     perror("read");
	     exit(-1);
	   }
	
	 printf(" * %d\n",*((short int*)buffer));
       }
     else
       {
	 pkt.msgID=htons(1);
	 pkt.msgSize=htons(58);
	 pkt.seq_num=htonl(lcv3++);
	 pkt.timestamp=time(NULL);
	 pkt.num_chan=htons(2);
	 pkt.num_samp=htons(2);
	 pkt.samp_rate=1.0;
	 strncpy(pkt.sta_name,"PFO",5);
	 strncpy(pkt.net_name,"SM",2);
	 pkt.pad=0;

	 strncpy(buffer,"dus",3); /* channel */
	 strncpy(buffer+3,"N",2); /* location code */
	 *(buffer+4)=0; /* pad */
	 strncpy(buffer+6,"lon",3); /* channel */
	 strncpy(buffer+9,"S",2); /* location code */
	 *(buffer+11)=0; /* pad */
	 *((short int*)(buffer+12))=htons(1000);
	 *((short int*)(buffer+14))=htons(-1000);
	 *((short int*)(buffer+16))=htons(3);
	 *((short int*)(buffer+18))=htons(4);

	 /*pkt.chksum=htons(0);*/ /* use this to send invalid pkts */
	 pkt.chksum=htons(sumit((char*)&pkt,36,buffer,20));
	 printf("sent data checksum=%d, size of header=%d\n",ntohs(pkt.chksum),sizeof(pkt));


	 if (write(sockfd,&pkt,38)!=38)
	   {
	     printf("write issue!\n");
	   }
	 if (write(sockfd,buffer,20)!=20)
	   {
	     printf("write issue!2\n");
	   }
       }
   }
}