void CViewer2Dlg::OnDropFiles(HDROP hDropInfo)
{
	HDROP hdrop = hDropInfo;
	char filePath[ MAX_PATH];
	const UINT size = DragQueryFileA(hdrop, 0, filePath, MAX_PATH);
	if (size == 0) 
		return;// handle error...

	m_pView->LoadModel(filePath);

	wstring wstr = common::str2wstr(filePath);
	CString str = wstr.c_str();
	m_FileList.InsertItem(m_FileList.GetItemCount(), str);

	CDialogEx::OnDropFiles(hDropInfo);
}