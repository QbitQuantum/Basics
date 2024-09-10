bool vsnet_addin::replace_text(const char * file, int line, const char * old, const char * text)
{
	EnvDTE::DocumentPtr	pDoc;
	HRESULT hr = GetOpenFileDocument(pDoc,file);
	if (hr == S_FALSE)
		return false;
	EnvDTE::TextDocumentPtr pTextDocument;
	pDoc->Object(CComBSTR("TextDocument"),(IDispatch**)&pTextDocument);

	if (pTextDocument == NULL)
		return false;

	EnvDTE::TextSelectionPtr pSelection;
	hr = pTextDocument->get_Selection(&pSelection);
	if (pSelection == NULL)
	{
		return false;
	}	
	hr = pSelection->GotoLine(line,(_variant_t)(long)0);
	pSelection->SelectLine();
	VARIANT_BOOL bRet;
	hr = pSelection->ReplaceTextA(CComBSTR(old),CComBSTR(text),EnvDTE::vsFindOptionsMatchWholeWord,&bRet);

	return hr == S_OK;
}