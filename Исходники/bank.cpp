int send_to_and_recv_from_bank_of_boc(char* pSend, int send_len,char* pRecv,int *recv_len,int max_recv_len,int delay_time)
{
	struct SockNode  SockNode,SockNode_rsp;
	CTcpSocket sock;	

	char bank_ip[20]="";
	int bank_port=0;
	int bank_port_rsp=0;
	//int delay_time=0;
	int ret=0;
	char temp[5]="";
	int length=0;

	TIniFile tf;

	if (!tf.Open(TRANS_INI_FILE))
	{
	   writelog(LOG_ERR,"Cann't open ini file,file=[%s]\n",TRANS_INI_FILE);
	   return E_TRANS_UNKNOW_ERROR;
	}

	tf.ReadString("BANK", "BANK_IP", "127.0.0.1", bank_ip,sizeof(bank_ip));
	bank_port=tf.ReadInt("BANK", "BANK_PORT",9001);
	bank_port_rsp=tf.ReadInt("BANK", "BANK_PORT_RSP",9002);

	if(0==delay_time)	delay_time=tf.ReadInt("BANK", "BANK_DELAY_TIME", 3000);
	tf.Close();
	
#ifdef	DEBUG
	//printf("BANK_IP=[%s],BANK_PORT[%d],DELAY_TIME[%d]\n",bank_ip,bank_port,delay_time);
#endif
	writelog(LOG_DEBUG,"connect to bank [%s][%d][%d]",bank_ip,bank_port,bank_port_rsp);
	//连接银行
	ret=SockNode.hSock.ConnectTcp(bank_ip, bank_port,5);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,bank_port);
		return E_TRANS_BANK_NETERR;
	}
	//发送数据到银行
	ret=SockNode.hSock.Send(pSend, send_len);
	
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,ret = %ret, error code is [%d] ",ret, errno);
		return E_TRANS_BANK_NETERR;
	}
	else if (0==ret)
	{
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank error，CTcpSocket.Send should not return this error,error code is[%d]!\n",errno);
	      	return	E_TRANS_BANK_NETERR;
	}
	writelog(LOG_DEBUG,"send to bank success, waiting for responsing!!");
	sleep(1);
	if(!sock.Create())
	{
	      	writelog(LOG_ERR,"sock.Create error!\n");
	      	return	E_TRANS_BANK_NETERR;
	}
	if(!sock.Listen(bank_port_rsp))
	{
	      	writelog(LOG_ERR,"sock.Listen error![%d]",errno);
	      	return	E_TRANS_BANK_NETERR;
	}
	CTcpSocket rcv_sock;
	if(sock.Accept(rcv_sock))
	{
		int rcvlen = rcv_sock.Recv(pRecv,max_recv_len,delay_time);
		if(rcvlen < 0)
		{
		      	writelog(LOG_ERR,"sock.Recv error![%d][%d]\n",rcvlen,errno);
		      	return	E_TRANS_BANK_NOANSWER;
		}
		writelog(LOG_DEBUG,"recv length[%d]",rcvlen);
		*recv_len=rcvlen;
		return 0;
	}
	return E_TRANS_BANK_NOANSWER;


/*

	ret=SockNode_rsp.hSock.Listen(bank_port_rsp);
	if(!ret)
	{
		char msg[256]="";
		SockNode_rsp.hSock.GetLastError(msg);
	      	writelog(LOG_ERR,"Listen bank error,error code is[%d],msg=[%s]!\n",ret,msg);
		return	E_TRANS_BANK_NETERR;
	}
	CTcpSocket rcv_sock;
	ret=SockNode_rsp.hSock.Accept(rcv_sock);
	if(ret)
	{
		int rcvlen = SockNode.hSock.Recv(pRecv,max_recv_len,delay_time);
		if(rcvlen < 0)
		{
			char msg[256]="";
			SockNode_rsp.hSock.GetLastError(msg);
		      	writelog(LOG_ERR,"Receive from bank error,error code is[%d],msg=[%s]!\n",ret,msg);
			return	E_TRANS_BANK_NETERR;
		}
		*recv_len=rcvlen;
		SockNode.hSock.Close();
		SockNode_rsp.hSock.Close();
		rcv_sock.Close();
		return 0;
	}
	return -2;
	*/
}