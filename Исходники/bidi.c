/*************************************************************
 *    BIDI_Reorder
 *
 *     Returns TRUE if reordering was required and done.
 */
BOOL BIDI_Reorder(
    HDC hDC,        /*[in] Display DC */
    LPCWSTR lpString,       /* [in] The string for which information is to be returned */
    INT uCount,     /* [in] Number of WCHARs in string. */
    DWORD dwFlags,  /* [in] GetCharacterPlacement compatible flags specifying how to process the string */
    DWORD dwWineGCP_Flags,       /* [in] Wine internal flags - Force paragraph direction */
    LPWSTR lpOutString, /* [out] Reordered string */
    INT uCountOut,  /* [in] Size of output buffer */
    UINT *lpOrder, /* [out] Logical -> Visual order map */
    WORD **lpGlyphs, /* [out] reordered, mirrored, shaped glyphs to display */
    INT *cGlyphs /* [out] number of glyphs generated */
)
{
    WORD *chartype;
    BYTE *levels;
    unsigned i, done, glyph_i;
    BOOL is_complex;

    int maxItems;
    int nItems;
    SCRIPT_CONTROL Control;
    SCRIPT_STATE State;
    SCRIPT_ITEM *pItems;
    HRESULT res;
    SCRIPT_CACHE psc = NULL;
    WORD *run_glyphs = NULL;
    WORD *pwLogClust = NULL;
    SCRIPT_VISATTR *psva = NULL;
    DWORD cMaxGlyphs = 0;
    BOOL  doGlyphs = TRUE;

    TRACE("%s, %d, 0x%08x lpOutString=%p, lpOrder=%p\n",
          debugstr_wn(lpString, uCount), uCount, dwFlags,
          lpOutString, lpOrder);

    memset(&Control, 0, sizeof(Control));
    memset(&State, 0, sizeof(State));
    if (lpGlyphs)
        *lpGlyphs = NULL;

    if (!(dwFlags & GCP_REORDER))
    {
        FIXME("Asked to reorder without reorder flag set\n");
        return FALSE;
    }

    if (lpOutString && uCountOut < uCount)
    {
        FIXME("lpOutString too small\n");
        return FALSE;
    }

    chartype = HeapAlloc(GetProcessHeap(), 0, uCount * sizeof(WORD));
    if (!chartype)
    {
        WARN("Out of memory\n");
        return FALSE;
    }

    if (lpOutString)
        memcpy(lpOutString, lpString, uCount * sizeof(WCHAR));

    is_complex = FALSE;
    for (i = 0; i < uCount && !is_complex; i++)
    {
        if ((lpString[i] >= 0x900 && lpString[i] <= 0xfff) ||
                (lpString[i] >= 0x1cd0 && lpString[i] <= 0x1cff) ||
                (lpString[i] >= 0xa840 && lpString[i] <= 0xa8ff))
            is_complex = TRUE;
    }

    /* Verify reordering will be required */
    if ((WINE_GCPW_FORCE_RTL == (dwWineGCP_Flags&WINE_GCPW_DIR_MASK)) ||
            ((dwWineGCP_Flags&WINE_GCPW_DIR_MASK) == WINE_GCPW_LOOSE_RTL))
        State.uBidiLevel = 1;
    else if (!is_complex)
    {
        done = 1;
        classify(lpString, chartype, uCount);
        for (i = 0; i < uCount; i++)
            switch (chartype[i])
            {
            case R:
            case AL:
            case RLE:
            case RLO:
                done = 0;
                break;
            }
        if (done)
        {
            HeapFree(GetProcessHeap(), 0, chartype);
            if (lpOrder)
            {
                for (i = 0; i < uCount; i++)
                    lpOrder[i] = i;
            }
            return TRUE;
        }
    }

    levels = HeapAlloc(GetProcessHeap(), 0, uCount * sizeof(BYTE));
    if (!levels)
    {
        WARN("Out of memory\n");
        HeapFree(GetProcessHeap(), 0, chartype);
        return FALSE;
    }

    maxItems = 5;
    pItems = HeapAlloc(GetProcessHeap(),0, maxItems * sizeof(SCRIPT_ITEM));
    if (!pItems)
    {
        WARN("Out of memory\n");
        HeapFree(GetProcessHeap(), 0, chartype);
        HeapFree(GetProcessHeap(), 0, levels);
        return FALSE;
    }

    if (lpGlyphs)
    {
        cMaxGlyphs = 1.5 * uCount + 16;
        run_glyphs = HeapAlloc(GetProcessHeap(),0,sizeof(WORD) * cMaxGlyphs);
        if (!run_glyphs)
        {
            WARN("Out of memory\n");
            HeapFree(GetProcessHeap(), 0, chartype);
            HeapFree(GetProcessHeap(), 0, levels);
            HeapFree(GetProcessHeap(), 0, pItems);
            return FALSE;
        }
        pwLogClust = HeapAlloc(GetProcessHeap(),0,sizeof(WORD) * uCount);
        if (!pwLogClust)
        {
            WARN("Out of memory\n");
            HeapFree(GetProcessHeap(), 0, chartype);
            HeapFree(GetProcessHeap(), 0, levels);
            HeapFree(GetProcessHeap(), 0, pItems);
            HeapFree(GetProcessHeap(), 0, run_glyphs);
            return FALSE;
        }
        psva = HeapAlloc(GetProcessHeap(),0,sizeof(SCRIPT_VISATTR) * uCount);
        if (!psva)
        {
            WARN("Out of memory\n");
            HeapFree(GetProcessHeap(), 0, chartype);
            HeapFree(GetProcessHeap(), 0, levels);
            HeapFree(GetProcessHeap(), 0, pItems);
            HeapFree(GetProcessHeap(), 0, run_glyphs);
            HeapFree(GetProcessHeap(), 0, pwLogClust);
            return FALSE;
        }
    }

    done = 0;
    glyph_i = 0;
    while (done < uCount)
    {
        unsigned j;
        classify(lpString + done, chartype, uCount - done);
        /* limit text to first block */
        i = resolveParagraphs(chartype, uCount - done);
        for (j = 0; j < i; ++j)
            switch(chartype[j])
            {
            case B:
            case S:
            case WS:
            case ON:
                chartype[j] = N;
            default:
                continue;
            }

        if ((dwWineGCP_Flags&WINE_GCPW_DIR_MASK) == WINE_GCPW_LOOSE_RTL)
            State.uBidiLevel = 1;
        else if ((dwWineGCP_Flags&WINE_GCPW_DIR_MASK) == WINE_GCPW_LOOSE_LTR)
            State.uBidiLevel = 0;

        if (dwWineGCP_Flags & WINE_GCPW_LOOSE_MASK)
        {
            for (j = 0; j < i; ++j)
                if (chartype[j] == L)
                {
                    State.uBidiLevel = 0;
                    break;
                }
                else if (chartype[j] == R || chartype[j] == AL)
                {
                    State.uBidiLevel = 1;
                    break;
                }
        }

        res = ScriptItemize(lpString + done, i, maxItems, &Control, &State, pItems, &nItems);
        while (res == E_OUTOFMEMORY)
        {
            maxItems = maxItems * 2;
            pItems = HeapReAlloc(GetProcessHeap(), 0, pItems, sizeof(SCRIPT_ITEM) * maxItems);
            if (!pItems)
            {
                WARN("Out of memory\n");
                HeapFree(GetProcessHeap(), 0, chartype);
                HeapFree(GetProcessHeap(), 0, levels);
                return FALSE;
            }
            res = ScriptItemize(lpString + done, i, maxItems, &Control, &State, pItems, &nItems);
        }

        if (lpOutString || lpOrder)
            for (j = 0; j < nItems; j++)
            {
                int k;
                for (k = pItems[j].iCharPos; k < pItems[j+1].iCharPos; k++)
                    levels[k] = pItems[j].a.s.uBidiLevel;
            }

        if (lpOutString)
        {
            /* assign directional types again, but for WS, S this time */
            classify(lpString + done, chartype, i);

            BidiLines(State.uBidiLevel, lpOutString + done, lpString + done,
                      chartype, levels, i, 0);
        }

        if (lpOrder)
        {
            int k, lastgood;
            for (j = lastgood = 0; j < i; ++j)
                if (levels[j] != levels[lastgood])
                {
                    --j;
                    if (odd(levels[lastgood]))
                        for (k = j; k >= lastgood; --k)
                            lpOrder[done + k] = done + j - k;
                    else
                        for (k = lastgood; k <= j; ++k)
                            lpOrder[done + k] = done + k;
                    lastgood = ++j;
                }
            if (odd(levels[lastgood]))
                for (k = j - 1; k >= lastgood; --k)
                    lpOrder[done + k] = done + j - 1 - k;
            else
                for (k = lastgood; k < j; ++k)
                    lpOrder[done + k] = done + k;
        }

        if (lpGlyphs && doGlyphs)
        {
            int j;
            BYTE runOrder[maxItems];
            int visOrder[maxItems];
            SCRIPT_ITEM *curItem;

            for (j = 0; j < nItems; j++)
                runOrder[j] = pItems[j].a.s.uBidiLevel;

            ScriptLayout(nItems, runOrder, visOrder, NULL);

            for (j = 0; j < nItems; j++)
            {
                int k;
                int cChars,cOutGlyphs;
                curItem = &pItems[visOrder[j]];

                cChars = pItems[visOrder[j]+1].iCharPos - curItem->iCharPos;

                res = ScriptShape(hDC, &psc, lpString + done + curItem->iCharPos, cChars, cMaxGlyphs, &curItem->a, run_glyphs, pwLogClust, psva, &cOutGlyphs);
                while (res == E_OUTOFMEMORY)
                {
                    cMaxGlyphs *= 2;
                    run_glyphs = HeapReAlloc(GetProcessHeap(), 0, run_glyphs, sizeof(WORD) * cMaxGlyphs);
                    if (!run_glyphs)
                    {
                        WARN("Out of memory\n");
                        HeapFree(GetProcessHeap(), 0, chartype);
                        HeapFree(GetProcessHeap(), 0, levels);
                        HeapFree(GetProcessHeap(), 0, pItems);
                        HeapFree(GetProcessHeap(), 0, psva);
                        HeapFree(GetProcessHeap(), 0, pwLogClust);
                        HeapFree(GetProcessHeap(), 0, *lpGlyphs);
                        ScriptFreeCache(&psc);
                        *lpGlyphs = NULL;
                        return FALSE;
                    }
                    res = ScriptShape(hDC, &psc, lpString + done + curItem->iCharPos, cChars, cMaxGlyphs, &curItem->a, run_glyphs, pwLogClust, psva, &cOutGlyphs);
                }
                if (res)
                {
                    if (res == USP_E_SCRIPT_NOT_IN_FONT)
                        TRACE("Unable to shape with currently selected font\n");
                    else
                        FIXME("Unable to shape string (%x)\n",res);
                    j = nItems;
                    doGlyphs = FALSE;
                    HeapFree(GetProcessHeap(), 0, *lpGlyphs);
                    *lpGlyphs = NULL;
                }
                else
                {
                    if (*lpGlyphs)
                        *lpGlyphs = HeapReAlloc(GetProcessHeap(), 0, *lpGlyphs, sizeof(WORD) * (glyph_i + cOutGlyphs));
                    else
                        *lpGlyphs = HeapAlloc(GetProcessHeap(), 0, sizeof(WORD) * (glyph_i + cOutGlyphs));
                    for (k = 0; k < cOutGlyphs; k++)
                        (*lpGlyphs)[glyph_i+k] = run_glyphs[k];
                    glyph_i += cOutGlyphs;
                }
            }
        }

        done += i;
    }
    if (cGlyphs)
        *cGlyphs = glyph_i;

    HeapFree(GetProcessHeap(), 0, chartype);
    HeapFree(GetProcessHeap(), 0, levels);
    HeapFree(GetProcessHeap(), 0, pItems);
    HeapFree(GetProcessHeap(), 0, run_glyphs);
    HeapFree(GetProcessHeap(), 0, pwLogClust);
    HeapFree(GetProcessHeap(), 0, psva);
    ScriptFreeCache(&psc);
    return TRUE;
}