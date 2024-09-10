void CDlgIDirectoryObject::OnGet() 
{
   CStringList sList;
   UINT nCount;
   HRESULT hr;
   

   UpdateData(TRUE);

   StringToStringList(m_sAttributes, sList );
   nCount = sList.GetCount();
   if ( nCount == 0 )
   {
	   return;
   }

   
   
   ///////////////////////////////////////
   // Now build the Attribute Names List
   ///////////////////////////////////////
   POSITION			pos;
   DWORD			dwNumAttr;
   LPWSTR			*pAttrNames=NULL;
   ADS_ATTR_INFO	*pAttrInfo;
   DWORD			dwReturn;
   

   USES_CONVERSION;


   pAttrNames = (LPWSTR*) AllocADsMem( sizeof(LPWSTR) * nCount );
   pos = sList.GetHeadPosition();
   dwNumAttr = 0;
   while( pos != NULL )
   {
	   pAttrNames[dwNumAttr] = T2OLE(sList.GetAt(pos));
	   dwNumAttr++;
	   sList.GetNext(pos);
   }

   
 
   
   /////////////////////////////////////////
   // Get attributes value requested
   // Note: The order is not necessarily the same as
   //       requested via pAttrNames.
   ///////////////////////////////////////////
   hr = m_pDirObject->GetObjectAttributes( pAttrNames, dwNumAttr, &pAttrInfo, &dwReturn );

   

   if ( SUCCEEDED(hr) )
   {
	  DWORD idx;
	  CString sDisplay;
	  CStringList sValueList;
	  UINT nCount;
	  POSITION pos;

	  m_cValueList.ResetContent();

	  for( idx=0; idx < dwReturn; idx++) 
	  {		  
          ADsToStringList( pAttrInfo[idx].pADsValues, pAttrInfo[idx].dwNumValues, sValueList );
		  sDisplay = OLE2T(pAttrInfo[idx].pszAttrName);
		  sDisplay += _T(":");
		  m_cValueList.AddString( sDisplay );
		  nCount = sValueList.GetCount();
		  if ( nCount == 0 ) // can not find/convert the value
		  {
			  m_cValueList.AddString(_T(" > [No Value]"));
			  continue;
		  }
		  else
		  {
			  pos = sValueList.GetHeadPosition();
			  while( pos != NULL )
			  {
				  sDisplay = _T(" > ");
				  sDisplay += sValueList.GetAt(pos);
				  m_cValueList.AddString( sDisplay );
				  sValueList.GetNext(pos);
			  }

		  }
		  
	  }

	  sValueList.RemoveAll();
   }

   

   ///////////////////////////////////////////////////////////
   // Use FreADsMem for all memory obtained from ADSI call 
   /////////////////////////////////////////////////////////////
   FreeADsMem( pAttrInfo );
   FreeADsMem( pAttrNames );

	
}