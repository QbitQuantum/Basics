HRESULT CWtlHtmlView::SetDocumentText( CString cstr)
{
	_bstr_t str(cstr);
	HRESULT hr = S_OK;
	VARIANT *param;
	SAFEARRAY *sfArray;
	IHTMLDocument2 *document;
	BSTR bstr = str.Detach();

	// Creates a new one-dimensional array
	sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);

	if(m_spHTMLDocument==NULL)
		this->GetBody();

	document= m_spHTMLDocument;
	if (sfArray == NULL || document == NULL) {
		hr=E_FAIL;
		goto cleanup;
	}

	hr = SafeArrayAccessData(sfArray,(LPVOID*) & param);
	param->vt = VT_BSTR;
	param->bstrVal = bstr;
	hr = SafeArrayUnaccessData(sfArray);
	hr = document->write(sfArray);

cleanup:
	if (sfArray != NULL) {
		SafeArrayDestroy(sfArray);
	}
	return hr;
}