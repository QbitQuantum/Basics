/***********************************************************************
 * SYSLINK_Render
 * Renders the document in memory
 */
static VOID SYSLINK_Render (const SYSLINK_INFO *infoPtr, HDC hdc, PRECT pRect)
{
    RECT rc;
    PDOC_ITEM Current;
    HGDIOBJ hOldFont;
    int x, y, LineHeight;
    SIZE szDoc;
    TEXTMETRICW tm;

    szDoc.cx = szDoc.cy = 0;

    rc = *pRect;
    rc.right -= SL_RIGHTMARGIN;
    rc.bottom -= SL_BOTTOMMARGIN;

    if(rc.right - SL_LEFTMARGIN < 0)
        rc.right = MAXLONG;
    if (rc.bottom - SL_TOPMARGIN < 0)
        rc.bottom = MAXLONG;
    
    hOldFont = SelectObject(hdc, infoPtr->Font);
    
    x = SL_LEFTMARGIN;
    y = SL_TOPMARGIN;
    GetTextMetricsW( hdc, &tm );
    LineHeight = tm.tmHeight + tm.tmExternalLeading;

    for(Current = infoPtr->Items; Current != NULL; Current = Current->Next)
    {
        int n, nBlocks;
        LPWSTR tx;
        PDOC_TEXTBLOCK bl, cbl;
        INT nFit;
        SIZE szDim;
        int SkipChars = 0;

        if(Current->nText == 0)
        {
            continue;
        }

        tx = Current->Text;
        n = Current->nText;

        Free(Current->Blocks);
        Current->Blocks = NULL;
        bl = NULL;
        nBlocks = 0;

        if(Current->Type == slText)
        {
            SelectObject(hdc, infoPtr->Font);
        }
        else if(Current->Type == slLink)
        {
            SelectObject(hdc, infoPtr->LinkFont);
        }
        
        while(n > 0)
        {
            /* skip break characters unless they're the first of the doc item */
            if(tx != Current->Text || x == SL_LEFTMARGIN)
            {
                if (n && *tx == '\n')
                {
                    tx++;
                    SkipChars++;
                    n--;
                }
                while(n > 0 && (*tx) == infoPtr->BreakChar)
                {
                    tx++;
                    SkipChars++;
                    n--;
                }
            }

            if((n == 0 && SkipChars != 0) ||
               GetTextExtentExPointW(hdc, tx, n, rc.right - x, &nFit, NULL, &szDim))
            {
                int LineLen = n;
                BOOL Wrap = FALSE;
                PDOC_TEXTBLOCK nbl;
                
                if(n != 0)
                {
                    Wrap = SYSLINK_WrapLine(tx, infoPtr->BreakChar, x, &LineLen, nFit, &szDim);

                    if(LineLen == 0)
                    {
                        /* move one line down, the word didn't fit into the line */
                        x = SL_LEFTMARGIN;
                        y += LineHeight;
                        continue;
                    }

                    if(LineLen != n)
                    {
                        if(!GetTextExtentExPointW(hdc, tx, LineLen, rc.right - x, NULL, NULL, &szDim))
                        {
                            if(bl != NULL)
                            {
                                Free(bl);
                                bl = NULL;
                                nBlocks = 0;
                            }
                            break;
                        }
                    }
                }
                
                nbl = ReAlloc(bl, (nBlocks + 1) * sizeof(DOC_TEXTBLOCK));
                if (nbl != NULL)
                {
                    bl = nbl;
                    nBlocks++;

                    cbl = bl + nBlocks - 1;
                    
                    cbl->nChars = LineLen;
                    cbl->nSkip = SkipChars;
                    cbl->rc.left = x;
                    cbl->rc.top = y;
                    cbl->rc.right = x + szDim.cx;
                    cbl->rc.bottom = y + szDim.cy;

                    if (cbl->rc.right > szDoc.cx)
                        szDoc.cx = cbl->rc.right;
                    if (cbl->rc.bottom > szDoc.cy)
                        szDoc.cy = cbl->rc.bottom;

                    if(LineLen != 0)
                    {
                        x += szDim.cx;
                        if(Wrap)
                        {
                            x = SL_LEFTMARGIN;
                            y += LineHeight;
                        }
                    }
                }
                else
                {
                    Free(bl);
                    bl = NULL;
                    nBlocks = 0;

                    ERR("Failed to alloc DOC_TEXTBLOCK structure!\n");
                    break;
                }
                n -= LineLen;
                tx += LineLen;
                SkipChars = 0;
            }
            else
            {
                n--;
            }
        }

        if(nBlocks != 0)
        {
            Current->Blocks = bl;
        }
    }
    
    SelectObject(hdc, hOldFont);

    pRect->right = pRect->left + szDoc.cx;
    pRect->bottom = pRect->top + szDoc.cy;
}