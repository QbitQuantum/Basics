//发送数据
void CSerialSampleDlg::OnBnClickedBtnSend()
{
	char * buf  =NULL;  //定义发送缓冲区
	DWORD dwBufLen = 0;   //定义发送缓冲区长度
	CString strSend = L"";

	//得到发送输入框
	CEdit *pEdtSendMsg = (CEdit*)GetDlgItem(IDC_EDT_SEND);
	ASSERT(pEdtSendMsg != NULL);

	//串口如果没有打开，直接返回
	if (m_pSerial == NULL)
	{
		AfxMessageBox(L"串口未打开");
		return;
	}

	//得到待发送的字符串
	pEdtSendMsg->GetWindowTextW(strSend);

	//将待发送的字符串转换成单字节，进行发送
	buf = new char[strSend.GetLength()*2+1];
	ZeroMemory(buf,strSend.GetLength()*2+1);
	//转换成单字节进行发送	
	WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strSend.GetBuffer(strSend.GetLength())
	   ,strSend.GetLength(),buf,strSend.GetLength()*2,NULL,NULL);

	dwBufLen = strlen(buf) + 1;
	//发送字符串
	m_pSerial->WriteSyncPort((BYTE*)buf,dwBufLen);

	//释放内存
	delete[] buf;
	buf = NULL;
}