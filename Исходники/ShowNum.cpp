UINT CShowNum::GetNum( int nID )
{	
	UpdateData(TRUE);
	return	GetDlgItemInt( nID, NULL, FALSE );
}