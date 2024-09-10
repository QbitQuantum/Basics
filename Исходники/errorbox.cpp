CWnd* CInformErrorDialog::GetSafeParent()
{
	CWnd *Parent = NULL;

#if !defined(EXCLUDE_FROM_RALPH) && !defined(EXCLUDE_FROM_XARALX)
	// if the splash box is up, use that as the parent
	Parent = CSplashDialog::GetpWnd();

	if (Parent)
		return Parent;
#endif

//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER
#ifndef STANDALONE
	// If there is a print-related dlg up, use it as the parent
	Parent = CCPrintDialog::GetPrintCWnd();
	if (Parent)
		return Parent;
#endif
#endif //webster

	// see if mainframe is up - use it if visible
	Parent = GetMainFrame();
	if (Parent && Parent->IsWindowVisible())
		return Parent;
	return NULL;
}