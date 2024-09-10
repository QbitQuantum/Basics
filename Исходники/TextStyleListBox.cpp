void TextStyleListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

//CRect members to store the position of the items
CRect rItem;
CDC* dc = CDC::FromHandle(lpDrawItemStruct->hDC);

if ((int)lpDrawItemStruct->itemID < 0)
{
// If there are no elements in the CListBox
// based on whether the list box has Focus  or not 
// draw the Focus Rect or Erase it,
if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && (lpDrawItemStruct->itemState & ODS_FOCUS))
{
    dc->DrawFocusRect(&lpDrawItemStruct->rcItem);
}
else if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && !(lpDrawItemStruct->itemState & ODS_FOCUS)) 
{
    dc->DrawFocusRect(&lpDrawItemStruct->rcItem); 
}
   return;
}


// String to store the text
CString csStyle;

// Get the item text.
GetText(lpDrawItemStruct->itemID, csStyle);

//Initialize the CListBox Item's row size
rItem = lpDrawItemStruct->rcItem;

UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
if (GetStyle() & LBS_USETABSTOPS)
nFormat |= DT_EXPANDTABS;


	COLORREF cText;
	COLORREF cBg;
	CFont font;
	font.CreatePointFont(100,"Times New Roman"); 
	LgbColorsDef cColors;
	GetColors(csStyle, cColors);
	cText = RGB(cColors.m_iFgRed, cColors.m_iFgGreen, cColors.m_iFgBlue);
	cBg = RGB(cColors.m_iBgRed, cColors.m_iBgGreen, cColors.m_iBgBlue);

// If CListBox item selected, draw the highlight rectangle.
// Or if CListBox item deselected, draw the rectangle using the window color.
if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&
(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
{
    CBrush br(::GetSysColor(COLOR_HIGHLIGHT));
    dc->FillRect(&rItem, &br);
}
else if (!(lpDrawItemStruct->itemState & ODS_SELECTED) && (lpDrawItemStruct->itemAction & ODA_SELECT)) 
{
	dc->FillSolidRect(&rItem, cBg);
    //CBrush br(::GetSysColor(COLOR_WINDOW));
    //dc->FillRect(&rItem, &br);
}
else if (!(lpDrawItemStruct->itemState & ODS_SELECTED)) {
	dc->FillSolidRect(&rItem, cBg);
}

// If the CListBox item has focus, draw the focus rect.
// If the item does not have focus, erase the focus rect.
if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && (lpDrawItemStruct->itemState & ODS_FOCUS))
{
    dc->DrawFocusRect(&rItem); 
}
else if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && !(lpDrawItemStruct->itemState & ODS_FOCUS))
{
    dc->DrawFocusRect(&rItem); 
}

// To draw the Text in the CListBox set the background mode to Transparent.
int iBkMode = dc->SetBkMode(TRANSPARENT);

	dc->SetBkColor(cBg);
	dc->SetTextColor(cText);
	dc->SelectObject(&font);

	//Draw the Text
	dc->TextOut(rItem.left, rItem.top, csStyle);

	// create memory device context
	CDC* pSrcMemDC = new CDC;
	assert( NULL != pSrcMemDC );

	pSrcMemDC->CreateCompatibleDC(dc);

	// RGB + Alpha
	int totalBytes = rItem.Width() * rItem.Height() * 4;

	// create bitmap
	CBitmap* pSrcBmp = new CBitmap;
	assert( NULL != pSrcBmp );

	// initialize
	pSrcBmp->CreateCompatibleBitmap(dc, rItem.Width(), rItem.Height());
	pSrcMemDC->SelectObject(pSrcBmp);

	void *byteArr = new BYTE [ totalBytes ];
	assert( NULL != byteArr );

	BYTE *tmp = (BYTE *) byteArr;

	// set the flagged array to the bitmap
	pSrcBmp->SetBitmapBits( totalBytes, byteArr );

	// Write text using EHS font blitter
	LgbTextIcon dumTextIcon;
	CString csFont = GetFont(csStyle);
	EhsWidgetClass* pWidget;
	EhsTgtViewportSurfaceClass* pSurface = NULL;
	EhsGraphicsColourClass xFgColour, xBgColour;
	EhsGraphicsFontClass* pFont = dumTextIcon.GetFontPtr(csFont);

	if (0) {
		//if (pFont) {
			//xFgColour = EhsGraphicsColour_argb(cColors.m_iFgRed, cColors.m_iFgGreen, cColors.m_iFgBlue, cColors.m_iFgAlpha);
			xFgColour = EhsGraphicsColour_argb(150, 150, 150, 150);
			xBgColour = EhsGraphicsColour_argb(255, 255, 255, 0);
			EhsWidgetTable_init(&EhsWidgetTable);
			pWidget = EhsWidgetTextbox_init(rItem.left, rItem.top, 0, rItem.Width(), rItem.Height(), xFgColour, xBgColour, pFont);
			EhsWidget_create(pWidget);
			EhsGraphicsColourClass xPalette[2];
			xPalette[0] = EHS_WIDGET_TEXTBOX(pWidget).xBgColour;
			xPalette[1] = EHS_WIDGET_TEXTBOX(pWidget).xFgColour;
		
			pSurface = EhsTgtViewportSurface_create(NULL,pWidget->xCurRect.nWidth,pWidget->xCurRect.nHeight,EHS_GRAPHICS_COLOUR_A1,xPalette,2);

			if (pSurface) {
			EhsWidgetTextbox_draw(pWidget, NULL, NULL, pSurface);

			// Copy the written data back from the bitmap
			pSrcBmp->GetBitmapBits( totalBytes, byteArr );

			// Blit Text
			int x,y;
		
			for (y = 0; y < rItem.Height(); y++) {
				int nPixIdx = y * rItem.Width() * 4;
				int nBmpIdx = y * ((pSurface->nWid+7)/8);
				for (x = 0; x < rItem.Width(); x++) {
					int nBit = 1 << (7u - (x % 8u));
					int nX = x*4;
					if ((nBit & EhsTgtViewportSurface_bitmap(pSurface)[nBmpIdx + x/8]) == nBit) {
						tmp[nPixIdx+nX] = (unsigned char) cColors.m_iFgBlue;
						tmp[nPixIdx+nX+1] = (unsigned char) cColors.m_iFgGreen;
						tmp[nPixIdx+nX+2] = (unsigned char) cColors.m_iFgRed;
						tmp[nPixIdx+nX+3] = (unsigned char) cColors.m_iFgAlpha;
					} else {
						tmp[nPixIdx+nX] = 255;
						tmp[nPixIdx+nX+1] = 255;
						tmp[nPixIdx+nX+2] = 255;
						tmp[nPixIdx+nX+3] = 0;
					}
				}
			}
		
			if (!pWidget->bOptimiseForSpeed) {
				EhsTgtViewportSurface_destroy(NULL, pSurface);
			}
			}
		}
/*
	// Copy this data into bitmap
	pSrcBmp->SetBitmapBits( totalBytes, byteArr );

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA; 

	AlphaBlend(
		dc->GetSafeHdc(),
		rItem.left, 
		rItem.top, 
		rItem.Width(),
		rItem.Height(),
		pSrcMemDC->GetSafeHdc(),
		0,
		0,
		rItem.Width(),
		rItem.Height(),
		bf );
		
	int PicSizeX = 30;
	int PicSizeY = 16;
	pSrcMemDC->SelectObject(pSrcBmp);
	dc->BitBlt(rItem.left+5, rItem.top+1, PicSizeX, PicSizeY, pSrcMemDC, 0, 0, SRCCOPY);
*/
	pSrcMemDC->DeleteDC();
	delete pSrcMemDC;

	pSrcBmp->DeleteObject();
	delete pSrcBmp;

	delete [] byteArr;

}