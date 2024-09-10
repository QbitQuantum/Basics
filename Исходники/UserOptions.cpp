void CUserOptions::addToolTip( int no, int id, CString str )
{
  CWnd* wnd = GetDlgItem( id );
  CRect rect; 
  wnd->GetClientRect( rect );
  m_tToolTip[no].Create( wnd );
  m_tToolTip[no].AddTool( wnd, str, rect, TOOLTIP_ID );
}