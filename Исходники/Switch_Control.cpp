int Switch_Control::SendResetMessage(const char* phostIp,int iPort)
{
	struct sockaddr_in s_addr;
	int sockid;
	socklen_t addr_len;

    sockid=socket(AF_INET,SOCK_STREAM,0);
	    
    s_addr.sin_family = AF_INET ;

   	s_addr.sin_addr.s_addr = inet_addr(phostIp) ;
    s_addr.sin_port=htons((unsigned short)iPort);

   
/*	 if (-1 == fcntl(sockid, F_SETFL, O_NONBLOCK))
	 {
		 printf("fcntl socket error!\n");
		 fflush(stdout);
		 return -1;
	 }	 
*/
	 
	 unsigned long ul = 1;
	 ioctl(sockid, FIONBIO, &ul); //设置为非阻塞模式
	 struct timeval timeout={3,1000*500}; //1秒
	 int len = sizeof(timeout);
	 setsockopt(sockid,SOL_SOCKET,SO_SNDTIMEO, &timeout,len);
	 setsockopt(sockid,SOL_SOCKET,SO_RCVTIMEO,&timeout,len);

	fd_set set;
 	printf("---begin connect \n");
    //重复连接3次，防止中断等原因导致的异常
    for(int i=0;i<3;i++)
    {
    	bool ret = false;
		int iret = -1;
		iret = connect(sockid,(struct sockaddr *)&s_addr,(int)(sizeof(s_addr)));
  		if(iret == -1)
   		{
   			struct timeval tm;
     		tm.tv_sec  = 0;
     		tm.tv_usec = 1000*500;
     		FD_ZERO(&set);
     		FD_SET(sockid, &set);
			int error=-1;
     		if( select(sockid+1, NULL, &set, NULL, &tm) > 0)
     		{
       			getsockopt(sockid, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len);
       			if(error == 0) 
				{
					ret = true;
					printf("---error no \n");
					//::close(sockid);
					//break;
   				}
 				else ret = false;
    		} else ret = false;
  		}
 		else if(iret==0)
		{	
			
			break;
		}
		if(i==2) 
    	 {
    	 	  //cout<<"connect Error "<<p_host<<":"<<p_Port<<endl;
    	 	  //perror("::connect");
    	 	  ::close(sockid);
    	 	  return -1;
    	 }
		 printf("---sleeep\n");
    	 usleep(1000);
    	 //cout<<"connect again: "<<p_host<<":"<<p_Port<<endl;
    }
    int     optval = 1;

	 ul = 0;
	 ioctl(sockid, FIONBIO, &ul); //设置为阻塞模式
	printf("---connect success \n");	

	char alivetick[1024]={0};
	int iData=0;
	char strdata[32]={0};
	sprintf(strdata,"%d",iData);
  	//发送心跳
	Stream ptmpRequest;

	ptmpRequest.m_clientSocket = sockid;
	//cJSON *pRet_root;
	ptmpRequest.pRet_root = cJSON_CreateObject();
	ptmpRequest.Requst_Json_str(2,"cmd","reset_device");
	ptmpRequest.Requst_Json_str(2,"returnCode","0");
	ptmpRequest.Requst_Json_str(2,"serialno","11111111");
	ptmpRequest.Send_Jsoon_str();

	memset(alivetick,0,sizeof(alivetick));
	int length = 0;
	int i_rc = 0, i_count = 0;
	int iRecvLen = 0;
	do
	{
		i_rc = recv(sockid, alivetick + i_count, 2000 - i_count, 0);
		if (i_rc <= 0)break;//异常关闭
		i_count += i_rc;
	} while (strstr(alivetick, "XXEE") == NULL);
	iRecvLen = i_count;
	if (iRecvLen <= 0){
		::close(sockid);
		return -1;
	}
	printf("recv:%s \n",alivetick);

	cJSON *pcmd = NULL;

			//解析报文数据
	replace(alivetick, "XXEE", "");
	cJSON* pRoot = cJSON_Parse(alivetick);

	if (pRoot)
	{
		pcmd = cJSON_GetObjectItem(pRoot, "cmd");
		if (pcmd)
		{
			//判断请求类型
			if(strcmp(pcmd->valuestring, "reset_device") == 0)
			{
				::close(sockid);
				return 0;
			}
		}

	}
	::close(sockid);
	return -1;
}