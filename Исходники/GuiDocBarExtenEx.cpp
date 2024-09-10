BOOL CGuiDocBarExtenEx::_IsMenuBar(int nPos, CPtrArray& arrBars)
{
	if (nPos < arrBars.GetSize()) {
		CControlBar* pBar = (CControlBar*)arrBars[nPos];
		if (pBar && pBar->GetDlgCtrlID() == AFX_IDW_MENUBAR)
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}