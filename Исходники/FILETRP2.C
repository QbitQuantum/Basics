void PEXPORT KppReplaceAtomInText(LPFUNC lpFunc,
				  ATOMID idAtom, LPREPLACEKEY rk)
{
    int idFile = BFILE(lpFunc);
    unsigned long lBegin = BFPOS(lpFunc);
    WORD wLen = BFLEN(lpFunc);
    GLOBALHANDLE hMem;
    LPSTR lpMem, lpAtom, lpBegin, lpEnd, lpPrev;
    FILE *fp = NULL;
    char atom[RET_BUFFER_LEN];
    WORD wAtomLen;
    
    if (!rk->wLen)
        return;
    wAtomLen = KppGetAtomName(idAtom, atom, RET_BUFFER_LEN);
    if (!wAtomLen)
        return;
    
    hMem = KppGetBodyFromFile(idFile, lBegin, wLen, "rb", TRUE);
    if (!hMem)
        return;
    
    lpMem = GLOBALLOCK(hMem);
    
    if (idFile != -1)
    {
        lpMem = KppExtractBody(lpMem, TRUE);
        if (!lpMem)
        {
            GLOBALUNLOCK(hMem);
            GLOBALFREE(hMem);
            return;
        }
    }
    
    lpPrev = NULL;
    lpBegin = lpMem;
    while (lpAtom = find_match(rk, lpMem, atom, &lpEnd, wAtomLen)) {
        if (is_atom_match(lpMem, &lpAtom, &lpEnd, &lpPrev, rk, wAtomLen))
        {
            if (!fp)
            {
                fp = fopen_share(KppGetTmpSaveFileName(), "ab");
                if (!fp)
                {
                    GLOBALUNLOCK(hMem);
                    GLOBALFREE(hMem);
                    return;
                }
                else
                {
                    fputc('\r', fp);
                    fputc('\n', fp);
                    lBegin = ftell(fp);
                }
            }

            if (lpAtom > lpBegin)
                fwrite(lpBegin, 1, lpAtom - lpBegin, fp);
                
            if (rk->rx)
            {
                char replace[RET_BUFFER_LEN];
                BOOL bTruncated;
                
                KppRegsub(rk->rx, rk->lpReplace, replace, RET_BUFFER_LEN,
                          &bTruncated);
                fputs(replace, fp);
            }
            else
                fputs(rk->lpReplace, fp);
            
            lpBegin = lpEnd;
        }
        else if (fp)
        {
            fwrite(lpMem, 1, (lpAtom - lpMem) + wAtomLen, fp);
            lpBegin = lpEnd;
        }

        lpMem = lpEnd;
    }
                           
    if (fp)
    {
        fputs(lpMem, fp);
        BFILE(lpFunc) = -1;
        BFPOS(lpFunc) = lBegin;
        BFLEN(lpFunc) = ftell(fp) - lBegin;
        fclose(fp);
    }
    
    GLOBALUNLOCK(hMem);
    GLOBALFREE(hMem);
}