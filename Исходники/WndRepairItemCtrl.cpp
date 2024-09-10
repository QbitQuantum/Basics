int CWndRepairItemCtrl::HitTest( CPoint point )
{
	CRect rect	= GetClientRect();
	int nWidth	= rect.Width() / 32;
	int nHeight		= rect.Height() / 35;

	for( int i = 0; i < MAX_VENDITEM; i++ )
	{
		int x	= i % 5;
		int y	= i / 5;
		rect.SetRect( x * 32, y * 32, x * 32 + 32, y * 32 + 32 );
		if( rect.PtInRect( point ) )
			return i;
	}
	return -1;
}