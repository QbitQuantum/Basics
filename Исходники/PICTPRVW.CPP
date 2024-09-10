void CDocumentPreview::SizePreviewWindow(int nWidth, int nHeight)
{
	m_crPreview.left = (m_crFullPreview.left+m_crFullPreview.right-nWidth)/2;
	m_crPreview.top = (m_crFullPreview.top+m_crFullPreview.bottom-nHeight)/2;
	m_crPreview.right = m_crPreview.left + nWidth;
	m_crPreview.bottom = m_crPreview.top + nHeight;

	CRect r = m_crPreview;

	// We can't both set and show the window at the same time
	// with SetWindowPos. So, we call it twice as needed.
	CWnd* pPreviewWnd = GetPreviewWnd();
	pPreviewWnd->SetWindowPos(NULL, r.left-1, r.top-1, nWidth+2, nHeight+2,
									  SWP_NOZORDER | SWP_NOREDRAW);

	pPreviewWnd->SetWindowPos(NULL, 0, 0, 0, 0,
									  SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW | SWP_SHOWWINDOW);

	// Invalidate ourselves to avoid background draw.
	CWnd* pDialog = GetDialog();
	pDialog->ClientToScreen(&m_crPreview);
	pPreviewWnd->ScreenToClient(&m_crPreview);
	r = m_crPreview;
	r.left--;
	r.top--;
	r.right++;
	r.bottom++;
	pPreviewWnd->InvalidateRect(&r, FALSE);
}