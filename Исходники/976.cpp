UINT engine2(LPVOID tip)
{
	int ip=int(tip);
#ifdef WIN32
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2,0),&wsadata)!=0){printf("[+] wsastartup error\n");mthread--;return -1;}
#endif
	SOCKET s;fd_set mask;struct timeval timeout, timeout2; struct sockaddr_in server;
	s=socket(AF_INET,SOCK_STREAM,0);
	if (s==-1){se++;mthread--;
#ifdef WIN32
	return -1;
#else
	return engine;
#endif
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(ip);
	server.sin_port=htons(42);
	if (scanend<=scan+1){printf("[+] status..: %d%s thread(s):%d       \r",(scanend)*100/(scan),pcent,mthread);}
	unsigned long flag=1;
	if (ioctlsocket(s,FIONBIO,&flag)!=0)
	{
		se++;mthread--;closesocket(s);
#ifdef WIN32
		return -1;
#else
		return engine;
#endif
	}
	connect(s,( struct sockaddr *)&server,sizeof(server));
	timeout.tv_sec=3;timeout.tv_usec=0;timeout2.tv_sec=5;timeout2.tv_usec=0;FD_ZERO(&mask);FD_SET(s,&mask);
	switch(select(s+1,NULL,&mask,NULL,&timeout))
	{
		case -1: {mthread--;closesocket(s);
#ifdef WIN32
		return -1;
#else
		return engine;
#endif
}
		case 0: {mthread--;closesocket(s);
#ifdef WIN32
		return -1;
#else
		return engine;
#endif
}
		default:
		if(FD_ISSET(s,&mask))
		{
			ok2++;
			if (send(s,data,sizeof(data)-1,0)==-1){fprintf(fplog,"IP.............: %s:%d\nSTATUS.........: error sending, not wins\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));fflush(fplog);
			if (bose2==1){printf("IP.............: %s:%d            \nSTATUS.........: error sending, not wins            \n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));}
			mthread--;tot++;closesocket(s);
#ifdef WIN32
			return -1;
#else
			return engine;
#endif
}
			sl(3);
			switch(select(s+1,&mask,NULL,NULL,&timeout2))
			{
				case -1: {mthread--;closesocket(s);
#ifdef WIN32
				return -1;
#else
				return engine;
#endif
}
				case 0: {fprintf(fplog,"IP.............: %s:%d\nSTATUS.........: nothing received, not wins or vulnerable service freezing\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));fflush(fplog);
				if (bose2==1){printf("IP.............: %s:%d            \nSTATUS.........: nothing received, not wins or vulnerable service freezing\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));}
				mthread--;tot++;closesocket(s);
#ifdef WIN32
				return -1;
#else
				return engine;
#endif
}
				default:
				rc = recv(s,recvbuf,sizeof(recvbuf),0);
			}
			if (rc<40||recvbuf[3]!=41&&recvbuf[8]!=88){fprintf(fplog,"IP.............: %s:%d\nSTATUS.........: not wins, wrong datas\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));fflush(fplog);
			if (bose2==1){printf("IP.............: %s:%d            \nSTATUS.........: not wins, wrong datas            \n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));}
			mthread--;tot++;closesocket(s);
#ifdef WIN32
			return -1;
#else
			return engine;
#endif
}
			ok3++;
			if (recvbuf[24]==-144&&recvbuf[25]==-107){spb=0;}
			else if (recvbuf[24]==40&&recvbuf[25]==-5){spb=1;}
			if (recvbuf[36]==37&&recvbuf[39]==1){fprintf(fplog,"IP.............: %s:%d\nSTATUS.........: wins enabled\nVULNERABILITY..: NOT_PATCHED\nOS.............: Windows 2003 SP%d\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),spb);fflush(fplog);
			if (bose2==1){printf("IP.............: %s:%d            \nSTATUS.........: wins enabled            \nVULNERABILITY..: NOT_PATCHED            \nOS.............: Windows 2003 SP%d            \n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),spb);}
			ok++;k3++;tot++;if (bose==1){scr1(server);}mthread--;closesocket(s);
#ifdef WIN32
			return -1;
#else
			return engine;
#endif
}
			else if (recvbuf[36]==53&&recvbuf[39]==1){fprintf(fplog,"IP.............: %s:%d\nSTATUS.........: wins enabled\nVULNERABILITY..: patched\nOS.............: Windows 2003 SP%d\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),spb);fflush(fplog);
			if (recvbuf[24]==-144&&recvbuf[25]==-107){spb=0;}
			else if (recvbuf[24]==40&&recvbuf[25]==-5){spb=1;}
			if (bose2==1){printf("IP.............: %s:%d            \nSTATUS.........: wins enabled            \nVULNERABILITY..: patched            \nOS.............: Windows 2003 SP%d            \n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),spb);}
			k3++;mthread--;tot++;closesocket(s);
#ifdef WIN32
			return -1;
#else
			return engine;
#endif
}
			else if (recvbuf[36]==71&&recvbuf[39]==1){fprintf(fplog,"IP.............: %s:%d\nSTATUS.........: wins enabled\nVULNERABILITY..: patched\nOS.............: Windows 2003 SP1\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));fflush(fplog);
			if (bose2==1){printf("IP.............: %s:%d            \nSTATUS.........: wins enabled            \nVULNERABILITY..: patched            \nOS.............: Windows 2003 SP1            \n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));}
			k3++;mthread--;tot++;closesocket(s);
#ifdef WIN32
			return -1;
#else
			return engine;
#endif
}
			else if (recvbuf[36]==85&&recvbuf[37]==31&&recvbuf[40]==24&&recvbuf[41]==37||
							 recvbuf[36]==-111&&recvbuf[37]==-127&&recvbuf[40]==64&&recvbuf[41]==-106||
							 recvbuf[36]==-107&&recvbuf[37]==43&&recvbuf[40]==8&&recvbuf[41]==54||
							 recvbuf[36]==-89&&recvbuf[37]==-99&&recvbuf[40]==-128&&recvbuf[41]==38||
							 recvbuf[36]==69&&recvbuf[37]==-112&&recvbuf[40]==-144&&recvbuf[41]==31||
							 recvbuf[36]==-37&&recvbuf[37]==-128&&recvbuf[40]==-136&&recvbuf[41]==-82){
			if (recvbuf[36]==85&&recvbuf[37]==31&&recvbuf[40]==24&&recvbuf[41]==37||recvbuf[36]==-111&&recvbuf[37]==-127&&recvbuf[40]==64&&recvbuf[41]==-106){sp=4;}
			else if (recvbuf[36]==-107&&recvbuf[37]==43&&recvbuf[40]==8&&recvbuf[41]==54){sp=3;}
			else if (recvbuf[36]==-89&&recvbuf[37]==-99&&recvbuf[40]==-128&&recvbuf[41]==38){sp=2;}
			else if (recvbuf[36]==69&&recvbuf[37]==-112&&recvbuf[40]==-144&&recvbuf[41]==31){sp=1;}
			else if (recvbuf[36]==-37&&recvbuf[37]==-128&&recvbuf[40]==-136&&recvbuf[41]==-82){sp=0;}
			if (recvbuf[16]==0&&recvbuf[17]==0&&recvbuf[18]==0){fprintf(fplog,"IP.............: %s:%d\nSTATUS.........: wins enabled\nVULNERABILITY..: patched\nOS.............: Windows 2000 SP%d\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),sp);fflush(fplog);
			if (bose2==1){printf("IP.............: %s:%d            \nSTATUS.........: wins enabled            \nVULNERABILITY..: patched            \nOS.............: Windows 2000 SP%d            \n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),sp);}
			k0++;mthread--;tot++;closesocket(s);
#ifdef WIN32
			return -1;
#else
			return engine;
#endif
}
			else {fprintf(fplog,"IP.............: %s:%d\nSTATUS.........: wins enabled\nVULNERABILITY..: NOT_PATCHED\nOS.............: Windows 2000 SP%d\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),sp);fflush(fplog);
			if (bose2==1){printf("IP.............: %s:%d            \nSTATUS.........: wins enabled            \nVULNERABILITY..: NOT_PATCHED            \nOS.............: Windows 2000 SP%d            \n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port),sp);}
			ok++;k0++;tot++;if (bose==1){scr2(server);}mthread--;closesocket(s);
#ifdef WIN32
			return -1;
#else
			return engine;
#endif
}
			}
			else {
				fprintf(fplog,"IP.............: %s:%d\nSTATUS.........: wins enabled\nVULNERABILITY..: unknown\nOS.............: NT4 (OS not implemented)\n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));fflush(fplog);
				if (bose2==1){printf("IP.............: %s:%d            \nSTATUS.........: wins enabled            \nVULNERABILITY..: unknown            \nOS.............: NT4 (OS not implemented)            \n\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));}
				t4++;mthread--;tot++;closesocket(s);
#ifdef WIN32
				return -1;
#else
				return engine;
#endif
}
		}
	}
	mthread--;
	closesocket(s);
#ifdef WIN32
	return 0;
#else
	return engine;
#endif
}