void RectAlphaDrawer::Draw(CDC& dc, CRect& rc, BYTE Alpha)
{
	if (m_pDC == NULL)
		CreateInternalDC(&dc);
	BLENDFUNCTION blFunc = {AC_SRC_OVER, 0, Alpha, 0}; 
	dc.AlphaBlend(rc.left, rc.top, rc.Width(), rc.Height(), GetInternalDC(), 0, 0, s_InternalRect.Width(), s_InternalRect.Height(), blFunc);
	if (m_drawOptions & DO_DrawNotAlphaPerigram)
		dc.Draw3dRect(&rc, m_bkColor, m_bkColor);
}