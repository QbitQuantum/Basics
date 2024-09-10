//线程静态函数
DWORD WINAPI CCommClient::StaticThreadFunc(LPVOID lpParam)
{
    CCommClient *pChannel = (CCommClient*)lpParam;
    SOCKET ClientSocket = pChannel->m_socket;

    int bytesRecv = SOCKET_ERROR;
    TCHAR recvbuf[8192] = {0};	//接收区
    DWORD dwPackteCount = 0;
    TCHAR *pDataBuff = NULL;	//缓冲区
    DWORD dwDataBuffLen = 0;	//缓冲区长度

    if(ClientSocket==NULL)
    {
        return 0;
    }
    while(!pChannel->StopIsSet())
    {
        bytesRecv = recv( ClientSocket, (char*)recvbuf, 8192, 0 );

        if( bytesRecv <= 0 )	//服务端断开连接 等待连接
        {
            g_commLog.Trace(LOGL_TOP,LOGT_PROMPT, __TFILE__,__LINE__, _T("服务器断开连接 err:%d"), WSAGetLastError());
            //这里崩溃，主动关闭内核的时候
            pChannel->m_pfnDataHandler(_T("DISCONNECT"),10);

            ClientSocket = NULL;
            return 0;
        }

#ifdef _UNICODE
        bytesRecv /= 2;  //UNICODE下收到的字符数为字节数/2
        if(pDataBuff == NULL)
        {
            pDataBuff = new TCHAR[bytesRecv];
            wmemcpy(pDataBuff,recvbuf,bytesRecv);
            dwDataBuffLen = bytesRecv;
        }
        else
        {
            TCHAR *tmpBuff = new TCHAR[dwDataBuffLen];
            wmemcpy(tmpBuff,pDataBuff,dwDataBuffLen);

            delete []pDataBuff;

            pDataBuff = new TCHAR[dwDataBuffLen + bytesRecv];

            wmemcpy(pDataBuff,tmpBuff,dwDataBuffLen);
            delete []tmpBuff;

            wmemcpy(&(pDataBuff[dwDataBuffLen]),recvbuf,bytesRecv);
            dwDataBuffLen += bytesRecv;
        }

        //包处理
        if(dwDataBuffLen<sizeof(DWORD)*2)continue; //小于最小包头不做如下处理

        DWORD dwPacketSize = 0; //包大小
        while(TRUE)
        {
            if(dwDataBuffLen == 0)break; //缓冲区没有数据
            memcpy(&dwPacketSize,pDataBuff,sizeof(DWORD));
            dwPacketSize /= 2;       //UNICODE下接收到包的实际长度为收到的字符数*2
            if(dwPacketSize > dwDataBuffLen)
                break; //包长度大于缓冲区长度不做处理

            TCHAR *pData = new TCHAR[dwPacketSize];	//拼一个包
            wmemcpy(pData,pDataBuff + 4,dwPacketSize - 4);

            pChannel->m_pfnDataHandler(pData,dwPacketSize - 4);
            delete []pData;

            TCHAR *tmpBuff = new TCHAR[dwDataBuffLen];
            wmemcpy(tmpBuff,pDataBuff,dwDataBuffLen);

            delete []pDataBuff;
            pDataBuff = NULL;

            dwDataBuffLen = dwDataBuffLen - dwPacketSize;
            pDataBuff = new TCHAR[dwDataBuffLen];
            wmemcpy(pDataBuff,&(tmpBuff[dwPacketSize]),dwDataBuffLen);
            delete []tmpBuff;
            dwPackteCount ++ ; //包计数器
        }

        printf("总共收到数据包 %d\n",dwPackteCount); //包计数器
        //Sleep(200);	//线程切换
    }
#else
        if(pDataBuff == NULL)
        {
            pDataBuff = new TCHAR[bytesRecv];
            memcpy(pDataBuff,recvbuf,bytesRecv);
            dwDataBuffLen = bytesRecv;
        }
        else
        {
            TCHAR *tmpBuff = new TCHAR[dwDataBuffLen];
            memcpy(tmpBuff,pDataBuff,dwDataBuffLen);

            delete []pDataBuff;

            pDataBuff = new TCHAR[dwDataBuffLen + bytesRecv];

            memcpy(pDataBuff,tmpBuff,dwDataBuffLen);
            delete []tmpBuff;

            memcpy(&(pDataBuff[dwDataBuffLen]),recvbuf,bytesRecv);
            dwDataBuffLen += bytesRecv;
        }

        //包处理
        if(dwDataBuffLen<sizeof(DWORD)*2)continue; //小于最小包头不做如下处理

        DWORD dwPacketSize = 0; //包大小
        while(TRUE)
        {
            //if(dwDataBuffLen == 0)break; //缓冲区没有数据
            memcpy((WCHAR*)&dwPacketSize,pDataBuff,sizeof(DWORD));
            if(dwPacketSize > dwDataBuffLen)
                break; //包长度大于缓冲区长度不做处理

            TCHAR *pData = new TCHAR[dwPacketSize];	//拼一个包
            memcpy(pData,pDataBuff + 4,dwPacketSize);

            pChannel->m_pfnDataHandler(pData,dwPacketSize);
            delete []pData;

            TCHAR *tmpBuff = new TCHAR[dwDataBuffLen];
            memcpy(tmpBuff,pDataBuff,dwDataBuffLen);

            delete []pDataBuff;
            pDataBuff = NULL;

            dwDataBuffLen = dwDataBuffLen - dwPacketSize;
            pDataBuff = new TCHAR[dwDataBuffLen];
            memcpy(pDataBuff,&(tmpBuff[dwPacketSize]),dwDataBuffLen);
            delete []tmpBuff;
            dwPackteCount ++ ; //包计数器
        }

        printf("总共收到数据包 %d\n",dwPackteCount); //包计数器
        //Sleep(200);	//线程切换
    }