void CVariablesGrid::CreateGrid(CWnd* parentWnd, UINT windowID)
{
	CWnd* tempWnd = parentWnd->GetDlgItem(windowID);
	CRect gridRect;
	tempWnd->GetWindowRect(gridRect);
	tempWnd->DestroyWindow();

	CRect dialogRect;
	parentWnd->GetClientRect(dialogRect);
	parentWnd->ClientToScreen(dialogRect);

	gridRect.OffsetRect(-dialogRect.TopLeft());

	Create(gridRect, parentWnd, windowID, WS_VISIBLE);
}