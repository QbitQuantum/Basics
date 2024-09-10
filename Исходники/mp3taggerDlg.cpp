void Cmp3taggerDlg::CleanCover()
{
	CBitmap nocover;

	nocover.LoadBitmap(IDB_NOCOVER);

	CImage img;
	img.Attach(nocover);

	CDC *pdc = m_stCover.GetDC();
	HDC hdc = pdc->GetSafeHdc();
	SetStretchBltMode(hdc, HALFTONE);
	img.StretchBlt(hdc, 0, 0, 150, 150);
}