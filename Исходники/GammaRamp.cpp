BOOL CGammaRamp::SetBrightness(WORD wBrightness, HDC hDC)
{
	BOOL bReturn = FALSE;
	HDC hGammaDC = hDC;

	if (hDC == NULL)
		hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL)
	{
		WORD GammaArray[3][256];

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iArrayValue = iIndex * (wBrightness + 128);

			if (iArrayValue > 65535)
				iArrayValue = 65535;

			GammaArray[0][iIndex] = 
			GammaArray[1][iIndex] = 
			GammaArray[2][iIndex] = (WORD)iArrayValue;
			
		}

		bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
	}

	if (hDC == NULL)
		ReleaseDC(NULL, hGammaDC);

	return bReturn;
}