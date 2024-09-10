CBitmap* COrnament::GetImage(void)
{
	CDC *pDC = m_pContext->GetDC();
	ASSERT(pDC != NULL);

	// If the image bitmap is not valid give the current state, free the
	// current bitmap and build the new one.
			
	if (ImageNeeded())
	{
		m_bmImage.DeleteObject();
	}

	// Check if we need to build a new bitmap.		
		
	if (m_bmImage.GetSafeHandle() == NULL)
	{
		// Create the bitmap for the image.
			
		CRect crImage(0, 0, Max(CurrentState()->m_czExtent.cx, 1), Max(CurrentState()->m_czExtent.cy, 1));
		
		if (m_bmImage.CreateCompatibleBitmap(pDC, crImage.Width(), crImage.Height()))
		{
			// Create a memory compatible DC and select the new bitmap into it.
				
			CDC ImageDC;
				
			if (ImageDC.CreateCompatibleDC(pDC))
			{
				CBrush cbTransparent(RGB(0,0,0));
				
				int nContext;
							
				if ((nContext = ImageDC.SaveDC()) != 0)
				{
					ImageDC.SetMapMode(MM_TEXT);
						
					if (ImageDC.SelectObject(&m_bmImage) != NULL)
					{
						// Create the image. Pixels that are transparent should be set to sero (black).
							
						ImageDC.FillRect(&crImage, &cbTransparent);
						DrawImage(&ImageDC);
						ClearImageNeeded();
					}
						
					ImageDC.RestoreDC(nContext);
				}
			}
		}
	}
	
	m_pContext->ReleaseDC();

	ASSERT(m_bmImage.GetSafeHandle() != NULL);
	
	if (m_bmImage.GetSafeHandle() == NULL)
	{
		return NULL;
	}
	
	return &m_bmImage;
}