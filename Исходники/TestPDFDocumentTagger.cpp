CStdString GetPdfRestrictionLevel(const CStdString& sPdfFile)
{
	CDIntfEx::IDIDocumentPtr spDocument;
	HRESULT hr = spDocument.CreateInstance(__uuidof(CDIntfEx::Document));
	if(S_OK != hr)
		throw Workshare::Com::ComException(_T("Unable to create instance of PDF Document"), hr);

	VARIANT_BOOL bOpen = spDocument->Open(sPdfFile.c_str());
	if(VARIANT_FALSE == bOpen)
	{
		CStdString sError;
		sError.Format(_T("Failed to open PDF document %s"), sPdfFile);
		throw Workshare::System::SystemException(sError);
	}

	_bstr_t keyWords;
	hr = _com_dispatch_raw_propget(spDocument, 0x5, VT_BSTR, keyWords.GetAddress());
	if(FAILED(hr))
		return c_sNoRestriction;

	CStdString restrictionTag = keyWords;
	CStdString level = c_sWSRestrictionLevel;
	CStdString snippet = restrictionTag.Left(static_cast<int>(level.length()));
	if(snippet != level)
		return c_sNoRestriction;

	restrictionTag = restrictionTag.Mid(static_cast<int>(level.length()) + 1);
	return restrictionTag;
}