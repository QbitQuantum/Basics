//--------------------------------------------------------------------------//
// Print single-fold card.													//
//--------------------------------------------------------------------------//
bool CAGDoc::PrintCardSingle(PRINTSIDE PrintSide, char *pszDriver,
								char *pszDevice, char *pszOutput,
								DEVMODE *pDevMode, bool &bRotated,
								const char *pszFileName)
{
	if (m_nPages != 4)
		return (false);

	bool bPortrait = (m_AGDocType == DOC_CARDHH || m_AGDocType == DOC_CARDFH);

	if (pDevMode)
	{
		if (bPortrait)
			pDevMode->dmOrientation = DMORIENT_PORTRAIT;
		else
			pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
		pDevMode->dmFields |= DM_ORIENTATION;
	}

	CAGDC *pDC = new CAGDC(pszDriver, pszDevice, pszOutput, pDevMode);
	CAGDCInfo di = pDC->GetDeviceInfo();

	if (pDevMode && pDevMode->dmOrientation == DMORIENT_PORTRAIT &&
		di.m_nHorzSize > di.m_nVertSize)
	{
		delete pDC;
		pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
		pDC = new CAGDC(pszDriver, pszDevice, pszOutput, pDevMode);
		di = pDC->GetDeviceInfo();
	}
	else if (pDevMode && pDevMode->dmOrientation == DMORIENT_LANDSCAPE &&
		di.m_nVertSize > di.m_nHorzSize)
	{
		delete pDC;
		pDevMode->dmOrientation = DMORIENT_PORTRAIT;
		pDC = new CAGDC(pszDriver, pszDevice, pszOutput, pDevMode);
		di = pDC->GetDeviceInfo();
	}

	RECT		DestRect;
	RECT		SrcRect;
	SIZE		sizePage;
	CAGMatrix	ViewMatrix;
	bool		bFlip;

	if (! pDC->StartDoc("Create and Print"))
	{
		delete pDC;
		return (false);
	}

	if (PrintSide == PRINT_OUTSIDE || PrintSide == PRINT_BOTH)
	{
		if (! pDC->StartPage())
		{
			pDC->AbortDoc();
			delete pDC;
			return (false);
		}

		//------------------------------------------------------------------//
		// Front															//
		//------------------------------------------------------------------//
		CAGPage *pPage = GetPage(1);
		pPage->GetPageSize(&sizePage);
		::SetRect(&SrcRect, 0, 0, sizePage.cx, sizePage.cy);
		GetSFPageRect(1, bPortrait, false, pDC, di, DestRect, bFlip, bRotated);
		ViewMatrix.ScaleAndCenter(DestRect, SrcRect, bFlip);
		pDC->SetViewingMatrix(ViewMatrix);
		pPage->Draw(*pDC);

		//------------------------------------------------------------------//
		// Back																//
		//------------------------------------------------------------------//
		pPage = GetPage(4);
		pPage->GetPageSize(&sizePage);
		::SetRect(&SrcRect, 0, 0, sizePage.cx, sizePage.cy);
		GetSFPageRect(4, bPortrait, false, pDC, di, DestRect, bFlip, bRotated);
		ViewMatrix.ScaleAndCenter(DestRect, SrcRect, bFlip);
		pDC->SetViewingMatrix(ViewMatrix);
		pPage->Draw(*pDC);

		//------------------------------------------------------------------//
		// BatchPrint filename.												//
		//------------------------------------------------------------------//
		if (pszFileName)
		{
			LOGFONT Font;
			memset(&Font, 0, sizeof(Font));
			Font.lfHeight = -(12 * APP_RESOLUTION / 72);
			lstrcpy(Font.lfFaceName, "Times New Roman");
			pDC->SetFont(&Font);
			pDC->SetTextColor(RGB (0, 0, 0));
			pDC->ExtTextOut(APP_RESOLUTION / 8,
							SrcRect.bottom - (APP_RESOLUTION / 8), 0, NULL, pszFileName,
							lstrlen(pszFileName), NULL);
		}

		if (! pDC->EndPage())
		{
			pDC->AbortDoc();
			delete pDC;
			return (false);
		}
	}

	if (PrintSide == PRINT_INSIDE || PrintSide == PRINT_BOTH)
	{
		if (! pDC->StartPage())
		{
			pDC->AbortDoc();
			delete pDC;
			return (false);
		}

		bool bPage2Empty = GetPage(2)->IsEmpty();
		bool bPage3Empty = GetPage(3)->IsEmpty();

		//------------------------------------------------------------------//
		// Inside Left / Top												//
		//------------------------------------------------------------------//
		CAGPage *pPage = GetPage(2);
		pPage->GetPageSize(&sizePage);
		::SetRect(&SrcRect, 0, 0, sizePage.cx, sizePage.cy);
		GetSFPageRect(2, bPortrait, ! bPage3Empty, pDC, di, DestRect, bFlip,
						bRotated);
		ViewMatrix.ScaleAndCenter(DestRect, SrcRect, bFlip);
		pDC->SetViewingMatrix(ViewMatrix);
		pPage->Draw(*pDC);

		//------------------------------------------------------------------//
		// BatchPrint filename.												//
		//------------------------------------------------------------------//
		if (pszFileName)
		{
			LOGFONT Font;
			memset(&Font, 0, sizeof(Font));
			Font.lfHeight = -(12 * APP_RESOLUTION / 72);
			lstrcpy(Font.lfFaceName, "Times New Roman");
			pDC->SetFont(&Font);
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->ExtTextOut(APP_RESOLUTION / 8,
							SrcRect.bottom - (APP_RESOLUTION / 8), 0, NULL, pszFileName,
							lstrlen(pszFileName), NULL);
		}

		//------------------------------------------------------------------//
		// Inside Right / Bottom											//
		//------------------------------------------------------------------//
		pPage = GetPage(3);
		pPage->GetPageSize(&sizePage);
		::SetRect(&SrcRect, 0, 0, sizePage.cx, sizePage.cy);
		GetSFPageRect(3, bPortrait, ! bPage2Empty, pDC, di, DestRect, bFlip,
						bRotated);
		ViewMatrix.ScaleAndCenter(DestRect, SrcRect, bFlip);
		pDC->SetViewingMatrix(ViewMatrix);
		pPage->Draw(*pDC);

		if (! pDC->EndPage())
		{
			pDC->AbortDoc();
			delete pDC;
			return (false);
		}
	}

	if (! pDC->EndDoc())
	{
		pDC->AbortDoc();
		delete pDC;
		return (false);
	}
	delete pDC;

	return (true);
}