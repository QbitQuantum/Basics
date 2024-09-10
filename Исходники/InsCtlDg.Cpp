void CInsertControlDlg::RefreshControlList()
{
   BOOL tDone;
   HRESULT hResult;
   IEnumGUIDPtr pEnum;
   ULONG nImplementedCategories;
   CATID* pcatidImpl;
   ULONG nRequiredCategories;
   CATID* pcatidReq;
   CLSID clsid;
   LPOLESTR pszName;
   CString strName;
   ULONG iCategory;
   int iItem;
   POSITION posControl;
   CString strServerPath;
   CString strString;

   m_lbControls.ResetContent();
   m_lControls.RemoveAll();

   nImplementedCategories = (ULONG)m_aImplementedCategories.GetSize();
   if( nImplementedCategories == 0 )
   {
	  nImplementedCategories = ULONG( -1 );
	  pcatidImpl = NULL;
   }
   else
   {
	  pcatidImpl = (CATID*)_malloca( nImplementedCategories*sizeof( CATID ) );
	  for( iCategory = 0; iCategory < nImplementedCategories; iCategory++ )
	  {
		 pcatidImpl[iCategory] = m_aImplementedCategories[iCategory];
	  }
   }

   if( m_butIgnoreRequiredCategories.GetCheck() )
   {
	  nRequiredCategories = ULONG( -1 );
	  pcatidReq = NULL;
   }
   else
   {
	  nRequiredCategories = (ULONG)m_aRequiredCategories.GetSize();
	  if( nRequiredCategories == 0 )
	  {
		 pcatidReq = NULL;
	  }
	  else
	  {
		 pcatidReq = (CATID*)_malloca( nRequiredCategories*sizeof( CATID ) );
		 for( iCategory = 0; iCategory < nRequiredCategories; iCategory++ )
		 {
			pcatidReq[iCategory] = m_aRequiredCategories[iCategory];
		 }
	  }
   }

   hResult = m_pCatInfo->EnumClassesOfCategories( nImplementedCategories,
	  pcatidImpl, nRequiredCategories, pcatidReq, &pEnum );


   _freea(pcatidImpl);
   _freea(pcatidReq);

   
   if( FAILED( hResult ) )
   {
	  return;
   }

   tDone = FALSE;

   int nExtent = 0;
   TEXTMETRIC tm;
   ::ZeroMemory(&tm, sizeof(TEXTMETRIC));
   CFont *pFont = NULL;
   CFont *pOldFont = NULL;
   CDC *pDC = m_lbControls.GetDC();
   ASSERT(pDC);
   if (pDC)
   {
	   pFont = m_lbControls.GetFont();
	   ASSERT(pFont);
       if (pFont)
	   {
		   pOldFont = pDC->SelectObject(pFont);
		   VERIFY(pDC->GetTextMetrics(&tm));
	   }
   }

   while( !tDone )
   {
	  hResult = pEnum->Next( 1, &clsid, NULL );
	  if( hResult == S_OK )
	  {
		 pszName = NULL;
		 hResult = OleRegGetUserType( clsid, USERCLASSTYPE_FULL, &pszName );
		 if( SUCCEEDED( hResult ) )
		 {
			strName = pszName;
			CoTaskMemFree( pszName );
			pszName = NULL;
			if (pDC && pFont)
			{
				CSize sz = pDC->GetTextExtent(strName);
				if (sz.cx > nExtent)
					nExtent = sz.cx;
			}
			iItem = m_lbControls.AddString( strName );
			posControl = m_lControls.AddTail( clsid );
			m_lbControls.SetItemDataPtr( iItem, posControl );
		 }
	  }
	  else
	  {
		 tDone = TRUE;
	  }
   }
   if (pDC && pFont)
   {
	   pDC->SelectObject(pOldFont);
	   m_lbControls.SetHorizontalExtent(nExtent + tm.tmAveCharWidth);
   }

   OnControlsSelChange();
}