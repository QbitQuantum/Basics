void CHtmlParser::testParseHtml(LPCTSTR szHTML)
{
	HRESULT hr = 0;

	try
	{
		MSHTML::IHTMLDocument2Ptr pDoc;
		hr = pDoc.CreateInstance(CLSID_HTMlDocument);

		SAFEARRAY* psa = SafeArrayCreateVector(VT_VARIANT, 0, 1);
		VARIANT* param;
		bstr_t bsData = szHTML;
		hr = SafeArrayAccessData(psa, (LPVOID*)&param);
		param->vt = VT_BSTR;
		param->bstrVal = (BSTR)bsData;

		hr = pDoc->write(psa);
		hr = pDoc->close();

		SafeArrayDestroy(psa);

		_bstr_t body = pDoc->body->innerHTML;
	
	} catch(_com_error& e)
	{
		e;
	}
}