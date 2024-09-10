//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
static void PrintTest(bool bFirstTest, char *pszDriver, char *pszDevice,
						char *pszOutput, DEVMODE *pDevMode)
{
	short nSaveCopies = -1;

	if (pDevMode)
	{
		pDevMode->dmOrientation = DMORIENT_PORTRAIT;
		pDevMode->dmFields |= DM_ORIENTATION;

		if (pDevMode->dmCopies > 1)
		{
			nSaveCopies = pDevMode->dmCopies;
			pDevMode->dmCopies = 1;
		}
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

	if (! pDC->StartDoc("Create and Print"))
	{
		delete pDC;
		if (pDevMode && nSaveCopies != -1)
			pDevMode->dmCopies = nSaveCopies;
		return;
	}

	if (! pDC->StartPage())
	{
		pDC->AbortDoc();
		delete pDC;
		if (pDevMode && nSaveCopies != -1)
			pDevMode->dmCopies = nSaveCopies;
		return;
	}

	if (bFirstTest)
	{
		POINT Pt = { di.m_PhysPageSize.cx / 2, di.m_nLogPixelsY };
		pDC->DPAtoVPA(&Pt, 1);
		DrawArrow(pDC, Pt);

		char szMsg[] = "Please put this page back into the printer\n\n"
			"with the printed side UP\n\n"
			"and the arrow pointing TOWARD the printer.";

		int nSpecOffset = 0;
		RECT MsgRect = { 0, di.m_nLogPixelsY * 3, di.m_PhysPageSize.cx,
		  di.m_nLogPixelsY * 6 };
		pDC->DPAtoVPA(&MsgRect);

		LOGFONT MsgFont;
		memset(&MsgFont, 0, sizeof(MsgFont));
		lstrcpy(MsgFont.lfFaceName, "Arial");
		MsgFont.lfHeight = -(14 * APP_RESOLUTION / 72);
		CAGSpec MsgSpec(MsgFont, RGB(0, 0, 0), eRagCentered);

		CAGSymText *pAGSymText = new CAGSymText();
		pAGSymText->Create(MsgRect);
		pAGSymText->SetVertJust(eVertTop);
		pAGSymText->SetText(szMsg, lstrlen(szMsg), 1, &MsgSpec, &nSpecOffset);
		pAGSymText->Draw(*pDC);
		delete pAGSymText;
	}
	else
	{
		POINT Pt = { di.m_PhysPageSize.cx / 4, di.m_nLogPixelsY };
		pDC->DPAtoVPA(&Pt, 1);
		DrawArrow(pDC, Pt);

		Pt.x = (di.m_PhysPageSize.cx / 4) * 3;
		Pt.y = di.m_nLogPixelsY;
		pDC->DPAtoVPA(&Pt, 1);
		DrawArrow(pDC, Pt);
	}

	if (! pDC->EndPage())
	{
		pDC->AbortDoc();
		delete pDC;
		if (pDevMode && nSaveCopies != -1)
			pDevMode->dmCopies = nSaveCopies;
		return;
	}

	if (! pDC->EndDoc())
	{
		pDC->AbortDoc();
		delete pDC;
		if (pDevMode && nSaveCopies != -1)
			pDevMode->dmCopies = nSaveCopies;
		return;
	}

	delete pDC;

	if (pDevMode && nSaveCopies != -1)
		pDevMode->dmCopies = nSaveCopies;
}