void *thread_send_query(void *arg)
{
    int fd;
	struct sockaddr_in cliddr,servddr;
	char *ip = "127.0.0.1";
	char buf[1000] = {0};
	
	cliddr.sin_family = AF_INET;
	Inet_pton(AF_INET,ip,&cliddr.sin_addr);
	//随机端口
	cliddr.sin_port = htons(0);
	
	fd = Socket(AF_INET,SOCK_STREAM,0);
	//Bind(fd,(struct sockaddr *)&cliddr,sizeof(cliddr));

	servddr.sin_family = AF_INET;
	Inet_pton(AF_INET,g_data.server.ip,&servddr.sin_addr);
	servddr.sin_port = htons(g_data.server.port);
	
	Connect(fd,(struct sockaddr *)&servddr,sizeof(servddr));
	
    for (int i = 0; i < g_data.per_thread_loop_num; ++i)
    {   
        snprintf(buf, sizeof(buf), "%s", "hello, huangben!");
	    Send(fd,buf,strlen(buf),0);
		int n =Recv(fd,buf,sizeof(buf),0);
		buf[n] = 0;
		printf("from server:%s\n",buf);
    }
	
	Close(fd);
    return NULL;
}