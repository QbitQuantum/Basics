int CTCPConnect::GetCustLevel(CString StrCardNum,CString strIP,CString strPort,UINT iOverTime)
{
    if (StartSocket(strPort,strIP))
    {
        char cCardNum[30];
        CCommonConvert::CStringToChar(StrCardNum,cCardNum);
        SocketPackage package = MakePackage(cCardNum);
        int size = sizeof(package);
        SendTo((char*)&package,sizeof(package));
        CString CardNum = _T("cardnum:")+StrCardNum;
        WriteLogWithTime(CardNum);
        char CardRecv[255];
        BOOL RecvTemp = FALSE;
        setsockopt(m_tSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&iOverTime,sizeof(UINT));
        if (!RecvFrom(CardRecv,255))
        {
            return -1;
        }
        int iLevel = GetLevel(CardRecv);

        //RecvFrom()
        CloseSocket();
        return iLevel;
    }
    else
    {
        CString strErr = _T("socket启动失败");
        return -1;
    }

}