int doProcess(CTcpSocket &acpsocket)
{
	
	int ret = 0;
    int send_len = 0;
    char recv_buf[4096] = "";
    char send_buf[4096] = "";
	acpsocket.Recv(recv_buf, sizeof(recv_buf), g_para.bank_timeout);
	ret=strlen(recv_buf);
    writelog(LOG_INFO,"len[%d],recv_buf[%s]\n",ret,recv_buf);
    ret = doResponse(recv_buf,strlen(recv_buf),send_buf,send_len);
    if(ret)
    {
        if(ret>0)
            return ret;
    }    
    
    send_buf[send_len]=0;
    writelog(LOG_INFO,"len[%d],send_buf[%s]\n",send_len,send_buf);
	ret = acpsocket.Send(send_buf,send_len);
	if(ret != send_len)
    {
        writelog(LOG_ERR,"发送数据错误\n");
        return -1;
    }
    return 0;
}