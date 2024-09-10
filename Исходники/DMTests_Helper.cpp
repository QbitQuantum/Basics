void DMTests_Helper::SaveDocument(const CStdString& sDocumentName, const CStdString& sAppID, CStdString& sTestDocID)
{

	USES_CONVERSION;

	try
	{
		DOCSObjects::IApplicationPtr    pApp( __uuidof( DOCSObjects::Application ));

		pApp->PutDefParentWindow( 0 );

		DOCSObjects::ILibrariesPtr pLibs	= pApp->GetLibraries();
		DOCSObjects::ILibraryPtr pLib		= pApp->GetCurrentLibrary();
		DOCSObjects::IDOCSFormsPtr pForms	= pLib->GetForms();
		DOCSObjects::IProfilePtr pBaseProf	= NULL;
		DOCSObjects::IDOCSFormPtr  pForm	= NULL;

		int	 iCount		= pForms->GetCount();
		bool bFoundProf	= FALSE;
		_variant_t vtIndex;
		vtIndex.vt = VT_I4;

		for (vtIndex.lVal = 1; (vtIndex.lVal <= iCount) && (!bFoundProf); vtIndex.lVal++)
		{
			pForm = pForms->GetItem(vtIndex);

			if (pForm->GetType() & DOCSObjects::FT_DEFAULT_PROFILE)
			{
				pBaseProf       = pLib->CreateProfile(pForm->GetName());
				bFoundProf      = TRUE;
			}
		}

		if (pBaseProf == NULL)
		{
			pBaseProf = pLib->CreateProfile( _bstr_t( _T("LAWPROF") ));
		}

		DOCSObjects::IColumnsPtr pCols = pBaseProf->GetColumns();

		DOCSObjects::IColumnPtr pCol = pCols->GetItem( _variant_t( _T("APP_ID") ));
		pCol->PutValue( _variant_t( T2CW(sAppID.c_str()) ) );

		pCol = pCols->GetItem( _variant_t( _T("DOCNAME") ));
		pCol->PutValue( _variant_t( sDocumentName.c_str() ) );

		pCol = pCols->GetItem( _variant_t( _T("TYPE_ID") ));
		pCol->PutValue( _variant_t( L"MEMO"));

		pCol = pCols->GetItem( L"AUTHOR_ID");
		pCol->PutValue(L"pair");

		pCol = pCols->GetItem(L"TYPIST_ID");
		pCol->PutValue(L"pair");

		pCol = pCols->GetItem(L"CLIENT_ID");
		pCol->PutValue(L"TEST");

		pCol = pCols->GetItem(L"MATTER_ID");
		pCol->PutValue(L"TEST");


		VARIANT_BOOL vb = pBaseProf->Save( DOCSObjects::OF_NORMAL );

		if(vb == VARIANT_FALSE)
		{
			throw std::exception("Profile save document failed");
		}

		DOCSObjects::IVersionPtr pVer = pBaseProf->GetCurrentVersion();

		CStdString sDest = pVer->GetFilePath();
		bool bSuccess = false;
		if (sAppID.CompareNoCase(_T("ACROBAT")) == 0)
		{
			bSuccess = (CopyFile(TEST_PDF_FILE,sDest.c_str(),false)!=0);
		}
		else
		{
			bSuccess = (CopyFile(TEST_DOC_FILE,sDest.c_str(),false)!=0);
		}
		if(!bSuccess)
		{
			throw std::exception("Copy of test file failed");
		}

		m_lDocNum = pBaseProf->GetDocNumber();

		BSTR bsLibName = pLib->GetName();
		CStdString sLibName(bsLibName);
		SysFreeString(bsLibName);

		sTestDocID.Format(_T("PowerDocs://%s/%d/1"),sLibName.c_str(),m_lDocNum);

		pVer->UploadFile( NULL );
		pVer->UnlockVersion( DOCSObjects::OF_NORMAL );

		pBaseProf->ReleaseDoc();

		m_vDocIDs.push_back(sTestDocID);
	}
	catch(_com_error& e)
	{
		CStdString sMsg;
		sMsg.Format(_T("Save document failed : %s"), (const TCHAR*)e.Description());
		throw std::exception(CStdStringA(sMsg));
	}
}