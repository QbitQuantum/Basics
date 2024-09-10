void CPreviewBar::OnSize(UINT nType, int cx, int cy) 
{
	CSizingControlBarG::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rc;
    GetClientRect(rc);

	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	if(pFrame==NULL)
		return;

	CImgClassCBDoc* pDoc=(CImgClassCBDoc*)pFrame->GetActiveDocument();
	if (pDoc == NULL)
	{
		return;
	}

	if(pDoc->m_pSelectedImage==NULL)
	{
		rc.SetRectEmpty();
		m_wndCanvas.MoveWindow(rc);
	}
	else
	{
		const int nWidth=rc.Width();
		const int nHeight=rc.Height();
		const float fRatio=(float)nHeight/nWidth;
		const float fImgRatio=(float)pDoc->m_pSelectedImage->GetHeight()/pDoc->m_pSelectedImage->GetWidth();

		int XDest, YDest, nDestWidth, nDestHeight;
		if(fImgRatio > fRatio)
		{
			nDestWidth=nHeight/fImgRatio;
			XDest=(nWidth-nDestWidth)/2;
			YDest=0;
			nDestHeight=nHeight;
		}
		else
		{
			XDest=0;
			nDestWidth=nWidth;
			nDestHeight=nWidth*fImgRatio;
			YDest=(nHeight-nDestHeight)/2;
		}
		CRect rect(XDest, YDest, XDest+nDestWidth, YDest+nDestHeight);
		m_wndCanvas.MoveWindow(rect);
		m_wndCanvas.Invalidate();
	}
}