HBRUSH JHCEdit::OnCtlColorEdit(CDCHandle dc, CEdit edit)
{
	dc.SetTextColor(colorTx);
	dc.SetBkColor(colorBg);
	dc.SetDCBrushColor(colorBg);
	return HBRUSH(GetStockObject(DC_BRUSH));
}