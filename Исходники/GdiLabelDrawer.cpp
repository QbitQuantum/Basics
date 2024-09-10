// *********************************************************************
// 					MeasureString()										
// *********************************************************************
void GdiLabelDrawer::MeasureString(CLabelInfo* lbl, CRect& rect)
{
	DrawTextW(_dc->m_hDC, lbl->text, -1, rect, DT_CALCRECT);

	// frame for GDI is very narrow; so we'll enlarge it a bit					
	rect.left -= rect.Height() / 6;
	rect.right += rect.Height() / 6;
}