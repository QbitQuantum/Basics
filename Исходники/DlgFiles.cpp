static void BasicList( CListCtrl& List )
	{
	List.InsertColumn( 0, "Filename" );
	List.InsertColumn( 1, "Size", LVCFMT_RIGHT );
	CRect R;
	List.GetClientRect( R );
	int iWidth = R.Width( ) / 5;
	List.SetColumnWidth( 0, iWidth * 4 );
	List.SetColumnWidth( 1, iWidth * 1 );
	}