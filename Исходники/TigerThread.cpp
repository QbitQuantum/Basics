void* TigerThread::thread_funcation(void *arg)
{
    ODSocket *pSocket = ODSocket::sharedODSocket();
    pSocket->Init();
    pSocket->Create(AF_INET, SOCK_STREAM,0);
    
    /*
     /////////////////////////////////////////////
     char ipaddr[20];
     cSocket.DnsParse("www.baidu.com", ipaddr);
     //192.168.22.154
     //aliyun-027.btcsky.com
     /////////////////////////////////////////////--DNS解析 www->ip
     */
    
    if (pSocket->Connect("58.83.190.220", 6621)) {
        char recvBuf[1024] = "\0";
        // std::string testmsg= |login|[email protected],e10adc3949ba59abbe56e057f20f883e,68:A8:6D:10:66:DC|$\r\n
        std::string testmsg= pSocket->msg_To_Sever;
        pSocket->Send(testmsg.data(),testmsg.length(),0);
        pSocket->Recv(recvBuf,1024,0);
        std::string rec_msg=std::string(recvBuf);
        printf("%s",rec_msg.c_str());
    }
    else
    {
        CCLog("服务器连接失败");
    }
    pSocket->Close();
    pSocket->Clean();
    return NULL;

}