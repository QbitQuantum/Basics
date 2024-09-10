void CItemData::Draw(CDrawContext* pContext, const CRect& crContent, int nSubItem)
{
	TRACE("CItemData without Draw() method\n");
	CDC* pDC = pContext->GetDC();

	CBrush cbDummy(RGB(255,128,64));
	pDC->FillRect(&crContent, &cbDummy);

	pContext->ReleaseDC();
}