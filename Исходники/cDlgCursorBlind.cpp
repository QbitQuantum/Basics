HCURSOR make_transparent_cursor ()
{
	int x = GetSystemMetrics ( SM_CXICON );
	int y = GetSystemMetrics ( SM_CYICON );
	BYTE * aAnd = new BYTE [ x * y ];
	BYTE * aXor = new BYTE [ x * y ];
	memset ( aAnd, 0xFF, x*y );
	memset ( aXor, 0x00, x*y );
	HCURSOR hCursor = CreateCursor ( g_hInstance, 0, 0, x, y, aAnd, aXor );
	return hCursor;
}