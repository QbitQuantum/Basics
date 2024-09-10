// 显示GPS串口接收的数据
LONG CGPSDemoDlg::OnRecvSerialData(WPARAM wParam,LPARAM lParam)
{
	//得到原始数据
	char * aRecv = (char *)wParam;
	
	CString strRecv = L"";
	CString strRecv1 = L"";
	//
	CEdit *pEdtRecv = (CEdit*)GetDlgItem(IDC_EDT_RECV);

	//得到接收框原来的文本
	pEdtRecv->GetWindowTextW(strRecv1);
	strRecv = CString(aRecv);
	//追加新接收到的文本
	pEdtRecv->SetWindowTextW(strRecv1+strRecv);
	
	//释放内存
	delete[] aRecv;
	aRecv = NULL;
	return 0;

}