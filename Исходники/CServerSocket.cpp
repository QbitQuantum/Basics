/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions
void CServerSocket::OnReceive(int nErrorCode)
{
	CString host,ip;UINT port;
	CString buf,text;
	CString _fileName;
	Receive(buf.GetBuffer(2056),2056);
	buf.ReleaseBuffer();
	GetPeerName(ip,port);


	if(buf.Find("<?Response FILETRANSFER?>:ACCEPT")>-1)
	{
		//AfxMessageBox("对方同意接收");
		file.Open(filePath,CFile::modeRead|CFile::typeBinary,NULL);
		remainder=file.GetLength();
		CString csRemainder;
		csRemainder.Format("%u",remainder);
		if (!fileTran)
		{
			CSendFileDlg *sfDlg=new CSendFileDlg(SOCKETTYPESERVER,this);
			sfDlg->Create(IDD_SENDFILE_DIALOG,CWnd::FromHandle(::GetDesktopWindow()));
			fileTran=sfDlg;
			fileTran->ShowWindow(SW_SHOW);
		}
		fileTran->SetDlgItemText(IDC_STATIC_SRCA,localIp);
		fileTran->SetDlgItemText(IDC_STATIC_DESA,thePeerIp);
		fileTran->SetDlgItemText(IDC_STATIC_FINFO,fileName+"\n大小: "+csRemainder+" 字节");
		CProgressCtrl *proSF=(CProgressCtrl*)fileTran->GetDlgItem(IDC_PROGRESS_TRANFILE);
		proSF->SetRange32(0,remainder);
		proSF->SetPos(0);


		TransferFile(filePath);
		return;
	}
	else if (buf.Find("<?Response FILETRANSFER?>:REFUSE")>-1)
	{
		AfxMessageBox("对方不同意接收该文件.",MB_ICONWARNING);
		return;
	}
	else if (buf.Find("<?FileContinue?>")>-1)
	{
		if (remainder<=0)
		{
			if (tag==0)
			{
				return;
			}
			tag=0;
			Send("<?FileStop?>",256);
			file.Close();
			AfxMessageBox("发送已完成.",MB_ICONINFORMATION);
			tag=1;
		}
		else
		{
			TransferFile(filePath);
		}
		return;
	}
	else{}


	CRichEditCtrl *m_RichEdit1;
	pcwnd=AfxGetApp()->GetMainWnd();
	m_RichEdit1=(CRichEditCtrl*)pcwnd->GetDlgItem(IDC_RICHEDIT_CONTENT);
	SOCKADDR_IN addrFrom;
	int len=sizeof(SOCKADDR);
	CString msg;
	HOSTENT *pHost;
	DWORD lineCount=m_RichEdit1->GetLineCount();

	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE |
		CFM_ITALIC | CFM_SIZE | CFM_UNDERLINE;
	cf.dwEffects = 0;
	cf.yHeight = 15*15;//文字高度
	cf.crTextColor = RGB(255, 0, 0); //文字颜色
	strcpy(cf.szFaceName ,_T("宋体"));//设置字体
	m_RichEdit1->SetDefaultCharFormat(cf);
	m_RichEdit1->SetBackgroundColor(FALSE,RGB(255,255,255));
	
	//ReceiveFrom(buf.GetBuffer(2056),2056,(SOCKADDR*)&addrFrom,&len);

	DWORD peerIP=inet_addr(ip.GetBuffer(0));  
	pHost=gethostbyaddr((LPSTR)&peerIP,4,AF_INET); 

	int pos=buf.GetLength();
	buf=buf.Right(pos-13);

	CTime time=CTime::GetCurrentTime();
	CString currentTime;
	currentTime.Format("          %02d:%02d:%02d",time.GetHour(),time.GetMinute(),time.GetSecond());
	
	host.Format("%s%s",pHost->h_name,currentTime);
	msg.Format("  \r\n  %s\r\n",buf);

	cf.yHeight = 13*13;//文字高度
	cf.crTextColor = RGB(0,110,254); //文字颜色
	strcpy(cf.szFaceName ,_T("微软雅黑"));//设置字体
	m_RichEdit1->SetSel(m_RichEdit1->GetTextLength(),m_RichEdit1->GetTextLength());
	m_RichEdit1->ReplaceSel(host);
	m_RichEdit1->SetSel(m_RichEdit1->GetTextLength()-host.GetLength(),m_RichEdit1->GetTextLength());
	m_RichEdit1->SetSelectionCharFormat(cf);
	
	m_RichEdit1->SetSel(-1,-1);
	m_RichEdit1->ReplaceSel(msg);
	cf.yHeight = 14*14;//文字高度
	cf.crTextColor = RGB(204,0,204); //文字颜色
	strcpy(cf.szFaceName ,_T("微软雅黑"));//设置字体
	m_RichEdit1->SetSel(m_RichEdit1->GetTextLength()-msg.GetLength(),m_RichEdit1->GetTextLength());
	m_RichEdit1->SetSelectionCharFormat(cf);
	m_RichEdit1->LineScroll(m_RichEdit1->GetLineCount()-lineCount);
	m_RichEdit1->SetSel(0,0);

	CAsyncSocket::OnReceive(nErrorCode);
}