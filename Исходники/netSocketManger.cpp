//接收数据线程
void netSocketManger::reciveThread()
{
    char buff[MAX_BUFF];
    int recv_len = 0;
    bool hasMorePackets = false;
 
    while(true)
    {
        
        if( !hasMorePackets ) {
            
            int ret = cSocket.Recv(buff, MAX_BUFF - recv_len, 0);
            
            if (ret <= 0) {
                isConnect = false;
                SocketData *errorData = newSocketData();
                errorData->eventType = DISCONNECT;
                m_mainQueue.Push(errorData);
                break;
            }
            if(ret < 1)
                break;
        }
       
            T_MSGHEAD_T reciveCmd;
            reciveCmd.len = 1;        //接收缓存中的前64个字节数据
            reciveCmd.enc = 0;        //数据是否加密标志
            reciveCmd.com = 0;        //数据是否压缩标志，这两个我们都设置为否，因为我们的数据本身只有一位
            reciveCmd.idx = (uInt)m_sn;      //包索引也设置为固定值，因为我们只有一个接口，这里发arduino马上就会回.
            reciveCmd.tea = 0;
            unsigned int pos = 0;
            
            SocketData *data = newSocketData();
            data->module.cmd = 100;   //先将100设置为灯的协议号
            data->module.eno = 0;     //主动将错误码设置为0,即正常
            data->eventType = RESPONSE;
            data->sn = reciveCmd.idx;
            std::string datax(&buff[pos],reciveCmd.len);
            data->body = std::string(datax);
            pos += reciveCmd.len;
            data->bodyLen = reciveCmd.len;
        
        log("接收:%s",data->body.c_str());
            log("*************************************************");
            log("*************************************************");
            
            m_mainQueue.Push(data);
            
            hasMorePackets = false;
        
    }
    
}