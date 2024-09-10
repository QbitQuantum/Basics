/**
@fn void set_frame_head_and_tail(m_oCommFrameStruct& frame)
@detail 填写数据包头尾信息
@param[in]	frame	数据包头
@return void
@note
*/
BOOL line_socket::Create(UINT nSocketPort, int nSocketType,LPCTSTR lpszSocketAddress)
{
    BOOL b_ret = TRUE;

    if(lpszSocketAddress != NULL)	ip_.Format(__TEXT("%s"), lpszSocketAddress);
    if(nSocketPort != 0) port_ = nSocketPort;

    b_ret = CAsyncSocket::Create(0x0,	nSocketType, 	FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE,  NULL);

    //设置接受缓冲
    int iOptionValue = recv_buff_size_ != 0 ?recv_buff_size_ : CURRENT_RECVBUF_SIZE;
    int iOptionLen = sizeof(int);
    SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

    //设置发送缓冲为0
    iOptionValue = 0;
    iOptionLen = sizeof(int);
    SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

    if(b_ret) {
        recv_proc_thread_ = AfxBeginThread(recv_processing_thread_proc, this);
        check_timeout_thread_ = AfxBeginThread(check_timeout_thread_proc, this);
        send_proc_thread_ = AfxBeginThread(send_processing_thread_proc, this);
        if(recv_proc_thread_ == NULL || check_timeout_thread_ == NULL || send_proc_thread_ == NULL) {
            Close();
            b_ret = FALSE;
        }
    }

    return b_ret;
}