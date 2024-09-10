void CShowModelPanel::GetPanelSize(int &nWidth, int &nHeight)
{		
	CWnd *pDlgWnd = this;
	CRect rcPanel; ;
	pDlgWnd->GetClientRect(&rcPanel);
	nWidth = rcPanel.Width();
	nHeight = rcPanel.Height();
}