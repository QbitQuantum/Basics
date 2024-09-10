//*****************************************************************************************
void CBCGPTreeMap::OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& rectClip, DWORD dwFlags)
{
	if (IsDirty())
	{
		m_Root.RecalcLayout(pGM);
		SetDirty(FALSE);
	}

	if ((dwFlags & BCGP_DRAW_STATIC) == 0)
	{
		return;
	}

	if (m_Root.m_arSubNodes.GetSize() > 0)
	{
		pGM->FillRectangle(m_rect, m_brFill);
		m_Root.OnDraw(pGM, rectClip.IsRectEmpty() ? m_rect : rectClip, m_brFill);
	}
}