////////////////////////////////////////////////////////////////////////////////
//	函数名：INT RecvData(
//				SOCKET hSocket,
//				OUT CHAR *pszBuffer,
//				INT nBufferSize,
//				DWORD dwTimeout )
//	用  途：接收数据(阻塞直至收到数据为止)
//	对全局变量的影响：无
//	参  数：
//		hSocket     : 待接收数据的套接字
//		pszBuffer   : 缓冲区
//		nBufferSize : 缓冲区大小
//		dwTimeout   : 接收超时
//	返回值：INT
//		>=0			: 接收到的字节数
//		<0			: 失败(SOCKET_FAIL: -1)
////////////////////////////////////////////////////////////////////////////////
INT CBufSocket::RecvData(SOCKET hSocket, OUT CHAR *pszBuffer, INT nBufferSize, DWORD dwTimeout)
{
    HANDLE hReadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    if (hReadEvent == NULL)
    {
        SetLastError( (INT)GetLastError() );
        return ( SOCKET_FAIL );
    }

    INT		nRecvBytes = 0;
    DWORD	dwWaitResult;
    for (;;)
    {
        // 注册FD_READ | FD_CLOSE 事件
        // (因为可能在等待FD_READ事件中，对方关闭套接字，所以要关注FD_CLOSE)
        if( WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, FD_READ | FD_CLOSE) == SOCKET_ERROR)
        {
            CloseHandle(hReadEvent);
            SetLastError( WSAGetLastError() );
            return (SOCKET_FAIL);
        }

        // 等等FD_READ | FD_CLOSE事件的发生
        //dwWaitResult = WSAWaitForMultipleEvents(1, &hReadEvent, TRUE,dwTimeout, TRUE);

        //seawind
        DWORD dwBeginTime = GetTickCount();
        BOOL bDataCome = FALSE;

        while(GetTickCount() - dwBeginTime < dwTimeout)
        {
            //和HttpDownload,FtpDownload类共享一个Event Handle
            if (m_hStopEvent != NULL && (WaitForSingleObject(m_hStopEvent, 0) == WAIT_OBJECT_0))
            {
                //要赶快跳走，用户点了Stop

                CloseHandle(hReadEvent);
                SetLastError( WSAGetLastError() );
                return (SOCKET_FAIL);

                //break;
            }

            dwWaitResult = WSAWaitForMultipleEvents(1, &hReadEvent, TRUE, 0, TRUE);

            if (dwWaitResult == WSA_WAIT_EVENT_0)
            {
                //数据来啦
                bDataCome = TRUE;
                break;
            }

            //空出CPU时间
            Sleep(DEFAULT_BLOCKED_SNDRCV_SLEEP);
        }

        //if (dwWaitResult != WSA_WAIT_EVENT_0)
        if (!bDataCome)
        {
            // 清除事件
            WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
            CloseHandle(hReadEvent);
            SetLastError( WSAGetLastError() );
            return (SOCKET_FAIL);
        }

        //////////////////////////////////////////////////////////////
        ///	注意：即使 dwWaitResult == WSA_WAIT_EVENT0 ，也应该
        ///			进一步检查网络是否发生错误
        ///////////////////////////////////////////////////////////////
        WSANETWORKEVENTS NetEvent;
        if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hReadEvent,&NetEvent) == SOCKET_ERROR)
        {
            // 清除事件
            WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
            CloseHandle(hReadEvent);
            SetLastError( WSAGetLastError() );
            return (SOCKET_FAIL);
        }

        //判断发生了什么事件 FD_READ 或 FD_CLOSE
        if( ( NetEvent.lNetworkEvents == FD_CLOSE ) ||
                ( NetEvent.lNetworkEvents	== FD_READ &&
                  NetEvent.iErrorCode[FD_READ_BIT] !=0 ) )	// 发生错误
        {
            // 清除事件
            WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
            CloseHandle(hReadEvent);
            SetLastError(WSAGetLastError() );
            return (SOCKET_FAIL);
        }
        ////////////////////////////////////////////////////////////////
        // 清除事件
        WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);

        // 接收数据
        if ((nRecvBytes = RecvOnce(hSocket, pszBuffer, nBufferSize)) >= 0)
            break;	// 跳出循环

        INT nErrorCode = -nRecvBytes;

        if ( nErrorCode != WSAEWOULDBLOCK )	//太多的未完成重叠操作
        {
            CloseHandle(hReadEvent);
            SetLastError( nErrorCode );
            return (SOCKET_FAIL);
        }

        //阻塞住了
        ////////////////////////////////////////////////////////////////////////
        //  如果发生阻塞,就等待一定时间后重试,以免CPU轮询浪费时间
        ////////////////////////////////////////////////////////////////////////
        Sleep(DEFAULT_BLOCKED_SNDRCV_SLEEP);
    }

    CloseHandle(hReadEvent);
    return (nRecvBytes);
}