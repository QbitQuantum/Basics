LRESULT CWkeWebkitWnd::OnImeStartComposition(UINT uMsg, WPARAM wParam,LPARAM lParam, BOOL& bHandled)
{
	wkeRect caret = m_pWebView->getCaret();

	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);

	CANDIDATEFORM form;
	form.dwIndex = 0;
	form.dwStyle = CFS_EXCLUDE;
	form.ptCurrentPos.x = caret.x + rcClient.left;
	form.ptCurrentPos.y = caret.y + caret.h + rcClient.top;
	form.rcArea.top = caret.y + rcClient.top;
	form.rcArea.bottom = caret.y + caret.h + rcClient.top;
	form.rcArea.left = caret.x + rcClient.left;
	form.rcArea.right = caret.x + caret.w + rcClient.left;
	COMPOSITIONFORM compForm;
	compForm.ptCurrentPos=form.ptCurrentPos;
	compForm.rcArea=form.rcArea;
	compForm.dwStyle=CFS_POINT;

	HWND hWnd=m_pOwner->GetManager()->GetPaintWindow();
	HIMC hIMC = ImmGetContext(hWnd);
	ImmSetCandidateWindow(hIMC, &form);
	ImmSetCompositionWindow(hIMC,&compForm);
	ImmReleaseContext(hWnd, hIMC);

	//bHandled = TRUE;
	return 0;
}