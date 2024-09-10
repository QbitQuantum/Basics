STDMETHODIMP CHashCheck::AddPages( LPFNADDPROPSHEETPAGE pfnAddPage, LPARAM lParam )
{
	PROPSHEETPAGE psp;
	psp.dwSize = sizeof(psp);
	psp.dwFlags = PSP_USECALLBACK | PSP_USEREFPARENT | PSP_USETITLE;
	psp.hInstance = g_hModThisDll;
	psp.pszTemplate = MAKEINTRESOURCE(IDD_HASHPROP);
	psp.pszTitle = MAKEINTRESOURCE(IDS_HP_TITLE);
	psp.pfnDlgProc = HashPropDlgProc;
	psp.lParam = (LPARAM)m_hList;
	psp.pfnCallback = HashPropCallback;
	psp.pcRefParent = (PUINT)&g_cRefThisDll;

	if (ActivateManifest(FALSE))
	{
		psp.dwFlags |= PSP_USEFUSIONCONTEXT;
		psp.hActCtx = g_hActCtx;
	}

	HPROPSHEETPAGE hPage = CreatePropertySheetPage(&psp);

	if (hPage && !pfnAddPage(hPage, lParam))
		DestroyPropertySheetPage(hPage);

	// HashProp has AddRef'ed and now owns our list
	SLRelease(m_hList);
	m_hList = NULL;

	return(S_OK);
}