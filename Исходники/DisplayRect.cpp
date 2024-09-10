BOOL CDisplayRect::PtInVideoRect(POINT Point)
{
	RECT VideoRct;
	GetDlgItem(IDC_DISWND)->GetWindowRect(&VideoRct);
	return PtInRect(&VideoRct, Point);
}