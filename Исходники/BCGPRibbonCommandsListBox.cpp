//******************************************************************************
void CBCGPRibbonCommandsListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	ASSERT (lpMIS != NULL);

	CClientDC dc (this);
	CFont* pOldFont = (CFont*) dc.SelectStockObject (DEFAULT_GUI_FONT);
	ASSERT_VALID (pOldFont);

	TEXTMETRIC tm;
	dc.GetTextMetrics (&tm);

	lpMIS->itemHeight = tm.tmHeight + 6;

	dc.SelectObject (pOldFont);
}