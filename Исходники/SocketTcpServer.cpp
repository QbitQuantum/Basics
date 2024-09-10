void CSocketTcpServer::SendMsg(CString msg)
{
    char buf[MAX_BUFFER]= {0};
    m_convert.CStringToChar(msg,buf);
    for(int i=0; i<m_index; i++)
    {
        m_ol[i]->nOpType = OP_WRITE;
        memset(&m_ol[i]->ol, 0, sizeof(m_ol[i]->ol));
        strcpy_s(m_ol[i]->szBuf,MAX_BUFFER,buf);
        m_ol[i]->wsaBuf.buf=m_ol[i]->szBuf;
        m_ol[i]->wsaBuf.len = MAX_BUFFER;
        if(SOCKET_ERROR==WSASend(m_ol[i]->sock,&(m_ol[i]->wsaBuf), 1,
                                 &(m_ol[i]->dwTrans), m_ol[i]->dwFlags,
                                 &(m_ol[i]->ol), CompleteRoutine))
        {
#ifdef _DEBUG
            CString ipAddress;
            m_convert.CharToCstring(ipAddress,inet_ntoa(m_ol[i]->addr.sin_addr));
            CString errcode;
            errcode.AppendFormat(_T("client %s socket broken"),ipAddress);
            MyWriteConsole(ipAddress);
#endif
        }
    }
}