BOOL CStaffSetDlg::ShowPhoto(const CString& strPhotoPath, CWnd* pWnd)
{
	
	POSITION pos=m_ListCtr_Staff.GetFirstSelectedItemPosition();
	int index=m_ListCtr_Staff.GetNextSelectedItem(pos);
	SLZStaff staffinfo=m_List_StaffInfo.GetAt(m_List_StaffInfo.FindIndex(index));
	CStatic* picPhoto = (CStatic*)pWnd;
	CDC* pDC = picPhoto->GetWindowDC();
	CRect rect;
	picPhoto->GetClientRect(&rect);
	CImage img;
	if(strPhotoPath.IsEmpty())
	{
		pDC->SelectStockObject(GRAY_BRUSH);
		pDC->FillRect(	
			&rect, pDC->GetCurrentBrush());
		UpdateData(FALSE);
		return FALSE;
	}
	HRESULT hResult = img.Load(strPhotoPath);
	if(FAILED(hResult))
	{
		MessageBox(_T("图片路径错误，导入失败"));
		staffinfo.SetStaffPhoto(_T(""));
		m_ListCtr_Staff.SetItemText(index,4,_T("未配置"));
		m_List_StaffInfo.GetAt(m_List_StaffInfo.FindIndex(index))=staffinfo;
		return FALSE;
	}
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	img.Draw(pDC->m_hDC, 0, 0, rect.Width(), rect.Height(), 0, 0, img.GetWidth(), img.GetHeight());
	//把图片填充在控件中
	return TRUE;
}