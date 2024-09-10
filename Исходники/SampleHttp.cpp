static void OnSkinChanged(HTMLControl *pCtrl)
{
	wchar_t css[128];
	if (!pCtrl) return;
	if (!ml_color) return; // make sure we have the function to get colors first!
	return;  // lets not do this for now...
	if (S_OK ==StringCchPrintfW(css, 128, L"BODY { background-color: #%06X; color:#%06X }",
	                            GetHTMLColor(ml_color(WADLG_ITEMBG)),
	                            GetHTMLColor(ml_color(WADLG_ITEMFG))))
	{
		pCtrl->SetHostCSS(css);
	}
}