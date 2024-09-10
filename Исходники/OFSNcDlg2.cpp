void COFSNcDlg2::LoadColor(IXMLDOMNode *pRoot, LPCTSTR szName, COLORREF &cr)
{
	CComBSTR bs, bsSelect;

	cr = CLR_NONE;

	bs.Empty();
	bsSelect = L"Color[@Name='";
	bsSelect += szName;
	bsSelect += L"']";
	SelectChildNode(pRoot, bsSelect, NULL, &bs);
	if(bs.m_str != NULL)
	{
		long ncr;
		int n = swscanf(bs.m_str, L"0x%06x", &ncr);
		if(n == 1)
			cr = ncr;
	}
}