int doProcess(CTcpSocket &acpsocket)
{
    printf("\n doProcess3  \n");
	
	
	int ret = 0;
    int pack_len = 0;
    int send_len = 0;
    char recv_buf[4096] = "";
    char send_buf[4096] = "";
	//ret = acpsocket.Recv(recv_buf, HEAD_LEN, g_para.bank_timeout);
    //ret = acpsocket.Recv(recv_buf, 2048, g_para.bank_timeout);
	//ret = acpsocket.Recv(recv_buf, sizeof(recv_buf), g_para.bank_timeout);
	acpsocket.Recv(recv_buf, sizeof(recv_buf), g_para.bank_timeout);
	ret=strlen(recv_buf);
	printf("\n recv_buf[%s] \n len[%d] ret[%d]\n",recv_buf,strlen(recv_buf),ret);
// 	if(ret != HEAD_LEN)
//     {
//         writelog(LOG_ERR,"接收银行数据包头错误\n");
//         return -1;
//     }
//     pack_len = atoi(recv_buf);
//     ret = acpsocket.Recv(recv_buf, pack_len, g_para.bank_timeout);
//     if(ret != pack_len)
//     {
//         writelog(LOG_ERR,"接收银行数据包体错误\n");
//         return -1;
//     }
 //   recv_buf[pack_len]=0;
    writelog(LOG_INFO,"len[%d],recv_buf[%s]\n",ret,recv_buf);
    ret = doResponse(recv_buf,strlen(recv_buf),send_buf,send_len);
    if(ret)
    {
        if(ret>0)
            return ret;
    }    
    
    send_buf[send_len]=0;
    writelog(LOG_INFO,"len[%d],send_buf[%s]\n",send_len,send_buf);
    printf("\n xxxxxxxxxxxxxxxxx \nsend_buf[%s]\nsend_len[%d]\n   xxxxxxxxxxxxxxxx\n",send_buf);
	ret = acpsocket.Send(send_buf,send_len);
	//ret = acpsocket.Send("1234",4);
	
/*
		int ret=0;
		int send_len=strlen(send_buf);
		char buf[2048]={0};
		ret=SockNode->Send(send_buf,send_len);
		if (ret<=0)
		{
			SockNode->Close();
			set_msg_log(szMsg,"发送数据至银行出错,错误代码[%d]\n",ret);
			return false;
		}

*/





   
	
	if(ret != send_len)
    {
        writelog(LOG_ERR,"发送数据错误\n");
        return -1;
    }
    return 0;
}