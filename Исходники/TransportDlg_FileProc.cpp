/**	@fn	void CTransportDlg::OnDropFiles(HDROP hDropInfo)
 *	@brief	拖拉文件至主窗口，启动文件发送线程发送文件
 *	@param hDropInfo 系统定义.
 */
void CTransportDlg::OnDropFiles(HDROP hDropInfo)
{
	char *filename = new char[100];
	int count = ::DragQueryFile(hDropInfo, 0xffffffff, NULL, 512);	//get count of dropped files

	for (int i = 0; i < count; i++)
	{
		//get filename
		int nchar = DragQueryFile(hDropInfo, i, filename, 512);

		SENDPROCPARAM *pSendFileProcParam = new SENDPROCPARAM;
		pSendFileProcParam->dwIPOpposite = m_dwIPOpposite;
		pSendFileProcParam->iPort = SERVERPORT;
		pSendFileProcParam->hMainWnd = m_hWnd;
		pSendFileProcParam->strFileName = filename;
		pSendFileProcParam->piProcess = &m_iProcess;

		HANDLE hSendFileThread = CreateThread(NULL, 0, SendFileProc, (LPVOID)pSendFileProcParam, 0, NULL);
		CloseHandle(hSendFileThread);		//close this handle to release its counter

	}

	DragFinish(hDropInfo);
	delete[] filename;

	CDialog::OnDropFiles(hDropInfo);
}