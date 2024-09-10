	void VListWin::DrawItem( GC& gc, int n, crect rect )
	{
		gc.SetFillColor( ( n % 2 ) ? 0xFFFFFF : 0xE0FFE0 );
		gc.FillRect( rect );
	}