void CDJMasterDlg::OnDropFiles(HDROP hDropInfo)
{
	UINT unFileCount;            
	WCHAR szFilePath[200];              
	unFileCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);   //系统的API函数         
	for( UINT i=0;i < unFileCount;i++)             
	{  
		int pathLen = DragQueryFileW(hDropInfo, i, szFilePath, _countof(szFilePath));  //API函数 

		AddMusicFile(szFilePath);

	}
	DragFinish(hDropInfo);   //API函数

	CDialog::OnDropFiles(hDropInfo);
}