BOOL StringToBitmap::TTFAddString(String_256 *text, UINT32 Xsize, UINT32 Ysize, UINT32 DPI, PLOGFONT pLogFont,
                                  INT32 IntLeading, KernelBitmap **BM, UINT32 ForeColour)
{
    KernelBitmap *Bitmap = *BM;

    /*	HDC ScreenDC = CreateCompatibleDC(NULL);
    	if (ScreenDC == NULL)
    	{
    		ERROR3("StringToBitmap::AddString: Unable to create screen DC");
    		return FALSE;
    	}*/

    CDC SysDisplay;
    BOOL ok=SysDisplay.CreateCompatibleDC(NULL);
    if(!ok)
    {
        //DeleteDC(ScreenDC);
        ERROR3("StringToBitmap::TTF AddString: Unable to create CDC");
        return FALSE;
    }

    HDC ScreenDC = SysDisplay.m_hDC;

    // bodge to get things working with GetBezierFromChar
    INT32 OldlfHeight = pLogFont->lfHeight;
    pLogFont->lfHeight = -(pLogFont->lfHeight - IntLeading);

    UINT32 CurrentPathSizeAlloc = 0;
    Trans2DMatrix *pTransform = NULL;
    DocCoord *pPathCoords = NULL;

    Path *pPath = NULL;
    //pPath = new Path();

    DocCoord *pPolyCordBuffer = NULL;
    PathVerb *pPolyVerbBuffer = NULL;
    UINT32 TextLength = (UINT32)text->Length();
    SIZE StringSize= {0,0};

    // Get handle of font

//	HFONT hNewFont = CreateFontIndirect(pLogFont);
//	HGDIOBJ hOldFont = SelectObject(ScreenDC, hNewFont);

    CFont UnHintedCFont;
    if(!UnHintedCFont.CreateFontIndirect(pLogFont))
    {
        SysDisplay.DeleteDC();
        pLogFont->lfHeight = OldlfHeight;
        return FALSE;
    }

    CFont* pOldCFont=SysDisplay.SelectObject(&UnHintedCFont);

    // Get the default character to use if a charater is not present in the font.
    WCHAR FontDefaultCharacter = (unsigned char)'?';
    TEXTMETRIC FontTextData;
#ifdef _UNCCODE
    if (SysDisplay.GetTextMetrics(&FontTextData))
        FontDefaultCharacter = FontTextData.tmDefaultChar;
#else
    if (SysDisplay.GetTextMetrics(&FontTextData))
        FontDefaultCharacter = (unsigned char)FontTextData.tmDefaultChar;
#endif

    // Work out a nice scaling factor so the font fits in the bitmap ok...

    // Not 32 ?
    GetTextExtentPoint(ScreenDC, *text, TextLength, &StringSize);

    if(StringSize.cy == 0)
    {
        SysDisplay.SelectObject(pOldCFont);
        SysDisplay.DeleteDC();
        pLogFont->lfHeight = OldlfHeight;
        return FALSE;
    }

    //ERROR3IF(!ok, "Initial GetTextExtentPoint32() failed");
    double YScale = ((double)Ysize / (double)StringSize.cy) / (double)2;
    double XScale = YScale;

    // Shift thumbnail upwards, and scale down a bit - to get the g's looking right
    // One or two fonts require this reducing (their tops are clipped), 72000/100 is
    // about right for most of them though...
    // Note the external previews were done with 72000/220 for Matrix and 72000/140 for
    // the capital only fonts.
    double YShift = 72000/100;//72000/80;

    YScale = (YScale * 78) / 100;
    XScale = (XScale * 78) / 100;

    if(!text->IsEmpty())
    {
        const TCHAR* pCurrentChar = (const TCHAR*)(*text);

        while (ok && *pCurrentChar!=0)
        {
            // Get the current character as Unicode.
#ifdef _UNICODE
            WCHAR wchr = *pCurrentChar;		// pCurrentChar is a pointer to WCHAR in _UNICODE builds
#else
            UINT32 CharToConvert = 0;
            if (UnicodeManager::IsDBCSLeadByte(*pCurrentChar))
                CharToConvert = UnicodeManager::ComposeMultiBytes(*pCurrentChar, *(pCurrentChar+1));
            else
                CharToConvert = (unsigned char)(*pCurrentChar);
            WCHAR wchr = UnicodeManager::MultiByteToUnicode(CharToConvert);
#endif

            // Get positioning information for this character
            ok = GetTextExtentPoint(ScreenDC, *text, (pCurrentChar-(TCHAR*)(*text)), &StringSize);
            ERROR3IF(!ok, "GetTextExtentPoint32() failed");
            if (!ok) break;

            // Get the characters path
            DWORD PathSize = 0;
            ok = TextManager::GetBezierFromChar(&SysDisplay, wchr, pLogFont, &PathSize, (POINT *)NULL, (BYTE *)NULL);
            if (!ok)
            {
                wchr = FontDefaultCharacter;
                ok = TextManager::GetBezierFromChar(&SysDisplay, wchr, pLogFont, &PathSize, (POINT *)NULL, (BYTE *)NULL);
            }
            ERROR3IF(!ok, "GetBezierFromChar returned false");
            if (!ok) break;

            // Pointer to an array of path coordinates
            if(pPolyCordBuffer == NULL)
            {
                TRY
                {
                    pPolyCordBuffer = new DocCoord[PathSize];
                }
                CATCH (CMemoryException, e)
                {
                    pPolyCordBuffer = NULL;
                    /*ERROR(_R(IDS_OUT_OF_MEMORY), FALSE);*/
                }
                END_CATCH
            }

            // Pointer to an array of path verbs
            if(pPolyVerbBuffer == NULL)
            {
                TRY
                {
                    pPolyVerbBuffer = new PathVerb[PathSize];
                }
                CATCH (CMemoryException, e)
                {
                    pPolyVerbBuffer = NULL;
                    /*ERROR(_R(IDS_OUT_OF_MEMORY), FALSE);*/
                }
                END_CATCH
            }

            if (pPolyCordBuffer == NULL || pPolyVerbBuffer == NULL)
            {
                ok = FALSE;
                break;
            }

            CurrentPathSizeAlloc = PathSize;

            // Fill up the buffers until they're bursting with fontyness
            ok = TextManager::GetBezierFromChar(&SysDisplay, wchr, pLogFont, &PathSize, (POINT *)pPolyCordBuffer,
                                                (BYTE *)pPolyVerbBuffer);
            if(!ok) TRACEUSER( "Richard", _T("GetBezierFromChar returned false in second phase...\n"));
            if(!ok)	break;

            // Spaces set PathSize to zero
            if((PathSize > 0)/* && (pPath != NULL)*/)
            {
                pPath = new Path();
                pPath->Initialise(PathSize, 12);
                pPath->CopyPathDataFrom(pPolyCordBuffer, pPolyVerbBuffer, PathSize, TRUE);

                // Major bodge at present with the x spacing...
                Matrix scale(XScale, 0, 0, YScale, (INT32)((XScale*StringSize.cx*72000)/(double)DPI), (INT32)YShift);

                pTransform = new Trans2DMatrix(scale);
                pPathCoords = pPath->GetCoordArray();
                pTransform->Transform( pPathCoords, pPath->GetNumCoords() );
                delete pTransform;

                pPath->InitialiseFlags();

                ok = ALU->GradFillPath(pPath, ForeColour, ForeColour, 0, 0, 0,/*Xsize/2,*/ Ysize, S2BMP_ANTIALIAS);
                ERROR3IF(!ok, "Gradfillpath returned false");
                if(!ok)	break;

                delete pPath;
            }

            // S2BMP_MAGIC is the worderfully fabby constant that mark's getbezierfromchar returns
            // Theory goes that he's going to sort this out sometime...
            if(CurrentPathSizeAlloc != S2BMP_MAGIC)
            {
                delete []pPolyCordBuffer;
                delete []pPolyVerbBuffer;

                pPolyCordBuffer = NULL;
                pPolyVerbBuffer = NULL;
                CurrentPathSizeAlloc = 0;
            }

            pPath = NULL;
            pTransform = NULL;

            pCurrentChar = camStrinc(pCurrentChar);
        }