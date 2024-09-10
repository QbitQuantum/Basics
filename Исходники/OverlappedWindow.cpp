LRESULT COverlappedWindow::OnControlColorEdit(HDC hdc)
{
	SetBkColor(hdc, backgroundColor);
	SetDCBrushColor(hdc, backgroundColor);
	SetTextColor(hdc, fontColor);
	return reinterpret_cast<LRESULT>(GetStockObject(DC_BRUSH));
}