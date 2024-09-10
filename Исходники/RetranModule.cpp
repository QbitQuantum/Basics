DWORD WINAPI RetranTreat(LPVOID lpParameter){

	WORD wVersionRequested; 
    WSADATA wsaData; 
    int err; 
    wVersionRequested = MAKEWORD(1,1); 
    err = WSAStartup(wVersionRequested,&wsaData); 
    if ( err != 0 ) { 
        return -1; 
    } 

    if ( LOBYTE( wsaData.wVersion ) != 1 || 
        HIBYTE( wsaData.wVersion ) != 1) { 
            WSACleanup( ); 
            return -1; 
    } 

    SOCKET retran_socket=socket(AF_INET,SOCK_DGRAM,0);

    SOCKADDR_IN  retran_addr;

	
	

    //retran_addr.sin_addr.S_un.S_addr=inet_addr("192.168.1.5");           //此处有修改
	retran_addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    retran_addr.sin_family=AF_INET;
    retran_addr.sin_port=htons(retranport);

    if(bind(retran_socket,(sockaddr*)&retran_addr,sizeof(SOCKADDR_IN))==-1){
		printf("bind error~~~~~~~~~~~~~~\n");
	}

	int priority=0;

	while(1) 
    { 
		SOCKADDR_IN client_socket; 
		int len = sizeof(SOCKADDR);
        char recvbuf[1500]; 
        int commd_size=recvfrom(retran_socket,recvbuf,1500,0,(SOCKADDR*)&client_socket,&len);
		if(commd_size<=0){
			//printf("Retan Comm error");
			continue;   //这个是自己加的9-24
		}
		printf("treat Retan %s to UPD server port %d  size:%d\n",inet_ntoa(client_socket.sin_addr),ntohs(client_socket.sin_port),commd_size);
		int pointer = 0;
		int userid ;
		memcpy(&userid,recvbuf,sizeof(int));
		pointer +=sizeof(int);
		while(1){
			priority++;
			long miss_top_id;
			int sqnum;
			int timestmp;
			memcpy(&miss_top_id,recvbuf+pointer,sizeof(long));
			pointer += sizeof(miss_top_id);
			memcpy(&sqnum,recvbuf+pointer,sizeof(int));
			pointer += sizeof(sqnum);
			memcpy(&timestmp,recvbuf+pointer,sizeof(int));
			pointer += sizeof(timestmp);

			RestoreCell rc;

			//printf("apply data id:%d sqnum:%d timestmp%d\n",miss_top_id,sqnum,timestmp);
			if(rsb.applyData(miss_top_id,sqnum,timestmp,&rc)>=0){
				//printf("finded data sqnum:%d\n",sqnum);

				KeyValue  *pkg=new KeyValue();
				memcpy(pkg->value,rc.data,rc.size+sizeof(long)+sizeof(int));
				pkg->pkgsize=rc.size;
				pkg->user_id=userid;
				pkg->key=priority;


				if(!retransQueue.isInSchedule(*pkg)){
				    retransQueue.priority_queue_enqueue(pkg);
				}
			}


			if(pointer+1>=commd_size)
				 break;


		}
    } 

	return 0;


}