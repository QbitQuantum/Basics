void CFileAskDlg::SetDlgReign()
{
	int UI_ROUNDRECT_WIDTH = 16;
	int UI_ROUNDRECT_HEIGHT = 16;

	CRect rc;
	POINT Points[6];
	GetClientRect(&rc);

	HRGN rgn1 = CreateRoundRectRgn(0, 0, rc.Width() / 2, rc.Height() / 2, UI_ROUNDRECT_WIDTH, UI_ROUNDRECT_HEIGHT);
	Points[0].x = 0;
	Points[0].y = UI_ROUNDRECT_HEIGHT;
	Points[1].x = 0;
	Points[1].y = rc.Height() + UI_ROUNDRECT_HEIGHT;
	Points[2].x = rc.Width() + UI_ROUNDRECT_WIDTH;
	Points[2].y = rc.Height() + UI_ROUNDRECT_HEIGHT;
	Points[3].x = rc.Width() + UI_ROUNDRECT_WIDTH;
	Points[3].y = 0;
	Points[4].x = UI_ROUNDRECT_WIDTH;
	Points[4].y = 0;
	Points[5].x = UI_ROUNDRECT_WIDTH;
	Points[5].y = UI_ROUNDRECT_HEIGHT;
	HRGN rgn2 = CreatePolygonRgn(Points, 6, ALTERNATE);
	CombineRgn(rgn1, rgn1, rgn2, RGN_OR);
	SetWindowRgn(rgn1, TRUE);

	DeleteObject(rgn2);
}