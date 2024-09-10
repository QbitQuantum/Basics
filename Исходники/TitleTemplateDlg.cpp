void TitleTemplateDlg::OnBnClickedTitlesetInseretbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle == -1 )
	{
		MessageBoxW ( _T("please insert title firstly.")); 
		return ; 
	}
	

	CWnd *pWnd = this->GetDlgItem( IDC_TITLESET_INSERTCHAR ); 
	CString editText, nonEscape; 
	
	pWnd->GetWindowTextW(  editText ); 
	UINT pos = 0; 
	CString *title =  &  m_titleTemplate[m_curTitle]; 
	while ( pos < editText.GetLength() )
	{
		TCHAR textChar = editText.GetAt(pos ++); 
		switch ( textChar ) 
		{
		case _T('['):
		case _T('\\'):
		case _T('.'):
		case _T('+'):
		case _T('*'):
		case _T(']'):
			*title += _T('\\'); 
			*title +=  textChar ;
			break; 
		default:
			*title +=  textChar; 

		}
	}
	
	showTitle(); 
}