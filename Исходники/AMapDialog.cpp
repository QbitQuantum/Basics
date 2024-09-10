void CAMapDialog::OnPaint()
{
	CPaintDC dc(this);
	CDC dcMem;
	RECT client;
	CBitmap * pOld = NULL;

	GetClientRect(&client);

	if(!m_pNDBViewer)
		return CDialog::OnPaint();

	dcMem.CreateCompatibleDC(&dc);
	if(!m_pAMap)
	{
		// First paint, we need to walk the AMaps and create the bitmap.
		CWaitCursor wait;
		int numPixel = client.right * client.bottom;
		IB search = ibAMapBase;
		IB size = 0;
		CB * freeSpace = new CB[numPixel];
		CB cbPixel = (m_pNDBViewer->GetHeader().root.ibFileEof / numPixel) + 1; // round up
		COLORREF cFull = m_pNDBViewer->GetHeader().root.fAMapValid ? c_Full : c_FullInvalid;
		int iFullR = GetRValue(cFull);
		int iFullG = GetGValue(cFull);
		int iFullB = GetBValue(cFull);
		COLORREF cFree = m_pNDBViewer->GetHeader().root.fAMapValid ? c_Free : c_FreeInvalid;
		int iFreeR = GetRValue(cFree);
		int iFreeG = GetGValue(cFree);
		int iFreeB = GetBValue(cFree);

		for(int i = 0; i < numPixel; i++)
			freeSpace[i] = CB(0);

		// Search the file for free space
		while(search < m_pNDBViewer->GetHeader().root.ibFileEof)
		{
			size = m_pNDBViewer->IsFree(search);
			if(size)
				MarkSpaceAsFree(freeSpace, cbPixel, numPixel, search, search+size);
			else
				size += cbPerSlot;

			search += size;
		}

		// allocate the bitmap
		m_pAMap = new CBitmap();
		m_pAMap->CreateCompatibleBitmap(&dc, client.right, client.bottom);
		pOld = dcMem.SelectObject(m_pAMap);
		
		for(int j = 0; j < client.bottom; j++)
		{
			for(int i = 0; i < client.right; i++)
			{
				// if this pixel extends past eof, just draw the eof pixel
				// the confusing +1 is because we want the end of the region mapped
				// by this pixel, which is the start of the region mapped by the next
				// pixel
				if((j * client.right + i + 1) * cbPixel <= m_pNDBViewer->GetHeader().root.ibFileEof)
				{
					double diff = (double)freeSpace[(j * client.right) + i] / (double)cbPixel;

					if(diff < 0) diff = 0.0;
					// make sure even the smallest bit of free space shows up
					if(diff > 0.0 && diff < c_minShade) diff = c_minShade;
					if(diff > 1.0) diff = 1.0;
					COLORREF c = RGB(
						(int)((double)iFullR - (iFullR*diff) + (iFreeR*diff)) & 0x00FF,
						(int)((double)iFullG - (iFullG*diff) + (iFreeG*diff)) & 0x00FF,
						(int)((double)iFullB - (iFullB*diff) + (iFreeB*diff)) & 0x00FF
						);
					dcMem.SetPixel(i, j, c);
				}
				else
				{
					dcMem.SetPixel(i, j, c_AMapPastEOF);
				}
				
			}
		}
		delete [] freeSpace;
		m_pNDBViewer->CacheAMapBitmap(m_pAMap);
	}
	else
	{
		pOld = dcMem.SelectObject(m_pAMap);
	}

	dc.BitBlt(client.left, client.top, client.right, client.bottom, &dcMem, 0, 0, SRCCOPY);
	dcMem.SelectObject(pOld);
}