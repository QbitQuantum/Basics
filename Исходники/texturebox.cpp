//-----------------------------------------------------------------------------
// Purpose: 
// Input  : pDC - 
// Output : Returns TRUE on success, FALSE on failure.
//-----------------------------------------------------------------------------
BOOL CTextureBox::OnEraseBkgnd(CDC *pDC) 
{
	CRect r;
	GetUpdateRect(r);
	pDC->SetROP2(R2_COPYPEN);
	FillRect(pDC->m_hDC, r, HBRUSH(GetStockObject(BLACK_BRUSH)));
	return TRUE;
}