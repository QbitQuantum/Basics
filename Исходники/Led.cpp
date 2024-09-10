///////////////////////////////////////////////////////////////////////////////
// Name:		SetLed
// Description:	This method will draw the LED to the specified DC.
//
// Entry:
//				CDC *pDC - DC to draw to
//
//				int iLedColor - Where color is defined by:
//			 		LED_COLOR_RED
//					LED_COLOR_GREEN
//					LED_COLOR_YELLOW
//					LED_COLOR_BLUE
//
//				int iMode - where mode is defined by:
//					LED_ON
//					LED_OFF
//					LED_DISABLED
//
//				int iShape - where shape is defined by:
//					LED_ROUND
//					LED_SQUARE
///////////////////////////////////////////////////////////////////////////////
void CLed::DrawLed(CDC *pDC,int nLEDColor, int nMode, int nShape)
{
	CRect rect;
	GetClientRect(&rect);

	//
	// Center led within an oversized window
	//
	if(rect.Width() >= LED_SIZE && rect.Height() >= LED_SIZE)
	{
		int nWidth = rect.Width();
		int nHeight = rect.Height();
		rect.left += (nWidth - LED_SIZE)/2;
		rect.right -= (nWidth - LED_SIZE)/2;
		rect.top += (nHeight - LED_SIZE)/2;
		rect.bottom -= (nHeight - LED_SIZE)/2;
	}

	//
	// Prepare temporary DCs and bitmaps
	//
	CBitmap TransBitmap;
	TransBitmap.CreateBitmap(LED_SIZE,LED_SIZE,1,1,NULL);
	CBitmap bitmapTemp;
	CBitmap* pBitmap = &m_LedBitmap;
	CDC srcDC;
	CDC dcMask;
	CDC TempDC;
	TempDC.CreateCompatibleDC(pDC);
	srcDC.CreateCompatibleDC(pDC);
	dcMask.CreateCompatibleDC(pDC);

	CBitmap* pOldBitmap = srcDC.SelectObject(pBitmap);
	CBitmap* pOldMaskbitmap = dcMask.SelectObject(&TransBitmap);
	bitmapTemp.CreateCompatibleBitmap(pDC,LED_SIZE,LED_SIZE);

	//
	// Work with tempDC and bitmapTemp to reduce flickering
	//
	CBitmap *pOldBitmapTemp = TempDC.SelectObject(&bitmapTemp);
	TempDC.BitBlt(0, 0, LED_SIZE, LED_SIZE, pDC, rect.left, rect.top, SRCCOPY); 

	//
	// Create mask
	//
	COLORREF OldBkColor = srcDC.SetBkColor(RGB(255,0,255));
	dcMask.BitBlt(0, 0, LED_SIZE, LED_SIZE,&srcDC, nMode*LED_SIZE, nLEDColor+nShape, SRCCOPY); 
	TempDC.SetBkColor(OldBkColor);

	//
	// Using the IDB_LEDS bitmap, index into the bitmap for the appropriate
	// LED. By using the mask color (RGB(255,0,255)) a mask has been created
	// so the bitmap will appear transparent.
	//
	TempDC.BitBlt(0, 0, LED_SIZE, LED_SIZE, &srcDC, nMode*LED_SIZE, nLEDColor+nShape, SRCINVERT); 
	TempDC.BitBlt(0, 0, LED_SIZE, LED_SIZE,&dcMask, 0, 0, SRCAND); 
	TempDC.BitBlt(0, 0, LED_SIZE, LED_SIZE, &srcDC, nMode*LED_SIZE, nLEDColor+nShape, SRCINVERT); 

	//
	// Since the actual minipulation is done to tempDC so there is minimal
	// flicker, it is now time to draw the result to the screen.
	//
	pDC->BitBlt(rect.left, rect.top, LED_SIZE, LED_SIZE, &TempDC, 0, 0, SRCCOPY); 
	
	//
	// House cleaning
	//
	srcDC.SelectObject(pOldBitmap);
	dcMask.SelectObject(pOldMaskbitmap);
	TempDC.SelectObject(pOldBitmapTemp);
	VERIFY(srcDC.DeleteDC());
	VERIFY(dcMask.DeleteDC());
	VERIFY(TempDC.DeleteDC());
	VERIFY(TransBitmap.DeleteObject());
	VERIFY(bitmapTemp.DeleteObject());
}