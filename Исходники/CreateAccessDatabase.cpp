CCreateAccessDatabase::CCreateAccessDatabase(const CString& csDatabasePath, const CString& csDatabaseName, const CString& errINIFile)
{
	// Define ADOX object pointers to Catalog (Database),
	//  Table and Column objects.
	m_pCatalog= NULL;
    m_pTable= NULL;
	m_pIndexPtr = NULL;

	m_csErrorINIFile = errINIFile;

	HRESULT hr = S_OK;

    try
	{
		//Create object instances:
		m_pCatalog.CreateInstance(__uuidof (ADOX::Catalog));

		BOOL bResult = MakeSureDirectoryPathExists (csDatabasePath+"\\");
		BSTR bstrConxString;
		CString conxString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
          csDatabasePath + "\\" + csDatabaseName;
		bstrConxString = conxString.AllocSysString ();
		//Create Database
		hr = (ADOX::_CatalogPtr)m_pCatalog->Create(bstrConxString);
		::SysFreeString (bstrConxString);
	}
	catch (_com_error &e)
	{
		// Redundant with new error codein CBackgroundAnalysis::ExecuteAnalysis ()
		m_csError.Format ("COM Exception HRESULT: 0x%x Message: %s",e.Error (), e.ErrorMessage ());
		SetError (m_csError,EXCEPTION_CAUGHT);
	}
	catch (...)
	{
		// Redundant with new error code in CBackgroundAnalysis::ExecuteAnalysis ()
		m_csError = "Unknown exception caught";
		SetError (m_csError,EXCEPTION_CAUGHT);
	}	

}