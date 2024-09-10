void Comparisons::UpdateOpenList()
{
	CMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	CWnd* pChild = pMainFrame->MDIGetActive();

	while (pChild)
	{
		CChildFrame* pChildFrame = DYNAMIC_DOWNCAST(CChildFrame, pChild);
		if (pChildFrame != NULL)
		{
			UpdateOpenDoc(pChildFrame->GetDocument());
		}
		pChild = pChild->GetWindow( GW_HWNDNEXT );
	}
}