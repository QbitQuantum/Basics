USER_FUNC  void upnp_main_thread(void* arg)
{
	int upnp_fd;
	uint32_t if_addr;
	fd_set sockfd_set;
	int max_fd ;
	struct timeval tv;	
	char *pkt_buffer;
	int ret,i;
	char *p=0;
#define UPNP_RECV_PACKET_SIZE      (1024)
	extern int hfnet_enable_multicast(int enable);
	hfnet_enable_multicast(1);
	pkt_buffer = hfmem_malloc(UPNP_RECV_PACKET_SIZE);
	if(pkt_buffer==NULL)
	{
		//u_printf("no mem\n");
		return;
	}
	while(1)
	{
		if((if_addr=get_if_ip_addr())==0)  //µÃµ½Ä£¿éµ±Ç°ipµØÖ·  kim
		{
			msleep(500);
			continue;
		}
		get_mac_addr();
		//u_printf("kim+++ if_addr is %x\n",if_addr);
		
		upnp_fd = create_multicast_socket(if_addr);
		if(upnp_fd<0)
			return;
		else
			break;
	}
	
	//tcp server  
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	memset((char*)&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(30001);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);	

  bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	listen(listenfd,10);

	//u_printf("tcp server bind ok!\n");
	
	
	if(listenfd > upnp_fd)
		max_fd =listenfd;
	else
		max_fd =upnp_fd;
	maxi = -1;
	
	for(i=0;i<MAXCLIENT;i++)
	{
		client[i] = -1;
	}
	//
	
			
	
	while(1)
	{
		int recvsize=0;
	
		tv.tv_sec=0;
		tv.tv_usec=200;
		////u_printf("time=%d\n",hfsys_get_time());
		
		
		
		
		FD_ZERO(&sockfd_set);
		FD_SET(upnp_fd,&sockfd_set);	
		FD_SET(listenfd,&sockfd_set);
		
	
		for(i=0;i<MAXCLIENT;i++)
		{
			if(client[i]>=0)
			{
				
				FD_SET(client[i],&sockfd_set);
				
				if(client[i] > max_fd)
					max_fd =client[i];
			
			}
		}
	/*	
			count++;
			if(count == 1000)
			{
				//u_printf("send alive package\r\n");
				send_alive_packet(upnp_fd,pkt_buffer,UPNP_RECV_PACKET_SIZE,if_addr);			
				count = 0;
			}		
		*/
		ret=select(max_fd+1,&sockfd_set,NULL,NULL,&tv);
		
		

		
		
		if(ret<=0)
		{
					
			//send_alive_packet(upnp_fd,pkt_buffer,UPNP_RECV_PACKET_SIZE,if_addr);
			continue;
		}
	
		if(FD_ISSET(listenfd, &sockfd_set))   //s2
		{
		
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
			for(i=0;i<MAXCLIENT;i++)
			{
				if(client[i]<0)
				{
					client[i] = connfd;
					maxi = maxi+1;
					//u_printf("accept client socket : %d  client count : %d\n",connfd,maxi+1);
					break;
				}
			}
			if(i == MAXCLIENT)
			{
				//u_printf("too many clients\r\n");
			}
			
		  /*FD_SET(connfd, &sockfd_set); //½«ÒÑÁ¬½Ósocket ¼ÓÈëselect
			
			if(connfd > max_fd)
				max_fd = connfd;  */
			
			//if(i > maxi)
			
			
			if(--ret<=0)
				continue;			
		}
	
		for(i=0;i<=maxi;i++)  //¼ì²éËùÓÐµÄÒÑÁ¬½ÓsocketÓÐÎÞÊý¾Ý  //s3
		{
			
			if(((sockfd = client[i])<0))
				continue;
			
			if(FD_ISSET(sockfd, &sockfd_set))
			{
				
				if((recv_num =recv(sockfd,tcpserver_buf,sizeof(tcpserver_buf),0))>0)
				{
					while(tcp_send_finish == 0)
					{
						u_printf("busy,try late again\r\n");
						msleep(10);
					}
					
					tcp_send_finish = 0;
					////u_printf("recv data bytes:%d\n %s\r\n",recv_num,tcpserver_buf);

					
					if(recv_num <400)  //·ÀÖ¹Á½ÌõÏûÏ¢Õ³Á¬
					{						
						TCP_Encode(); //add tcp identification code			

						u_printf("FW to MCU,LOCAL TCP,TCP fd is %d:\r\n%s\r\n\r\n",sockfd,tcpserver_encodedbuf);
						
						hfuart_send(HFUART0,tcpserver_encodedbuf,strlen(tcpserver_encodedbuf), 50);
					
				//	if(tcp_uartfd == 0)
					//{
						tcp_uartfd = sockfd;
					}
					else
					{
						u_printf("recv num is %d, a catastrophe.Get rid of it\r\n",recv_num);					
					}
					
						tcp_send_finish = 1;

					
					  //²âÊÔ²éÑ¯Éè±¸ÓÃ
/*		
					if((p = strstr(tcpserver_buf,"info"))!= NULL)   //ÊÖ»ú²éÑ¯Éè±¸ÐÅÏ¢
				{
					//u_printf("send info\r\n");
					write(sockfd,info,strlen(info));
				}
				else if((p = strstr(tcpserver_buf,"channel"))!= NULL)   //ÊÖ»ú²éÑ¯°²È«Ä£Ê½´ò¿ª¹Ø±ÕµÄ×´Ì¬
				{
					//u_printf("send channel\r\n");
					write(sockfd,channel,strlen(channel));
				}
	*/				
				
					memset(tcpserver_encodedbuf,0,400);
					memset(tcpserver_buf,0,400);		
				
				}
				else
				{
					close(sockfd);
					//FD_CLR(sockfd, &sockfd_set);
					client[i] = -1;
					maxi=maxi -1;
					//u_printf("delet client socket ,client count : %d\n",maxi+1);
					
				}
		
				if(--ret <= 0)
					break;
				
			}
		}		
		
		
		if(FD_ISSET(upnp_fd, &sockfd_set))  //s1
		{			
			struct sockaddr_in fromaddr;
			
				
			socklen_t sockaddr_size = sizeof(struct sockaddr_in);
			memset(pkt_buffer,0,UPNP_RECV_PACKET_SIZE);
			recvsize = recvfrom(upnp_fd, (char*)pkt_buffer, UPNP_RECV_PACKET_SIZE-4, 0,(struct sockaddr *) &fromaddr, &sockaddr_size);
			
	//		//u_printf("kim+++ Broadcast from  ip:%x, port:%x\n",fromaddr.sin_addr.s_addr,fromaddr.sin_port);
			if (recvsize < 0)
			{
				//u_printf("recv() fail\n");
			}
			else
			{

				
				
				if(strstr(pkt_buffer,"Lucis-tech")!=NULL)
				{
					//u_printf("recv length=%d,buffer is %s\n",recvsize,pkt_buffer);
					if(Sync_Flag == 1)   //only  after  mcu sync Fa info to wifi
					{
						//u_printf("test AAA\r\n");
						send_msearch_rsp_packet(&fromaddr);
					}
				}	

			}			
			
			if(--ret<=0)
				continue;
		}
		


	}

	if(pkt_buffer!=NULL)
		hfmem_free(pkt_buffer);
	
	return ;
}