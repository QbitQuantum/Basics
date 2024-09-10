void CDlgForbidenIP::OnBnClickedButton1()
{
    //添加封禁
    char szIP[20]      = {'\0'};
    char szSeconds[20] = {'\0'};
    CString strIP;
    CString strSeconds;
    int     nType = 0;

    m_txtForbidenIP.GetWindowText(strIP);

    int nSrcLen = WideCharToMultiByte(CP_ACP, 0, strIP, strIP.GetLength(), NULL, 0, NULL, NULL);
    int nDecLen = WideCharToMultiByte(CP_ACP, 0, strIP, nSrcLen, szIP, 20, NULL,NULL);
    szIP[nDecLen] = '\0';

    nSrcLen = WideCharToMultiByte(CP_ACP, 0, strSeconds, strSeconds.GetLength(), NULL, 0, NULL, NULL);
    nDecLen = WideCharToMultiByte(CP_ACP, 0, strSeconds, nSrcLen, szSeconds, 20, NULL,NULL);
    szSeconds[nDecLen] = '\0';

    if(strlen(szIP) == 0)
    {
        MessageBox(_T(MESSAGE_INSERT_NULL) , _T(MESSAGE_TITLE_ERROR), MB_OK);
        return;
    }

    switch(GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2))
    {
    case IDC_RADIO1:
        nType = 0;
        break;
    case IDC_RADIO2:
        nType = 0;
        break;
    }

    char szSendMessage[200] = {'\0'};
    char szCommand[100]     = {'\0'};
    sprintf_s(szCommand, 100, "%s ForbiddenIP -c %s -t %d -s %s ", m_pTcpClientConnect->GetKey(), szIP, nType, szSeconds);
    int nSendLen = (int)strlen(szCommand);

    memcpy_s(szSendMessage, 200, &nSendLen, sizeof(int));
    memcpy_s(&szSendMessage[4], 200, &szCommand, nSendLen);

    char szRecvBuff[10 * 1024] = {'\0'};
    int nRecvLen = 10 * 1024;
    bool blState = m_pTcpClientConnect->SendConsoleMessage(szSendMessage, nSendLen + sizeof(int), (char*)szRecvBuff, nRecvLen);
    if(blState == false)
    {
        MessageBox(_T(MESSAGE_SENDERROR) , _T(MESSAGE_TITLE_ERROR), MB_OK);
    }
    else
    {
        int nStrLen      = 0;
        int nPos         = 4;
        int nResult      = 0;
        memcpy_s(&nResult, sizeof(int), &szRecvBuff[nPos], sizeof(int));
        nPos += sizeof(int);

        if(nResult == 0)
        {
            MessageBox(_T(MESSAGE_RESULT_SUCCESS) , _T(MESSAGE_TITLE_ERROR), MB_OK);
        }
        else
        {
            MessageBox(_T(MESSAGE_RESULT_FAIL) , _T(MESSAGE_TITLE_SUCCESS), MB_OK);
            OnBnClickedButton3();
        }
    }
}