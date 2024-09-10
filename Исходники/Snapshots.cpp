HRESULT CHtmlTableSnapshots::SetDocumentText(CComPtr<IWebBrowser2> pWebBrowser, std::string cstr)
{
	_bstr_t tbstr(cstr.c_str());
	//HRESULT_EXCEPTION hr = S_OK;
	HRESULT hr = S_OK;
	VARIANT *param;
	SAFEARRAY *sfArray;
	CComPtr<IHTMLDocument2> document;
	BSTR  bstr= tbstr.Detach();

	try
	{
		// Creates a new one-dimensional array
		sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);

		document=GetDocument(pWebBrowser);
		if (sfArray == NULL || document == NULL) 
			throw std::exception("CMainDlg::SetDocumentText) Failed IHTMLDocument2\n");

		hr = SafeArrayAccessData(sfArray,(LPVOID*) & param);
		param->vt = VT_BSTR;
		param->bstrVal = bstr;
		hr = SafeArrayUnaccessData(sfArray);
		hr = document->write(sfArray);
	}
	catch(std::exception e)
	{
		AtlTrace(e.what());
		throw e;
	}
	catch(HRESULT hResult)
	{
		std::string errmsg =(LPCSTR)( "CMainDlg::SetDocumentText Failed: %s\n" +   ErrorFormatMessage(hResult));
		AtlTrace("CMainDlg::SetDocumentText Failed: %s\n",  (LPCSTR) ErrorFormatMessage(hResult));
		throw std::exception(errmsg.c_str());
	}
	catch(...)
	{
		AtlTrace("CMainDlg::OpenIE() Failed\n");
		throw std::exception("CMainDlg::OpenIE() Failed\n");
	}

	if (sfArray != NULL) 
		SafeArrayDestroy(sfArray);
	return S_OK;
}