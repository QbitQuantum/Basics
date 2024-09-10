int doProcess(CTcpSocket &acpsocket)
{
    int ret = 0;
    int pack_len = 0;
    int send_len = 0;
    char recv_buf[256] = "";
    char send_buf[256] = "";
    ret = acpsocket.Recv(recv_buf, HEAD_LEN, g_para.bank_timeout);
    if(ret != HEAD_LEN)
    {
        writelog(LOG_ERR,"接收银行数据包头错误\n");
        return -1;
    }
    pack_len = atoi(recv_buf);
    ret = acpsocket.Recv(recv_buf, pack_len, g_para.bank_timeout);
    if(ret != pack_len)
    {
        writelog(LOG_ERR,"接收银行数据包体错误\n");
        return -1;
    }
	recv_buf[pack_len]=0;
    writelog(LOG_INFO,"len[%d],recv_buf[%s]\n",ret,recv_buf);
    ret = doResponse(recv_buf,pack_len,send_buf,send_len);
    if(ret)
    {
        if(ret>0)
            return ret;
    }    
    
    send_buf[send_len]=0;
    writelog(LOG_INFO,"len[%d],send_buf[%s]\n",strlen(send_buf),send_buf);
    ret = acpsocket.Send(send_buf,send_len);
    if(ret != send_len)
    {
        writelog(LOG_ERR,"发送数据错误\n");
        return -1;
    }
    return 0;
}