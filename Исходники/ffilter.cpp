///////////////////////////////////////////////////////////////////////////////////////////
// base filter class
void BaseFilter_c::Set ( const wchar_t * szFilter )
{
	m_dMasks.Clear ();

	int iLen = wcslen ( szFilter );
	if ( ! iLen )
		return;

	int iPrev = 0;
	Mask_t tMask;
	for ( int i = 0; i < iLen; ++i )
		if ( szFilter [i] == L',' || szFilter [i] == L';' )
		{
			if ( szFilter [i+1] == L'-' )
			{
				++i;
				tMask.m_bInvert = true;
			}
			else
				tMask.m_bInvert = false;

			if ( i - iPrev < MAX_FILTER_LEN )
			{
				wcsncpy ( g_dFilter, szFilter + iPrev, i - iPrev );
				g_dFilter [i - iPrev] = L'\0';

				// cut spaces
				wchar_t * szFilterStart = & ( g_dFilter [0] );
				while ( *szFilterStart && iswspace ( *szFilterStart ) )
					++szFilterStart;

				wcslwr ( szFilterStart );
				tMask.m_sMask = szFilterStart;
				iPrev = i+1;
				m_dMasks.Add ( tMask );
			}
		}

	// string has text but there are no masks
	if ( iPrev < iLen )
	{
		tMask.m_bInvert = *szFilter == L'-';
		int iOffset = ( tMask.m_bInvert ? 1 : 0 );

		int iFilterLen = wcslen ( szFilter + iOffset + iPrev );
		if ( iFilterLen < MAX_FILTER_LEN )
		{
			wcsncpy ( g_dFilter, szFilter + iOffset + iPrev, iFilterLen );
			g_dFilter [iFilterLen] = L'\0';

			// cut spaces
			wchar_t * szFilterStart = & ( g_dFilter [0] );
			while ( *szFilterStart && iswspace ( *szFilterStart ) )
				++szFilterStart;

			wcslwr ( szFilterStart );

			tMask.m_sMask = szFilterStart;
			m_dMasks.Add ( tMask );
		}
	}
}