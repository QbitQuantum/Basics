CPaintHelper::CPaintHelper(CUIGlobals &uig, HDC hDC) :
	m_uig(uig), m_priv_hDC(hDC), m_hDC(m_priv_hDC),
	m_eFont(UIF_VOID),
	m_eBrush(UIB_VOID),
	m_ePen(UIP_VOID),
	m_eText(UIC_VOID),
	m_eBk(UIC_VOID),
	m_hOldFont(NULL), m_hOldBrush(NULL), m_hOldPen(NULL),
	m_bOldFont(FALSE), m_bOldBrush(FALSE), m_bOldPen(FALSE)
{
	if (m_hDC != NULL)
	{
		m_oldtextcolor = GetTextColor(m_hDC);
		m_oldbkcolor = GetBkColor(m_hDC);
		m_oldbkmode = GetBkMode(m_hDC);
	}
}