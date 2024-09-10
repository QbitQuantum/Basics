void COXHyperBarRender::RenderToolbar(CDC * pDC, RECT * pRect, SIZE szBtn, POINT * pMouse, CBitmap * pOverlay)
{
	// The first time this is run after the toolbar is set up, 
	// call the method to fill the array of image data
	if (!m_buttonInfo)
	{
		if(m_pToolbar->GetToolBarCtrl().m_hWnd && m_pToolbar->GetToolBarCtrl().GetButtonCount())
		{
			Initialise(szBtn);
		}
		else return;
	}

	CImageList * const pImages = m_pToolbar->GetToolBarCtrl().GetImageList();

	const int width = pRect->right - pRect->left;
	const int height = pRect->bottom - pRect->top;

	// Create the bitmap used as a double buffer
	if (!m_buffer)
	{
		m_buffer = new CBitmap();
		// The buffer will be created when the mouse is not over the toolbar
		m_buffer->CreateCompatibleBitmap(pDC, width, height+(COXHyperBar::OffsetY * 2));
	}

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap * pOld = dc.SelectObject(m_buffer);

	// offset is the amount of space around each button
	const int offset = 4;
	const int buttonCount = m_pToolbar->GetToolBarCtrl().GetButtonCount();

	RECT rc;
	rc.right = width;
	rc.bottom = height;
	rc.top = rc.left = 0;

	// Reset the command, it will be set again if our mouse is over a button in the code below
	m_nCmd = -1;

	// This variable is used to accumulate the current position as we draw the buttons
	POINT ptDraw;
	ptDraw.x = ptDraw.y = 0;

	// We need to do this in two parts:
	// 1 - create a bitmap which has the overlay as a background and then the buttons drawn in the right positions
	// 2 - use the AlphaBlend function to blend this toolbar onto our device context.
	// The reason for this is that we need to use the Image List to draw the buttons transparently first,
	// then we need to do the alpha blend after that.
	CDC imageListDC;
	imageListDC.CreateCompatibleDC(pDC);
	CBitmap imageListBitmap;
	imageListBitmap.CreateCompatibleBitmap(pDC, width, height);
	imageListDC.SetStretchBltMode(COLORONCOLOR);
	dc.SetStretchBltMode(COLORONCOLOR);
	CBitmap * pOldImageList = imageListDC.SelectObject(&imageListBitmap);

	// If pOverlay != NULL, then draw the pOverlay onto both the buffer bitmap, and the bitmap that will be the source for alpha blending.
	if (pOverlay)
	{
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dc);
		CBitmap * pOld = dcBmp.SelectObject(pOverlay);

		imageListDC.BitBlt(0, 0, width, height, &dcBmp, 0, 0, SRCCOPY);
		dc.BitBlt(0, 0, width, height, &dcBmp, 0, 0, SRCCOPY);

		dcBmp.SelectObject(&pOld);
	}

	// rcBar becomes the rectangle we use to know the position of the toolbar within our CDC
	CRect rcBar = rc;

	if (pOverlay)
	{
		rcBar.InflateRect(0, -(COXHyperBar::OffsetY + 2));	
	}
	
	((COXHyperBar*)m_pToolbar)->RenderBackground(&dc, &rcBar);
	((COXHyperBar*)m_pToolbar)->RenderBackground(&imageListDC, rcBar);

	double * hypers = new double[buttonCount];
	double hyperTotal = 0.0;
	for(int j=0;j<buttonCount;++j)
	{
		// Skip seperators, which would otherwise kill the spacing, etc.
		if (!m_buttonInfo[j].commandID)
		{
			hypers[j] = 0;
			continue;
		}

		double distanceFromDOI = ColumnDistanceFromDOI(j, buttonCount, width, pMouse);

		// Plug the distance from zero (the DOI itself is at zero) into the hyperbolic function.
		// .05 -> .4 Focus
		hypers[j] = ValueAtX(distanceFromDOI, m_Focus);
		hyperTotal += hypers[j];
	}

	double factor = width/hyperTotal;

	for(int n=0;n<buttonCount;++n)
	{
		double distanceFromDOI = ColumnDistanceFromDOI(n, buttonCount, width, pMouse);

		double hyperbolic = hypers[n];

		// commandID is 0 for non buttons.
		if (!m_buttonInfo[n].commandID) continue;

		int alpha = 255;

		if (pMouse)
		{
			// The second param is always 1
			alpha = (int) (ValueAtX(distanceFromDOI, m_Focus) * 255);
		}

		// If we're not drawing the overlay window, we nust draw at the default width
		int imgWidth = (pMouse) ? (int)(factor * hyperbolic) - offset * 2 : m_buttonInfo[n].width ;
		int imgHeight = (pMouse)?(int)(m_buttonInfo[n].height * factor/m_buttonInfo[n].width * hyperbolic) : m_buttonInfo[n].height ;

		ptDraw.x += offset;
		ptDraw.y = (height -  imgHeight)/2;

		POINT pt;
		pt.x = pt.y = 0;
		// Draw the whole toolbar image
		SIZE szDraw;
		szDraw.cx = szDraw.cy = 0;

		CDC itemDC;
		itemDC.CreateCompatibleDC(&dc);
		CBitmap itemBitmap;
		itemBitmap.CreateCompatibleBitmap(&dc, m_buttonInfo[n].defaultWidth, m_buttonInfo[n].defaultHeight);
		CBitmap * pOldItemBitmap = itemDC.SelectObject(&itemBitmap);

		itemDC.FillSolidRect(0, 0,  m_buttonInfo[n].defaultWidth,  m_buttonInfo[n].defaultHeight, RGB(255,0,255));

		pImages->Draw(&itemDC, m_buttonInfo[n].bitmapIndex, pt, ILD_TRANSPARENT);

		if (pMouse)
		{
			// Check if this is the active button
			CRect rcDraw(ptDraw.x, ptDraw.y, imgWidth + ptDraw.x, ptDraw.y + imgHeight);

			if (PtInRect(&rcDraw, *pMouse))
			{
				m_nCmd = m_buttonInfo[n].commandID;
			}
		}

		// Draw the button transparently onto the image list render DC
		TransparentBlt(imageListDC, ptDraw.x, ptDraw.y, imgWidth, imgHeight, itemDC, 0, 0, m_buttonInfo[n].defaultWidth, m_buttonInfo[n].defaultHeight, RGB(255, 0, 255));

		// Now blend it back across the main DC
		BLENDFUNCTION bf;
		bf.AlphaFormat = 0;
		bf.BlendFlags = 0;
		bf.BlendOp =  0;
		bf.SourceConstantAlpha = (BYTE)alpha;
		AlphaBlend(dc, ptDraw.x, ptDraw.y, imgWidth, imgHeight, imageListDC, ptDraw.x, ptDraw.y, imgWidth, imgHeight, bf);

		itemDC.SelectObject(pOldItemBitmap);

		ptDraw.x += offset + imgWidth;
	}

	pDC->BitBlt(0, 0, width,  height, &dc, 0, 0, SRCCOPY);

	imageListDC.SelectObject(pOldImageList);

	dc.SelectObject(pOld);

	delete [] hypers;

	// Once the paint has occurred, set the flag to say if we drew over the main toolbar, or the floating window.
	((COXHyperBar*)m_pToolbar)->m_bHasRedrawn = (pMouse == NULL);
 }