CPPageFileInfoClip::CPPageFileInfoClip(CString fn, IFilterGraph* pFG)
	: CPropertyPage(CPPageFileInfoClip::IDD, CPPageFileInfoClip::IDD)
	, m_fn(fn)
	, m_clip(ResStr(IDS_AG_NONE))
	, m_author(ResStr(IDS_AG_NONE))
	, m_copyright(ResStr(IDS_AG_NONE))
	, m_rating(ResStr(IDS_AG_NONE))
	, m_location_str(ResStr(IDS_AG_NONE))
	, m_album(ResStr(IDS_AG_NONE))
	, m_hIcon(NULL)
{
	BeginEnumFilters(pFG, pEF, pBF) {
		if (CComQIPtr<IPropertyBag> pPB = pBF) {
			if (!((CMainFrame*)AfxGetMainWnd())->CheckMainFilter(pBF)) {
				continue;
			}

			CComVariant var;
			if (SUCCEEDED(pPB->Read(CComBSTR(_T("ALBUM")), &var, NULL))) {
				m_album = var.bstrVal;
			}
		}

		if (CComQIPtr<IAMMediaContent, &IID_IAMMediaContent> pAMMC = pBF) {
			if (!((CMainFrame*)AfxGetMainWnd())->CheckMainFilter(pBF)) {
				continue;
			}

			CComBSTR bstr;
			if (SUCCEEDED(pAMMC->get_Title(&bstr)) && bstr.Length()) {
				m_clip = bstr.m_str;
				bstr.Empty();
			}
			if (SUCCEEDED(pAMMC->get_AuthorName(&bstr)) && bstr.Length()) {
				m_author = bstr.m_str;
				bstr.Empty();
			}
			if (SUCCEEDED(pAMMC->get_Copyright(&bstr)) && bstr.Length()) {
				m_copyright = bstr.m_str;
				bstr.Empty();
			}
			if (SUCCEEDED(pAMMC->get_Rating(&bstr)) && bstr.Length()) {
				m_rating = bstr.m_str;
				bstr.Empty();
			}
			if (SUCCEEDED(pAMMC->get_Description(&bstr)) && bstr.Length()) {
				m_descText = bstr.m_str;
				m_descText.Replace(_T(";"), _T("\r\n"));
				bstr.Empty();
			}
		}
	}
	EndEnumFilters;
}