CSize CGumpStatic::GetTextExtend() const
{
	CGumpEditorDoc* pDoc = GfxGetGumpDocument();
	ASSERT(pDoc);

	CWnd* pWnd = AfxGetMainWnd(); //pDoc->FindView(RUNTIME_CLASS(CGumpEditorView));

	CDC* pDC = pWnd->GetDC();

	CFont* pFont = pDoc->GetFont(m_fontId);
	CFont* pOld = pDC->SelectObject(pFont);

	pDC->SelectObject(pFont);

	CSize size = pDC->GetTextExtent(GetTitle());

	pDC->SelectObject(pOld);

	return size;
}