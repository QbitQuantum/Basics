void CJSOpenView::OnFileWindowOpen() {
	HRESULT hr;
	CString str;
	try {
		CComQIPtr<IHTMLDocument2> document = GetHtmlDocument();
		if (document != NULL) {
			IHTMLWindow2Ptr window;
			document->get_parentWindow(&window);
			if (window != NULL) {
				CComBSTR url;
				document->get_URL(&url);

				CComPtr<IHTMLWindow2> newwin;
				if (FAILED(hr = window->open(url, CComBSTR(L"_blank"), CComBSTR(), false, &newwin))) {
					_com_issue_errorex(hr, window, IID_IHTMLWindow2);
				}
				printf("");
			}
		}
	}
	catch (_com_error err) {
		AfxMessageBox(CString(err.ErrorMessage()), MB_ICONEXCLAMATION);
	}
}