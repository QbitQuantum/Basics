BOOL CWndMessageBox::IsDisable( )
{
	CWndButton * pWndButton = (CWndButton*)GetDlgItem(IDOK);
	if( pWndButton && pWndButton->IsWindowEnabled( ) )
		return TRUE;

	return FALSE;
}