void ShowSourceLine(const std::string& fileName, int lineNr)
{
	const wchar_t* progIds[] =
	{
		L"VisualStudio.DTE",
		L"VisualStudio.DTE.10.0",
		L"VisualStudio.DTE.9.0",
		L"VisualStudio.DTE.8.0",
		L"VisualStudio.DTE.7.1",
		L"VisualStudio.DTE.7.0"
	};

	for (auto it = std::begin(progIds); it != std::end(progIds); ++it)
	{
		auto pIDte = GetActiveObject<EnvDTE::_DTE>(ClsidFromProgId(*it));
		if (!pIDte)
			continue;

		CComPtr<EnvDTE::ItemOperations> pIOps;
		CComPtr<EnvDTE::Window> pWindow;

		HRESULT hr = pIDte->get_ItemOperations(&pIOps);
		if (SUCCEEDED(hr))
			hr = pIOps->OpenFile(CComBSTR(fileName.c_str()), CComBSTR(EnvDTE::vsViewKindTextView), &pWindow);

		CComPtr<EnvDTE::Document> pDocument;
		CComPtr<IDispatch> pIDisp;
		if (SUCCEEDED(hr))
			hr = pIDte->get_ActiveDocument(&pDocument);
		if (SUCCEEDED(hr))
			hr = pDocument->get_Selection(&pIDisp);
		CComPtr<EnvDTE::TextSelection> pSelection = com_cast<EnvDTE::TextSelection>(pIDisp);
		if (SUCCEEDED(hr) && pSelection)
			hr = pSelection->GotoLine(lineNr, VARIANT_FALSE);

		if (SUCCEEDED(hr))
			break;
	}
}