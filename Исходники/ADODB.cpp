HRESULT CADODB::OpenAccessDB(LPCTSTR strFileName,
							 LPCTSTR strPWD /* = NULL */) /*throw(_com_error &)*/
{
	if (NULL == strPWD)
		strPWD = _T("");

	// ODBC Driver
	//LPCTSTR ACCESSDBCNNTEMPLATE = _T("DBQ=%s;PWD=%s;DRIVER={Microsoft Access Driver (*.mdb)};");

	// Jet OLEDB (recommend)
	LPCTSTR ACCESSDBCNNTEMPLATE = _T("Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=%s;")
		_T("Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";")
		_T("Jet OLEDB:Registry Path=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=0;")
		_T("Jet OLEDB:Database Password=%s;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;")
		_T("Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;")
		_T("Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False");
	CString strcnn;
	strcnn.Format(ACCESSDBCNNTEMPLATE, strFileName, strPWD);
	m_bstrCnn = strcnn;

	HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
		_com_issue_error(hr);
	m_pConnection->CursorLocation = adUseClient;

	return m_pConnection->Open(m_bstrCnn, "", "", adConnectUnspecified);
}