//	Read the specified data file and add to the data store.
// 27-Oct-2004	SFK	Added db open, if needed.  If successful, facility-specific database is open.
STDMETHODIMP CVifmImport::AddData(
	short sFacilityID, 
	BSTR bstrFilename, 
	VARIANT_BOOL bOverwrite, 
	BSTR *bstrResult, 
	VARIANT_BOOL *pvbResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	USES_CONVERSION;

	*pvbResult = VARIANT_FALSE;

	CString strResult;
	CVifmDataFile File(false);//m_bQuietMode);
	File.mbOverwrite = (bOverwrite != VARIANT_FALSE);

	if (!Db.mbDatabaseOpen) 
		Db.OpenTheDatabase(sFacilityID);

	if (Db.mbDatabaseOpen) 
	{
		Db.msFacNum = sFacilityID;
		CString cs(bstrFilename);
		bool b  = File.ReadDataFile(&Db, cs, &strResult);
		*pvbResult = b?VARIANT_TRUE:VARIANT_FALSE;
	}
	else 
	{
		strResult = "Could not open database for VIFM Import";
	}
	
	*bstrResult = T2BSTR(LPCSTR(strResult));
	Db.CloseDatabase();			// 12-Jan-2005	Close db after each action to allow 2 programs to use the COM
	return S_OK;
}