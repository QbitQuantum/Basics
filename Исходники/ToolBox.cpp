void NASCToolBox::WstringToWchars( wstring temp, wchar_t *WC ) const
{
	int L = temp.length( );
	try {
		for( int i = 0; i < L; i ++ ) WC[ i ] = temp[ i ];
		WC[ L ] = L'\0';
	}
	catch( ... ) {
		cerr << "ERROR_TB002 - Out of Array Size." << endl;//数组越界
		system( "PAUSE" );
	}
	return;
}