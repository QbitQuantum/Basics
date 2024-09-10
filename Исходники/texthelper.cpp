HSURFACE CTextHelper::CreateWrappedSurface (ILTClient* pClientDE, int nWidth, HLTFONT hFont, char* pString, HLTCOLOR foreColor, HLTCOLOR backColor, int nAlignment, LTBOOL bCropped, int nExtraX, int nExtraY)
{
	if (!pString || !pClientDE) return LTNULL;

	// check if we are supposed to do hard wrapping
	bool bHardTextWrap = false;
	{
		HSTRING hStr = pClientDE->FormatString(IDS_ENABLETEXTHARDWRAP);
		if (hStr)
		{
			const char* pComp = pClientDE->GetStringData(hStr);
			if (pComp != NULL)
			{
				if (stricmp(pComp,"TRUE") == 0) bHardTextWrap = true;
			}
			pClientDE->FreeString (hStr);
		}
	}

	// get period or other characters that are not supposed to be at start of a line
	char sPeriodChars[256] = ".";
	{
		HSTRING hStr = pClientDE->FormatString(IDS_EXCLULTLineSTARTCHARS);
		if (hStr)
		{
			const char* pComp = pClientDE->GetStringData(hStr);
			if (pComp != NULL)
			{
				_mbsncpy((unsigned char*)sPeriodChars, (const unsigned char*)pComp, 255);
				sPeriodChars[255] = '\0';
			}
			pClientDE->FreeString (hStr);
		}
	}

	char* pWorkingString = new char [strlen (pString) + 1];
	if (!pWorkingString) return LTNULL;

	CDynArray<uint32> surfaces (1, 2);		// cannot create a dynarray of HSURFACES - compiler error C2926
	uint32 nSurfaces = 0;

	char* ptr = (char*) pString;
	while (*ptr != '\0')
	{
		// copy what's left into the working string

		strcpy (pWorkingString, ptr);

		// create a string that will fit into the desired width

		LTBOOL bDone = LTFALSE;
		HSURFACE hSurface = LTNULL;
		while (!bDone)
		{
			// create a string surface from the working string to test

			HSTRING hString = pClientDE->CreateString (pWorkingString);
			if (!hString) break;

			hSurface = pClientDE->CreateSurfaceFromString (hFont, hString, foreColor, backColor, nExtraX, nExtraY);
			if (!hSurface)
			{
				pClientDE->FreeString (hString);
				break;
			}

			pClientDE->FreeString (hString);
			
			// get the dimensions of the surface

			uint32 nTestWidth = 0;
			uint32 nTestHeight = 0;
			pClientDE->GetSurfaceDims (hSurface, &nTestWidth, &nTestHeight);

			if (nTestWidth > (uint32)nWidth)
			{
				// string too long, remove some and try again

				char* pSpace;

				// remove by character if we are hard wrapping
				if (bHardTextWrap)
				{
					pSpace = pWorkingString;

					// find last hard in string pPrev
					char* pPrev = NULL;
					while (pSpace != NULL)
					{
						pPrev = pSpace;
						pSpace = (char*)_mbsinc ((const unsigned char*)pSpace);
						if (*pSpace == '\0') pSpace = NULL;
					}
					if (pPrev == NULL) pSpace = pWorkingString;
					else 
					{
						//decrement 1 character
						pSpace = (char*)_mbsdec ((const unsigned char*)pWorkingString, (const unsigned char*)pPrev);

						// check if we are on a period then we need to decrement 3 more
						if ((char*)_mbsspnp((const unsigned char*)pPrev, (const unsigned char*)sPeriodChars) != pPrev)
						{
							if (pSpace != NULL)	pSpace = (char*)_mbsdec ((const unsigned char*)pWorkingString, (const unsigned char*)pSpace);
							if (pSpace != NULL)	pSpace = (char*)_mbsdec ((const unsigned char*)pWorkingString, (const unsigned char*)pSpace);
						}
					}

				}

				// remove by word if hard wrap is not on
				else 
				{
					pSpace = (char*)_mbsrchr ((const unsigned char*)pWorkingString, ' ');
					if (!pSpace) pSpace = pWorkingString;

					while (_mbsnbcmp ((const unsigned char*)pSpace, (const unsigned char*)" ", 1) == 0 && pSpace != pWorkingString)
					{
						pSpace = (char*)_mbsdec ((const unsigned char*)pWorkingString, (const unsigned char*)pSpace);
						if (!pSpace) pSpace = pWorkingString;
					}
				}


				if (pSpace == pWorkingString)
				{
					bDone = LTTRUE;
				}
				else
				{
					pSpace = (char*)_mbsinc ((const unsigned char*)pSpace);
					*pSpace = '\0';
				}

				pClientDE->DeleteSurface (hSurface);
				hSurface = LTNULL;
			}
			else
			{
				// it fits!

				bDone = LTTRUE;
			}
		}
		
		// if we got here without bDone being TRUE, there was an error
		if (!bDone)
		{
			delete [] pWorkingString;
			for (uint32 i = 0; i < nSurfaces; i++)
			{
				pClientDE->DeleteSurface ((HSURFACE)surfaces[i]);
			}
			return LTNULL;
		}

		// if bDone is true but there's no surface, we couldn't make it fit
		// just create a surface from the string and it will get clipped later
		if (bDone && !hSurface)
		{
			HSTRING hString = pClientDE->CreateString (pWorkingString);
			hSurface = pClientDE->CreateSurfaceFromString (hFont, hString, foreColor, backColor, nExtraX, nExtraY);
			if (!hString || !hSurface)
			{
				if (hString) pClientDE->FreeString (hString);
				if (hSurface) pClientDE->DeleteSurface (hSurface);

				delete [] pWorkingString;
				for (uint32 i = 0; i < nSurfaces; i++)
				{
					pClientDE->DeleteSurface ((HSURFACE)surfaces[i]);
				}
				return LTNULL;
			}
			pClientDE->FreeString (hString);
		}

		// add this surface to the array

		surfaces[nSurfaces] = (uint32) hSurface;
		nSurfaces++;

		// increment ptr to next character in the string

		ptr += strlen (pWorkingString);
		
		char* pPrev = NULL;
		while (_mbsnbcmp ((const unsigned char*)ptr, (const unsigned char*)" ", 1) == 0 && *ptr)
		{
			pPrev = ptr;
			ptr = (char*)_mbsinc ((const unsigned char*)ptr);
			if (!ptr) 
			{
				ptr = pPrev;
				break;
			}
		}
	}

	delete [] pWorkingString;

	// ok, now we should have an array of surfaces that we can combine into one large one...

	if (!nSurfaces) return LTNULL;

	// crop the surfaces if they need to be cropped (leave a one-pixel border)

	if (bCropped)
	{
		for (uint32 i = 0; i < nSurfaces; i++)
		{
			HSURFACE hCropped = CropSurface (pClientDE, (HSURFACE)surfaces[i], LTNULL);
			if (hCropped)
			{
				pClientDE->DeleteSurface ((HSURFACE)surfaces[i]);
				surfaces[i] = (uint32) hCropped;
			}
		}
	}

	// get the final surface height

	uint32 nTotalHeight = 0;
	for (uint32 i = 0; i < nSurfaces; i++)
	{
		uint32 nSurfWidth = 0;
		uint32 nSurfHeight = 0;
		pClientDE->GetSurfaceDims ((HSURFACE)surfaces[i], &nSurfWidth, &nSurfHeight);

		nTotalHeight += nSurfHeight;
	}

	// create the final surface

	HSURFACE hFinalSurface = pClientDE->CreateSurface (nWidth, nTotalHeight);
	if (!hFinalSurface)
	{
		for (uint32 i = 0; i < nSurfaces; i++)
		{
			pClientDE->DeleteSurface ((HSURFACE)surfaces[i]);
		}
		return LTNULL;
	}
	pClientDE->FillRect ((HSURFACE)hFinalSurface, LTNULL, LTNULL);

	// draw the string surfaces onto final one

	int y = 0;
	for (int i = 0; i < nSurfaces; i++)
	{
		uint32 nSurfWidth = 0;
		uint32 nSurfHeight = 0;
		pClientDE->GetSurfaceDims ((HSURFACE)surfaces[i], &nSurfWidth, &nSurfHeight);

		int x = 0;
		switch (nAlignment)
		{
			case TH_ALIGN_CENTER:	x = ((int)nWidth - (int)nSurfWidth) / 2;	break;
			case TH_ALIGN_RIGHT:	x = (int)nWidth - (int)nSurfWidth;			break;
		}
		pClientDE->DrawSurfaceToSurface (hFinalSurface, (HSURFACE)surfaces[i], LTNULL, x, y);
		y += nSurfHeight;

		// delete this surface since we don't need it anymore

		pClientDE->DeleteSurface ((HSURFACE)surfaces[i]);
	}
	
	if (bCropped)
	{
		HSURFACE hCropped = CropSurface (pClientDE, hFinalSurface, backColor);
		if (hCropped)
		{
			pClientDE->DeleteSurface (hFinalSurface);
			return hCropped;
		}
	}

	return hFinalSurface;
}