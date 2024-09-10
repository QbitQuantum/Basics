int ControlLayoutHelper::CalculateHeaderTextHeight(CWnd& calculateWnd)
{
	if(calculateWnd.GetSafeHwnd() == NULL)
		return 0;
	
	CDC* pDC = calculateWnd.GetWindowDC();

	CRect groupRect(0,0,0,0);

	if(NULL != pDC)
	{
		CString wndText;
		calculateWnd.GetWindowText(wndText);

		pDC->DrawText(wndText, &groupRect, DT_CALCRECT);
	}

	return groupRect.Height();
}