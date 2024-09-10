void CMFCMDIPlayerView::OnSize(UINT nType, int cx, int cy) 
{	
	CView::OnSize(nType, cx, cy);

	if (cy && cx)
	{
		// calculate the size of the frame
		CFrameWnd* pFrame = GetParentFrame();
		if (pFrame != NULL)
		{
			CRect rectSized(0, 0, cx, cy);
			pFrame->CalcWindowRect(rectSized);
			pFrame->SetWindowPos(this,0,0,rectSized.Width() + 4,rectSized.Height()+ 4, SWP_NOZORDER | SWP_NOMOVE );

		}
	}
}