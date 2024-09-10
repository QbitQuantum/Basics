int CRealTimeGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	if( ID == m_buttonIndex && msg == UGCT_BUTTONCLICK )
	{
		QuickSetNumber( 0, row, 0 );
		QuickRedrawCell( 0, row );

		CUGCell cell;
		GetCell( 3, row, &cell );
		cell.SetBackColor(RGB(255,255,255));
		cell.SetTextColor(RGB(0,0,0));
		cell.SetText( _T( "Okay" ) );
		SetCell( 3, row, &cell );
		QuickRedrawCell( 3, row );

		TRACE( _T( "Reset the progress bar in row %ld" ), row );
		GotoCell( -1, row );
	}

	if( ID == UGCT_CHECKBOX && msg == UGCT_CHECKBOXSET )
	{
		if( param == TRUE )
			TRACE( _T( "Progress bar in row %ld was enabled." ), row );
		else
			TRACE( _T( "Progress bar in row %ld was disabled." ), row );
	}
		
	return TRUE;
}