/*!
 @brief イメージの取得

 @param [in]    pSelectItem     選択データ
 @param [out]   bitmap          イメージ
 */
BOOL CImageFontDlg::GetBitmapImage(LPVOID pSelectItem, CImage &bitmap)
{
	CRect rect;
	GetClientRect(&rect);

	bitmap.Create(rect.Width(), rect.Height(), 32);

	HDC hDC = bitmap.GetDC();
	Gdiplus::Graphics graphics(hDC);
	graphics.Clear((Gdiplus::ARGB)Gdiplus::Color::White);

	CString strMessage;
	strMessage = _T("1234567890\n");
	strMessage += _T("abcdefghijklmnopqrstuvwxyz\n");
	strMessage += _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
	strMessage += _T("あいおえおかきくけこさしすせそたちつてとなにぬねの\n");
	strMessage += _T("はひふへほまみむめもやゆよらりるれろわをん\n");

	LOGFONT *pLogfont = (LOGFONT *) pSelectItem;
	Gdiplus::Font font(hDC, pLogfont);

	Gdiplus::RectF drawLayout(0, 0, (Gdiplus::REAL)rect.Width(), (Gdiplus::REAL)rect.Height());

	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	stringFormat.SetTrimming(Gdiplus::StringTrimmingNone);

	Gdiplus::SolidBrush brush((Gdiplus::ARGB)Gdiplus::Color::Black);

	graphics.SetTextRenderingHint((Gdiplus::TextRenderingHint) (GetSpaceKeyDownCount() % (int)Gdiplus::TextRenderingHintClearTypeGridFit));
	graphics.DrawString(strMessage, -1, &font, drawLayout, &stringFormat,&brush);


	bitmap.ReleaseDC();

	return TRUE;
}