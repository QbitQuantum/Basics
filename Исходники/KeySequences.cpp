void CKeySequences::OnBnClickedRemove( ) {
	UINT count = m_KeyComboList.GetSelectedCount( );
	if ( count < 1 )
		return;

	int ret = MessageBox( CString( (LPCWSTR) IDS_KEYSEQUENCES_CONFIRM_PROMPT ), CString( (LPCWSTR) IDS_KEYSEQUENCES_CONFIRM_TITLE ), MB_YESNO | MB_ICONWARNING );
	if ( IDYES != ret ) {
		return;
	}

	POSITION pos = m_KeyComboList.GetFirstSelectedItemPosition( );
	int* items = new int[count];
	int n = 0;

	int i = m_KeyComboList.GetNextSelectedItem( pos );
	while ( -1 != i ) {
		items[n++] = i;
		i = m_KeyComboList.GetNextSelectedItem( pos );
	}
	qsort_s( items, count, sizeof( int ), compare_keys_reverse, NULL );

	for ( UINT n = 0; n < count; n++ ) {
		m_KeyComboList.DeleteItem( items[n] );
		m_Options.m_ComposeKeyEntries.RemoveAt( items[n] );
	}

	delete[] items;

	SetModified( );
}