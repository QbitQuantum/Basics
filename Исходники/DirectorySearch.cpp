////////////////////////////////////////////
// OnExecute
// Demonstrate:
// IDirectorySearch::ExecuteSearch
// IDirectorySearch::GetNextRow
// IDirectorySearch::GetColumn
// IDirectorySearch::SetSearchPreference
//
/////////////////////////////////////////////
void CDlgIDirectorySearch::OnExecute() 
{
	ASSERT( m_pSearch );
	CWaitCursor wait;
	
	UpdateData(TRUE); // Get data from the Dialog Box
	HRESULT hr;
	ADS_SEARCH_HANDLE hSearch;
	ADS_SEARCH_COLUMN col;
	CString s;
	int idx=0;
	int nCount;
	LPWSTR *pszAttr=NULL;
	POSITION pos;
	USES_CONVERSION;


	


	/////////////////////////////////
	// Reset the Total Number
	//////////////////////////////////
	SetDlgItemText( IDC_TOTAL, _T(""));


	/////////////////////////////////////////////
	// Get the attribute list, and preparing..
	///////////////////////////////////////////
	CStringList sAttrList;
	m_cListView.DeleteAllItems(); // Reset the UI

    while( m_cListView.DeleteColumn(0))
	{
		;
	}

	//////////////////////////////////////////////////
	// Preparing for attribute list
	// and columns to display
	CString sTemp;
	m_cAttrList.GetWindowText(s);

	// we need to add adspath, so that we can refer to this object later when user dblclk the item
	if ( !s.IsEmpty() )
	{
		sTemp = s;
		sTemp.MakeLower();
		if ( s.Find(_T("adspath"),0) == -1 )
		{
			s += _T(",ADsPath");
		}
	}

	// convert to string list for easy manipulation
	StringToStringList( s, sAttrList );



	nCount = sAttrList.GetCount();
	idx=0;
	if ( nCount )
	{
		
		pszAttr = (LPWSTR*) AllocADsMem( nCount * sizeof(LPWSTR));
	
		pos = sAttrList.GetHeadPosition();
		while ( pos != NULL )
		{
			s = sAttrList.GetAt(pos);
			pszAttr[idx] = T2OLE(s);
			sAttrList.GetNext(pos );
			idx++;
		}
	}
	else
	{
		nCount = -1;
	}






	/////////////////////////////////////////
	// BEGIN  Set the preferences
	///////////////////////////////////////
	DWORD dwCountPref = 0;
	ADS_SEARCHPREF_INFO prefInfo[ MAX_SEARCH_PREF ];
	ADS_SORTKEY *pSortKey = NULL;

	if ( m_bEnableFilter == FALSE )
	{
		// Reset the preference
		m_pSearch->SetSearchPreference( prefInfo, dwCountPref );
	}
	else // Preferences are specified
	{
		////////////////////////
		// Timeout Pref
		////////////////////////////
		if ( m_nTimeOut != 0 )
		{
			prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_TIMEOUT;
			prefInfo[dwCountPref].vValue.dwType = ADSTYPE_INTEGER;
			prefInfo[dwCountPref].vValue.Integer = m_nTimeOut;
			dwCountPref++;
		}

		//////////////////////////////
		// Search Scope
		/////////////////////////////
		idx = m_CADsSearchScope.GetCurSel();
		if ( idx != CB_ERR )
		{
			prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_SEARCH_SCOPE;
			prefInfo[dwCountPref].vValue.dwType = ADSTYPE_INTEGER;
			prefInfo[dwCountPref].vValue.Integer = idx;
			dwCountPref++;
		}



		///////////////////////////////////////////////////
		// Cache Result. The default is to cache the result
		/////////////////////////////////////////////////
		if ( !m_bCacheResult )
		{
			prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_SEARCH_SCOPE;
			prefInfo[dwCountPref].vValue.dwType = ADSTYPE_BOOLEAN;
			prefInfo[dwCountPref].vValue.Boolean = FALSE;
			dwCountPref++;
		}

		//////////////////////////////////////////////////
		// Page Size
		///////////////////////////////////////////////////
		if ( m_nPageSize > 0 )
		{
			prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_PAGESIZE;
			prefInfo[dwCountPref].vValue.dwType = ADSTYPE_INTEGER;;
			prefInfo[dwCountPref].vValue.Integer = m_nPageSize;
			dwCountPref++;
		}


		////////////////////////////////////////////////
		// Chase Referrals
		///////////////////////////////////////////////
		idx = m_cChaseReferrals.GetCurSel();
		if ( idx != CB_ERR )
		{
			prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_CHASE_REFERRALS;
			prefInfo[dwCountPref].vValue.dwType = ADSTYPE_INTEGER;
			switch( idx )
			{
			case 0:
				 prefInfo[dwCountPref].vValue.Integer = ADS_CHASE_REFERRALS_NEVER; 
				 break;
			case 1:
				 prefInfo[dwCountPref].vValue.Integer = ADS_CHASE_REFERRALS_SUBORDINATE;
				 break;
			case 2:
				 prefInfo[dwCountPref].vValue.Integer = ADS_CHASE_REFERRALS_EXTERNAL;
				 break;
			default:
				 prefInfo[dwCountPref].vValue.Integer = ADS_CHASE_REFERRALS_EXTERNAL;
				 
			}
			
			dwCountPref++;
		}


		///////////////////////////////////////////////
		// Sort On
		////////////////////////////////////////////////
		if ( !m_sSortOn.IsEmpty() )
		{
			CStringList sList;
			UINT nCount;
			prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_SORT_ON;
			prefInfo[dwCountPref].vValue.dwType = ADSTYPE_PROV_SPECIFIC;
  			StringToStringList( m_sSortOn, sList );

			nCount = sList.GetCount();
			if ( nCount >  0 )
			{
				POSITION pos;
				pos= sList.GetHeadPosition();
				pSortKey = (ADS_SORTKEY *) LocalAlloc( LMEM_FIXED | LMEM_ZEROINIT, sizeof(ADS_SORTKEY) * nCount );
				idx = 0;
				while( pos != NULL )
				{
					pSortKey[idx].pszAttrType = T2OLE(sList.GetAt(pos));
					pSortKey[idx].pszReserved = NULL;
					pSortKey[idx].fReverseorder =0;

					// Next
					idx++;
					sList.GetNext( pos );
				}
				
				prefInfo[dwCountPref].vValue.ProviderSpecific.dwLength = sizeof(ADS_SORTKEY) * nCount;
				prefInfo[dwCountPref].vValue.ProviderSpecific.lpValue = (LPBYTE) pSortKey;
				dwCountPref++;
			}

		}

		//////////////////////////////////////////////
		// Size Limit
		//////////////////////////////////////////////
		if ( m_nSizeLimit > 0 )
		{
            prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_SIZE_LIMIT;
            prefInfo[dwCountPref].vValue.dwType = ADSTYPE_INTEGER;
            prefInfo[dwCountPref].vValue.Integer = m_nSizeLimit;
			dwCountPref++;
		}


		//////////////////////////////////////////////////
		// A Synchronous
		///////////////////////////////////////////////////
		if ( m_bAsynch )
		{
			prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_ASYNCHRONOUS;
            prefInfo[dwCountPref].vValue.dwType = ADSTYPE_BOOLEAN;
            prefInfo[dwCountPref].vValue.Integer = TRUE;
			dwCountPref++;

		}

		/////////////////////////////////////////////////////
		//  Attribute Type Only
		//////////////////////////////////////////////////////
		if ( m_bAttrib )
		{
			prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_ATTRIBTYPES_ONLY;
            prefInfo[dwCountPref].vValue.dwType = ADSTYPE_BOOLEAN;
            prefInfo[dwCountPref].vValue.Integer = TRUE;
			dwCountPref++;

		}


		/////////////////////////////////////////////////////
		//  Derefence Alias
		//////////////////////////////////////////////////////
		if ( m_nDeref != CB_ERR )
		{
			prefInfo[dwCountPref].dwSearchPref = ADS_SEARCHPREF_DEREF_ALIASES;
            prefInfo[dwCountPref].vValue.dwType = ADSTYPE_INTEGER;
            prefInfo[dwCountPref].vValue.Integer = m_nDeref;
			dwCountPref++;


		}



		///////////////////////////////////////////////
		// Now Set the selected preferences
		//////////////////////////////////////////////
		hr = m_pSearch->SetSearchPreference( prefInfo, dwCountPref );


		
	}

	/////////////////////////////////////////
	// END  Set the preferences
	///////////////////////////////////////





	////////////////////////////////////////
	// Execute the Search
	//////////////////////////////////////
	DWORD dwCount=0;

	hr = m_pSearch->ExecuteSearch(T2OLE(m_sFilter), pszAttr, nCount, &hSearch );


	////////////////////////////////
	//// cleanup
	////////////////////////////////
	if ( pszAttr ) 
	{
  		FreeADsMem( pszAttr );
	}
	
	if ( pSortKey )
	{
		LocalFree( pSortKey );
	}




	if ( !SUCCEEDED(hr) )
	{
		AfxMessageBox(GetErrorMessage(hr));
		return;
	}

	////////////////////////////////////////////////////////
	// Enumerate the rows
	////////////////////////////////////////////////////////

	sAttrList.RemoveAll();

	

	
	/////////////////////////////////////////////////////////
	// Retrieve the column names returned from the server
	///////////////////////////////////////////////////////////
	LPWSTR pszColumn;
	hr = m_pSearch->GetFirstRow( hSearch );

	if ( !SUCCEEDED(hr) )
	{
		return;
	}
	
	

	idx=0;
	while( (hr=m_pSearch->GetNextColumnName( hSearch, &pszColumn )) != S_ADS_NOMORE_COLUMNS )
	{
		s = OLE2T( pszColumn );
		m_cListView.InsertColumn(idx, s, LVCFMT_LEFT, 150 ); // adding columns to the UI	
		sAttrList.AddTail(s);
		FreeADsMem( pszColumn );
		idx++;
	}



	/////////////////////////////////////////////
	// Start iterating the result set
	////////////////////////////////////////////
	int nCol;
	CStringList sValueList;

    do 
	{
		nCol=0;
		pos = sAttrList.GetHeadPosition();

		while( pos != NULL )
		{
		
		    s = sAttrList.GetAt(pos); //column name

			// Get the Name and display it in the list 
			hr = m_pSearch->GetColumn( hSearch, T2OLE(s), &col );
			if ( SUCCEEDED(hr) )
			{
				s =_T("");
				
				if ( col.dwADsType != ADSTYPE_INVALID ) // if we request for attrib only, no value will be returned
				{
					ADsToStringList(col.pADsValues, col.dwNumValues, sValueList );
					StringListToString( sValueList, s );
				}
	
				if ( nCol )
				{
					m_cListView.SetItemText(0,nCol, s);
				}
				else
				{
				   m_cListView.InsertItem(0, s);
				}
				
				m_pSearch->FreeColumn( &col );
			}


			

			nCol++;
			sAttrList.GetNext(pos);

		}
		dwCount++;
		/////////////////////////////
		//Display the total so far
		////////////////////////////////
		s.Format("%ld object(s)", dwCount );
		SetDlgItemText( IDC_TOTAL, s );
	
	} 
	while( (hr=m_pSearch->GetNextRow( hSearch)) != S_ADS_NOMORE_ROWS );	 

	

	m_pSearch->CloseSearchHandle( hSearch ); 



	


}