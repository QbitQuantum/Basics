void CRibbonListFontButton::OnShowPopupMenu ()
{
	ASSERT_VALID (this);

	CBCGPBaseRibbonElement::OnShowPopupMenu ();

	if (m_sizeMaxText == CSize (0, 0))
	{
		CBCGPRibbonBar* pRibbonBar = GetTopLevelRibbonBar ();
		ASSERT_VALID (pRibbonBar);

		CClientDC dc (pRibbonBar);
		CFont* pOldFont = dc.SelectObject (&globalData.fontBold);

		for (int i = 0; i < m_arItems.GetSize (); i++)
		{
			CSize szText = dc.GetTextExtent (m_arItems [i].m_Caption);

			for (int j = 0; j < 2; j++)
			{
				LOGFONT& lf = m_arItems [i].m_Font[j];

				CFont font;
				font.CreateFontIndirect (&lf);
				dc.SelectObject (&font);

				CSize szText2 = dc.GetTextExtent (lf.lfFaceName);

				szText.cx = max (szText.cx, szText2.cx);
				szText.cy += szText2.cy;
			}

			m_arItems [i].m_Height = szText.cy;

			m_sizeMaxText.cx = max (m_sizeMaxText.cx, szText.cx);
			m_sizeMaxText.cy = max (m_sizeMaxText.cy, szText.cy);
		}

		dc.SelectObject (pOldFont);
	}

	CBCGPRibbonPaletteButton::OnShowPopupMenu ();
}