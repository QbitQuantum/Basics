BOOL CDBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	// create a database object through the exported function & class factory object
	IClassFactory *pDBFactory=NULL;
	
	HRESULT hRes;
	hRes=CoGetClassObject(CLSID_DBSAMPLE, CLSCTX_SERVER, NULL, IID_IClassFactory, (void**) &pDBFactory);
	if (FAILED(hRes)) {
		CString csError;
		csError.Format(_T("Error %x obtaining class factory for DB Object!"), hRes);
		AfxMessageBox(csError);
		return FALSE;
		}

	hRes=pDBFactory->CreateInstance(NULL, IID_IDB, (void**) &m_pDB);
	if (FAILED(hRes)) {
		CString csError;
		csError.Format(_T("Error %x creating DB Object!"), hRes);
		AfxMessageBox(csError);
		return FALSE;
		}
	
	pDBFactory->Release(); // do not need the factory anymore

	// equivalent way of creating object:
	//   hRes=CoCreateInstance(CLSID_DBSAMPLE, NULL, CLSCTX_SERVER, IID_IDB, (void**) &pDBFactory);

	// initialize state of the document:
	m_csData="No data yet!"; // string displayed in views: last data read
	m_nCount=0;							 // number of writes done through this document
	m_nTable=-1;						 // number of last table created through this document
	return TRUE;
}