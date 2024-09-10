// 写数据
DWORD CMySerialPort::WriteData(unsigned char* sbuf, DWORD sendlen)
{
    DWORD dwBytesWritten = sendlen;
    DWORD dwErrorFlags;
    COMSTAT comStat;

    // 检查是否要关闭串口
    if (m_bClosePort)
    {
        ClosePort();
        return 0;
    }

    if (false == PeerIsValid())
    {
        LOG.err_log("请设置有效的目的串口!");
        return -1;
    }

    if (0 >= sendlen)
    {
        LOG.err_log("要发送的字节数必须大于0");
    }

    BOOL bWriteStat = FALSE; // 发送状态
    DWORD dwWritedLen = 0; // 实际发送的字节数
    DWORD dwTotalWrited = 0; // 累计已发送的字节总数

    while(dwBytesWritten > 0)
    {
        ClearCommError(m_peerHandle, &dwErrorFlags,&comStat);

        bWriteStat = WriteFile(m_peerHandle, sbuf + dwTotalWrited, dwBytesWritten,
            &dwWritedLen, NULL);

        if(!bWriteStat)
        {
            LOG.warn_log("写串口[%s]失败!", (LPCSTR)m_strComName);
            return sendlen - dwBytesWritten;
        }

        dwBytesWritten -= dwWritedLen;
        dwWritedLen += dwWritedLen;
    }
    //PurgeComm(m_portHandle, PURGE_TXABORT|
    //    PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
    return sendlen - dwBytesWritten;
}