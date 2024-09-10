void PowerDocsExtHelper::PopulateDocPropertiesForVersion(DOCSObjects::IVersionPtr pVer,WSDocNonCom& wsDoc,const DOCSObjects::IProfilePtr& pProf)
{
	try
	{
		DOCSObjects::IColumnsPtr pCols	= pProf->GetColumns();
		// have stuck this value in the type and class members (?)
 		//DOCSObjects::IColumnPtr pCol = pCols->GetItem( _variant_t( "DOCNAME" ));
		
		CStdString csDescription = GetColumnValue(pCols, _T("DOCNAME"));
		wsDoc.SetDescription(csDescription);
		
		wsDoc.SetExtension(GetDocumentExtension(pProf));
			
		wsDoc.SetType(GetColumnValue(pCols, _T("APP_ID")));
		wsDoc.SetClass(GetColumnValue(pCols, _T("TYPE_ID")));
		wsDoc.SetAuthor(GetColumnValue(pCols, _T("AUTHOR_ID")));
		wsDoc.SetOperator(GetColumnValue(pCols, _T("TYPIST_ID")));
		
		long lDocNum = pProf->GetDocNumber();
		CStdString sLibName ( pProf->GetLibrary()->GetName() );
		CStdString sVersion (pVer->GetVersionLabel());

		CStdString sDocID;
 		sDocID.Format(_T("PowerDocs://%s/%d/%s"), sLibName.c_str(), lDocNum, sVersion.c_str());
		wsDoc.SetDocId(sDocID);

		if(wsDoc.GetLocalFile().length()>0)
		{
			WIN32_FIND_DATA w32Data;
			CStdString sLocalFile = wsDoc.GetLocalFile();
			
			HANDLE hFile = FindFirstFile(sLocalFile, &w32Data);
			
			wsDoc.SetFileSizehigh(w32Data.nFileSizeHigh);
			wsDoc.SetFileSizeLow(w32Data.nFileSizeLow);
			
			
			SYSTEMTIME sysTime;
			FileTimeToSystemTime(&w32Data.ftLastWriteTime, &sysTime);
			DATE dTime;
			SystemTimeToVariantTime(&sysTime, &dTime);
			
			wsDoc.SetModifiedTime(dTime);
			FindClose(hFile);
		}
		
	}
	catch(_com_error&)
	{		
 		LOG_WS_ERROR(_T("::PopulateDocProperties threw excpetion") );
	}
	
	return;
}