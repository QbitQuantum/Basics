void CTreepadView::OnFileSaveAs()
{
	if (!tree.size()) {
		return;
	}
	BOOL isOpen = FALSE;
	CString defaultDir = L"D:\\Treepad\\Iteration";
	CString filter = L"PNG File (*.png)||";
	CString fileName = L"image1.png";         //默认打开的文件名
	CFileDialog openFileDlg(isOpen, L"png", fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		CRect rcBk;
		GetClientRect(&rcBk);
		CDC* pDC = GetDC();
		CImage Image;
		Image.Create(rcBk.Width(), rcBk.Height(), 24);
		::BitBlt(Image.GetDC(), 0, 0, rcBk.Width(), rcBk.Height(), pDC->m_hDC, 0, 0, SRCCOPY);
		Image.Save(filePath);
		Image.ReleaseDC();
		Image.Destroy();
	}
	// TODO: 在此添加命令处理程序代码
}