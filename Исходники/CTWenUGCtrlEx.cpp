void CTWenUGCtrlEx::OnSetup(void)
{
	CFont * pcFont = GetFont(m_nFontID_Content); 

	CUGCell	cell;
	GetGridDefault(&cell); 
	cell.SetTextColor(RGB(0,0,0)); 
	cell.SetFont(pcFont);
	cell.SetReadOnly(true);
	SetGridDefault(&cell); 

	CString AppPath = CApplication::GetApplicationPath();
	AppPath += _T('\\');


	m_nIndexBMP_Delete		= AddBitmap(AppPath + _T("_Action_Delete.bmp"));
	m_nIndexBMP_INF			= AddBitmap(AppPath + _T("_Action_Info.bmp"));
	m_nIndexBMP_Add			= AddBitmap(AppPath + _T("_Action_Add.bmp"));

	CString s;
	if(m_nIndexBMP_Delete<0)
		s += (_T("\r\n") + AppPath + _T("_Action_Delete.bmp"));
	if(m_nIndexBMP_INF<0) 
		s += (_T("\r\n") + AppPath + _T("_Action_Info.bmp"));
	if(m_nIndexBMP_Add<0) 
		s += (_T("\r\n") + AppPath + _T("_Action_Add.bmp"));
	if(!s.IsEmpty()) AfxMessageBox(_T("以下图片未能加载：") + s);
}