HRESULT STDMETHODCALLTYPE CNzbParser::startElement( 
	/* [in] */ const wchar_t *pwchNamespaceUri,
	/* [in] */ int cchNamespaceUri,
	/* [in] */ const wchar_t *pwchLocalName,
	/* [in] */ int cchLocalName,
	/* [in] */ const wchar_t *pwchRawName,
	/* [in] */ int cchRawName,
	/* [in] */ ISAXAttributes *pAttributes)
{
	CString localName(pwchLocalName, cchLocalName);
	if(localName == _T("nzb")) {
		ASSERT(theNzb);
		curNzb = theNzb;
	} else if(localName == _T("file")) {
		ASSERT(curNzb);
		curFile = new CNzbFile(curNzb);
		const wchar_t* pwchSubject;
		int cchSubject;
		VERIFY(SUCCEEDED(pAttributes->getValueFromName(L"", 0, L"subject", wcslen(L"subject"), &pwchSubject, &cchSubject)));
		curFile->subject = CString(pwchSubject, cchSubject);
		curNzb->files.Add(curFile);
	} else if(localName == _T("group")) {
		ASSERT(curFile);
		curGroup = true;
		curGroupString.Empty();
	} else if(localName == _T("segment")) {
		ASSERT(curFile);
		curSegment = new CNzbSegment(curFile);
		const wchar_t* pwchBytes;
		int cchBytes;
		VERIFY(SUCCEEDED(pAttributes->getValueFromName(L"", 0, L"bytes", wcslen(L"bytes"), &pwchBytes, &cchBytes)));
		CString bytes(pwchBytes, cchBytes);
		curSegment->bytes = _wcstoui64(bytes, NULL, 10);

		const wchar_t* pwchNumber;
		int cchNumber;
		VERIFY(SUCCEEDED(pAttributes->getValueFromName(L"", 0, L"number", wcslen(L"number"), &pwchNumber, &cchNumber)));
		CString number(pwchNumber, cchNumber);
		curSegment->number = wcstoul(number, NULL, 10);

		curFile->segments.Add(curSegment);
	}
	return S_OK;
}