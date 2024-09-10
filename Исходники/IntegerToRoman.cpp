void IntegerToRoman::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString source;
	GetDlgItem(IDC_EDIT2)->GetWindowTextA(source);
	//文本内容保存在source变量中
	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(source));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}
}