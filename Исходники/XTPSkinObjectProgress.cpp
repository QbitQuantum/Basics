void CXTPSkinObjectProgress::OnDraw(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CXTPBufferDC dcMem(*pDC, rcClient);

	dcMem.FillSolidRect(rcClient, GetColor(COLOR_3DFACE));

	DWORD dwStyle = GetStyle();
	BOOL bVert = dwStyle & PBS_VERTICAL;
	int nBarPart = bVert ? PP_BARVERT : PP_BAR;
	int nChunkPart = bVert ? PP_CHUNKVERT : PP_CHUNK;

	CXTPSkinManagerClass* pClassProgress = GetSkinClass();
	pClassProgress->DrawThemeBackground(&dcMem, nBarPart, 0,  rcClient);

	CRect rc = rcClient;

	CRect rcMargins = pClassProgress->GetThemeRect(nBarPart, 0,  TMT_SIZINGMARGINS);

	rc.DeflateRect(rcMargins);

	int iWidth, dxBlock;

	if (GetStyle() & PBS_MARQUEE)
	{
		rcClient = rc;

		dxBlock = pClassProgress->GetThemeInt(0, 0, TMT_PROGRESSCHUNKSIZE, rc.Height() * 2 / 3);
		int dxSpace = pClassProgress->GetThemeInt(0, 0, TMT_PROGRESSSPACESIZE, 2);

		rc.left = m_nMarqueePos + rcClient.left;

		if (dxBlock == 1 && dxSpace == 0)
		{
			dxBlock = 8;

			rc.right = rc.left + 5 * dxBlock;

			if (rc.right > rcClient.right)
			{
				CRect rcPart(rcClient.left, rc.top, rcClient.left + rc.right - rcClient.right, rc.bottom);
				pClassProgress->DrawThemeBackground(&dcMem, nChunkPart, 0,  rcPart);

				rc.right = rcClient.right;
			}

			pClassProgress->DrawThemeBackground(&dcMem, nChunkPart, 0,  rc);
			return;
		}

		for (int i = 0; i < 5; i++)
		{
			if (rc.left >= rcClient.right)
				rc.left = rcClient.left;

			rc.right = rc.left + dxBlock;

			if (rc.right > rcClient.right)
				rc.right = rcClient.right;

			pClassProgress->DrawThemeBackground(&dcMem, nChunkPart, 0,  rc);
			rc.left = rc.right + dxSpace;
		}
		return;
	}

	PBRANGE range;
	SendMessage(PBM_GETRANGE, (WPARAM) FALSE, (LPARAM) &range);

	int iLow = range.iLow;
	int iHigh = range.iHigh;
	int iPos =  (int)SendMessage(PBM_GETPOS);


	if (bVert)
	{
		iWidth = rc.Height();
		dxBlock = (rcClient.right - rcClient.left) * 2 / 3;
	}
	else
	{
		iWidth = rc.Width();
		dxBlock = (rcClient.bottom - rcClient.top) * 2 / 3;
	}

	int x = MulDiv(iWidth, iPos - iLow, iHigh - iLow);

	dxBlock = pClassProgress->GetThemeInt(0, 0, TMT_PROGRESSCHUNKSIZE, dxBlock);
	int dxSpace = pClassProgress->GetThemeInt(0, 0, TMT_PROGRESSSPACESIZE, 2);


	if (dxBlock == 0)
		dxBlock = 1;

	if (dxBlock == 1 && dxSpace == 0)
	{
		if (bVert)
		{
			rc.top = rc.bottom - x;
		}
		else
		{
			rc.right = rc.left + x;
		}
		pClassProgress->DrawThemeBackground(&dcMem, nChunkPart, 0,  rc);
		return;
	}

	int nBlocks = (x + (dxBlock + dxSpace) - 1) / (dxBlock + dxSpace);

	for (int i = 0; i < nBlocks; i++)
	{
		if (bVert)
		{
			rc.top = rc.bottom - dxBlock;

			if (rc.bottom <= rcClient.top)
				break;

			if (rc.top <= rcClient.top)
				rc.top = rcClient.top + 1;

		}
		else
		{
			rc.right = rc.left + dxBlock;

			if (rc.left >= rcClient.right)
				break;

			if (rc.right >= rcClient.right)
				rc.right = rcClient.right - 1;
		}

		pClassProgress->DrawThemeBackground(&dcMem, nChunkPart, 0,  rc);


		if (bVert)
			rc.bottom = rc.top - dxSpace;
		else
			rc.left = rc.right + dxSpace;
	}
}