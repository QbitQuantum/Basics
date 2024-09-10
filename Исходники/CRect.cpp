size_t CGRect::Read( LPCTSTR pszVal )
{
	ADDTOCALLSTACK("CGRect::Read");
	// parse reading the rectangle
	TCHAR *pszTemp = Str_GetTemp();
	strcpy( pszTemp, pszVal );
	TCHAR * ppVal[5];
	size_t i = Str_ParseCmds( pszTemp, ppVal, COUNTOF( ppVal ), " ,\t");
	switch (i)
	{
		case 5:
			m_map = ATOI(ppVal[4]);
			if (( m_map < 0 ) || ( m_map >= 256 ) || !g_MapList.m_maps[m_map] )
			{
				g_Log.EventError("Unsupported map #%d specified. Auto-fixing that to 0.\n", m_map);
				m_map = 0;
			}
			m_bottom = ATOI(ppVal[3]);
			m_right = ATOI(ppVal[2]);
			m_top =	ATOI(ppVal[1]);
			m_left = ATOI(ppVal[0]);
			break;
		case 4:
			m_map = 0;
			m_bottom = ATOI(ppVal[3]);
			m_right = ATOI(ppVal[2]);
			m_top =	ATOI(ppVal[1]);
			m_left = ATOI(ppVal[0]);
			break;
		case 3:
			m_map = 0;
			m_bottom = 0;
			m_right = ATOI(ppVal[2]);
			m_top =	ATOI(ppVal[1]);
			m_left = ATOI(ppVal[0]);
			break;
		case 2:
			m_map = 0;
			m_bottom = 0;
			m_right = 0;
			m_top =	ATOI(ppVal[1]);
			m_left = ATOI(ppVal[0]);
			break;
		case 1:
			m_map = 0;
			m_bottom = 0;
			m_right = 0;
			m_top = 0;
			m_left = ATOI(ppVal[0]);
			break;
	}
	NormalizeRect();
	return( i );
}