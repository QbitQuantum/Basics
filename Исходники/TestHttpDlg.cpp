int CTestHttpDlg::ThreadFunc()
{
	//CFileDialog FileDlg(FALSE);
    
	CHttpSocket sock;
		
	
    BOOL IFOK = FALSE;

	IFOK = sock.Socket();    
    if(!IFOK)
    {
        ASSERT(FALSE);
        return 0;
    }

	sock.SetTimeout(10,0);
	IFOK = sock.Connect((LPTSTR)(LPCTSTR)m_strServer, m_port);
    if(!IFOK)
    {
        ASSERT(FALSE);
        return 0;
    }

    //set reqestheader
    string strsend = m_strRequest;      
    sock.SetRequest(strsend);
    
    //sock.SendRequest(strsend.c_str(), strsend.length() );
    sock.SendRequest( );

	int nLineSize = 0;

	char szLine[256+1];
    memset(szLine, 0, 256+1);

    m_ctrlList.ResetContent();
	while(nLineSize != -1)
	{
		nLineSize = sock.GetResponseLine(szLine,256);
		if(nLineSize > -1)
		{
			szLine[nLineSize] = '\0';
			m_ctrlList.AddString(szLine);
		}
	}
	//char szValue[30];
	//HttpSocket.GetField("Content-Length",szValue,30);
    
    string strContent = sock.GetContent();
    int pos = strContent.find("[");    
    string strJson = strContent.substr(pos + 1, strContent.length()-2 );
    int nFileSize = strContent.length();

    if(strJson.length() ){
        //JSONNode* node = (JSONNode*)json_parse(strJson.c_str() );
        //if(!node)
        //    return 0;
        //char jsontype = json_type(node);
        //if(JSON_NODE == jsontype)
        //{}
        //int nodesize = json_size(node);
        //json_char * res = json_as_string(json_at(node, 0));
    }
    //bool ifok = HttpSocket.GetContentLength(nFileSize);
	int nSvrState = sock.GetServerState();
	//int nFileSize = atoi(szValue);
	m_ctrlProgress.ShowWindow(SW_SHOW);
	m_ctrlProgress.SetRange(0,nFileSize / 1024);
	
	
    //bool ifwriteok = this->WriteFile(sock, nFileSize);
	
	m_ctrlProgress.ShowWindow(SW_HIDE);
	m_ctrlProgress.SetPos(0);

    string sdf;
    sdf.push_back('d');

    sock.CloseSocket();

	return 0;
}