void CGraphPanel::UpdateGraphWindow(LPCRECT rect)
{
    if(!offscreen)
    {
		return;
    };
    CRect r;
    if (rect==NULL) GetClientRect(&r);
	else r.CopyRect(rect);

    //do paint here
    CDC* dc = offscreen->GetDibCDC();
    if (dc != NULL)
    {
	CRect rect_to_draw;
	GetClientRect(rect_to_draw);
	DrawToDC(dc, rect_to_draw);
	offscreen->SetReady(TRUE);
    };

    CDC* cdc = GetDC();
    DoRedraw(cdc, &r);
    ReleaseDC(cdc);
}