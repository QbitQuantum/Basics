void CLibraryDetailView::OnFindItemA(NMLVFINDITEM* pNotify, LRESULT* pResult)
{
	USES_CONVERSION;
	LPCTSTR pszFind = A2CT( (LPCSTR)pNotify->lvfi.psz );
	
	GET_LIST();
	CQuickLock oLock( Library.m_pSection );

	for ( int nLoop = 0 ; nLoop < 2 ; nLoop++ )
	{
		for ( int nItem = pNotify->iStart ; nItem < pList->GetItemCount() ; nItem++ )
		{
			if ( CLibraryFile* pFile = Library.LookupFile( m_pList[ nItem ].nIndex ) )
			{
				if ( pNotify->lvfi.flags & LVFI_STRING )
				{
					if ( _tcsnicmp( pszFind, pFile->m_sName, _tcslen( pszFind ) ) == 0 )
					{
						*pResult = nItem;
						return;
					}
				}
			}
		}
		pNotify->iStart = 0;
	}

	*pResult = -1;
}