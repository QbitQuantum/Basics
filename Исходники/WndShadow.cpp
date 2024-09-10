void CWndShadow::MakeShadow(UINT32 *pShadBits, HWND hParent, RECT *rcParent)
{
	// The shadow algorithm:
	// Get the region of parent window,
	// Apply morphologic erosion to shrink it into the size (ShadowWndSize - Sharpness)
	// Apply modified (with blur effect) morphologic dilation to make the blurred border
	// The algorithm is optimized by assuming parent window is just "one piece" and without "wholes" on it
	
	// Get the region of parent window,
	HRGN hParentRgn = CreateRectRgn(0, 0, 0, 0);
	GetWindowRgn(hParent, hParentRgn);
	
	// Determine the Start and end point of each horizontal scan line
	SIZE szParent = { rcParent->right - rcParent->left, rcParent->bottom - rcParent->top };
	SIZE szShadow = { szParent.cx + 2 * m_nSize, szParent.cy + 2 * m_nSize };
	// Extra 2 lines (set to be empty) in ptAnchors are used in dilation
	int nAnchors = max(szParent.cy, szShadow.cy);   // # of anchor points pares
	int(*ptAnchors)[2] = new int[nAnchors + 2][2];
	int(*ptAnchorsOri)[2] = new int[szParent.cy][2];   // anchor points, will not modify during erosion
	ptAnchors[0][0] = szParent.cx;
	ptAnchors[0][1] = 0;
	ptAnchors[nAnchors + 1][0] = szParent.cx;
	ptAnchors[nAnchors + 1][1] = 0;
	if (m_nSize > 0)
	{
		// Put the parent window anchors at the center
		for (int i = 0; i < m_nSize; i++)
		{
			ptAnchors[i + 1][0] = szParent.cx;
			ptAnchors[i + 1][1] = 0;
			ptAnchors[szShadow.cy - i][0] = szParent.cx;
			ptAnchors[szShadow.cy - i][1] = 0;
		}
		ptAnchors += m_nSize;
	}
	for (int i = 0; i < szParent.cy; i++)
	{
		// find start point
		int j;
		for (j = 0; j < szParent.cx; j++)
		{
			if (PtInRegion(hParentRgn, j, i))
			{
				ptAnchors[i + 1][0] = j + m_nSize;
				ptAnchorsOri[i][0] = j;
				break;
			}
		}
	
		if (j >= szParent.cx) // Start point not found
		{
			ptAnchors[i + 1][0] = szParent.cx;
			ptAnchorsOri[i][1] = 0;
			ptAnchors[i + 1][0] = szParent.cx;
			ptAnchorsOri[i][1] = 0;
		}
		else
		{
		// find end point
			for (j = szParent.cx - 1; j >= ptAnchors[i + 1][0]; j--)
			{
				if (PtInRegion(hParentRgn, j, i))
				{
					ptAnchors[i + 1][1] = j + 1 + m_nSize;
					ptAnchorsOri[i][1] = j + 1;
					break;
				}
			}
		}
	}

	if (m_nSize > 0)
		ptAnchors -= m_nSize;   // Restore pos of ptAnchors for erosion
	int(*ptAnchorsTmp)[2] = new int[nAnchors + 2][2];  // Store the result of erosion
	// First and last line should be empty
	ptAnchorsTmp[0][0] = szParent.cx;
	ptAnchorsTmp[0][1] = 0;
	ptAnchorsTmp[nAnchors + 1][0] = szParent.cx;
	ptAnchorsTmp[nAnchors + 1][1] = 0;
	int nEroTimes = 0;
	// morphologic erosion
	for (int i = 0; i < m_nSharpness - m_nSize; i++)
	{
		nEroTimes++;
		//ptAnchorsTmp[1][0] = szParent.cx;
		//ptAnchorsTmp[1][1] = 0;
		//ptAnchorsTmp[szParent.cy + 1][0] = szParent.cx;
		//ptAnchorsTmp[szParent.cy + 1][1] = 0;
		for (int j = 1; j < nAnchors + 1; j++)
		{
			ptAnchorsTmp[j][0] = max(ptAnchors[j - 1][0], max(ptAnchors[j][0], ptAnchors[j + 1][0])) + 1;
			ptAnchorsTmp[j][1] = min(ptAnchors[j - 1][1], min(ptAnchors[j][1], ptAnchors[j + 1][1])) - 1;
		}
		// Exchange ptAnchors and ptAnchorsTmp;
		int(*ptAnchorsXange)[2] = ptAnchorsTmp;
		ptAnchorsTmp = ptAnchors;
		ptAnchors = ptAnchorsXange;
	}
	
	// morphologic dilation
	ptAnchors += (m_nSize < 0 ? -m_nSize : 0) + 1;   // now coordinates in ptAnchors are same as in shadow window
	// Generate the kernel
	int nKernelSize = m_nSize > m_nSharpness ? m_nSize : m_nSharpness;
	int nCenterSize = m_nSize > m_nSharpness ? (m_nSize - m_nSharpness) : 0;
	UINT32 *pKernel = new UINT32[(2 * nKernelSize + 1) * (2 * nKernelSize + 1)];
	UINT32 *pKernelIter = pKernel;
	for (int i = 0; i <= 2 * nKernelSize; i++)
	{
		for (int j = 0; j <= 2 * nKernelSize; j++)
		{
			double dLength = sqrt((i - nKernelSize) * (i - nKernelSize) + (j - nKernelSize) * (double)(j - nKernelSize));
			if (dLength < nCenterSize)
				*pKernelIter = m_nDarkness << 24 | PreMultiply(m_Color, m_nDarkness);
			else if (dLength <= nKernelSize)
			{
				UINT32 nFactor = ((UINT32)((1 - (dLength - nCenterSize) / (m_nSharpness + 1)) * m_nDarkness));
				*pKernelIter = nFactor << 24 | PreMultiply(m_Color, nFactor);
			}
			else
				*pKernelIter = 0;
				//TRACE("%d ", *pKernelIter >> 24);
				pKernelIter++;
		}
		//TRACE("\n");
	}
	// Generate blurred border
	for (int i = nKernelSize; i < szShadow.cy - nKernelSize; i++)
	{
		int j;
		if (ptAnchors[i][0] < ptAnchors[i][1])
		{
	
			// Start of line
			for (j = ptAnchors[i][0];j < min(max(ptAnchors[i - 1][0], ptAnchors[i + 1][0]) + 1, ptAnchors[i][1]);j++)
			{
				for (int k = 0; k <= 2 * nKernelSize; k++)
				{
					UINT32 *pPixel = pShadBits +
									(szShadow.cy - i - 1 + nKernelSize - k) * szShadow.cx + j - nKernelSize;
					UINT32 *pKernelPixel = pKernel + k * (2 * nKernelSize + 1);
					for (int l = 0; l <= 2 * nKernelSize; l++)
					{
						if (*pPixel < *pKernelPixel)
							*pPixel = *pKernelPixel;
							
						pPixel++;
						pKernelPixel++;
					}
				 }
			}   // for() start of line
		
			// End of line
			for (j = max(j, min(ptAnchors[i - 1][1], ptAnchors[i + 1][1]) - 1);j < ptAnchors[i][1];j++)
			{
				for (int k = 0; k <= 2 * nKernelSize; k++)
				{
					UINT32 *pPixel = pShadBits +(szShadow.cy - i - 1 + nKernelSize - k) * szShadow.cx + j - nKernelSize;
					UINT32 *pKernelPixel = pKernel + k * (2 * nKernelSize + 1);
					for (int l = 0; l <= 2 * nKernelSize; l++)
					{
						if (*pPixel < *pKernelPixel)
							*pPixel = *pKernelPixel;

						pPixel++;
						pKernelPixel++;
					}
				}
			}   // for() end of line

		}
	}   // for() Generate blurred border
		
		// Erase unwanted parts and complement missing
	UINT32 clCenter = m_nDarkness << 24 | PreMultiply(m_Color, m_nDarkness);
	for (int i = min(nKernelSize, max(m_nSize - m_nyOffset, 0));i < max(szShadow.cy - nKernelSize, min(szParent.cy + m_nSize - m_nyOffset, szParent.cy + 2 * m_nSize));i++)
	{
		UINT32 *pLine = pShadBits + (szShadow.cy - i - 1) * szShadow.cx;
		if (i - m_nSize + m_nyOffset < 0 || i - m_nSize + m_nyOffset >= szParent.cy)   // Line is not covered by parent window
		{
			for (int j = ptAnchors[i][0]; j < ptAnchors[i][1]; j++)
			{
				*(pLine + j) = clCenter;
			}
		}
		else
		{
			for (int j = ptAnchors[i][0];j < min(ptAnchorsOri[i - m_nSize + m_nyOffset][0] + m_nSize - m_nxOffset, ptAnchors[i][1]);j++)
				*(pLine + j) = clCenter;
			for (int j = max(ptAnchorsOri[i - m_nSize + m_nyOffset][0] + m_nSize - m_nxOffset, 0);j < min(ptAnchorsOri[i - m_nSize + m_nyOffset][1] + m_nSize - m_nxOffset, szShadow.cx);j++)
				*(pLine + j) = 0;
			for (int j = max(ptAnchorsOri[i - m_nSize + m_nyOffset][1] + m_nSize - m_nxOffset, ptAnchors[i][0]);j < ptAnchors[i][1];j++)
				*(pLine + j) = clCenter;
		}
	}
	
	// Delete used resources
	delete[](ptAnchors - (m_nSize < 0 ? -m_nSize : 0) - 1);
	delete[] ptAnchorsTmp;
	delete[] ptAnchorsOri;
	delete[] pKernel;
	DeleteObject(hParentRgn);
}