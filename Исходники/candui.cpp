void ChangeCand(HWND hUIWnd)
{
    LPUIPRIV        lpUIPriv;
    HIMC            hIMC;
    CONST INPUTCONTEXT * lpIMC;
    LPCANDIDATEINFO lpCandInfo;
    LPCANDIDATELIST lpCandList;
    int             nCandWi, nCandHi;

    lpUIPriv = (LPUIPRIV)GetWindowLong(hUIWnd, IMMGWL_PRIVATE);
    if (!lpUIPriv) {
        return;
    }

    if (!(lpUIPriv->fdwUIFlags & UI_CAND_ALREADY_OPEN)) {
        return;
    }

    hIMC = (HIMC)GetWindowLong(hUIWnd, IMMGWL_IMC);
    if (!hIMC) {
        return;
    }

    lpIMC = (CONST INPUTCONTEXT *)ImmLockIMC(hIMC);
    if (!lpIMC) {
        return;
    }

    if (!lpIMC->hCandInfo) {
        ImmUnlockIMC(hIMC);
        return;
    }

    lpCandInfo = (LPCANDIDATEINFO)ImmLockIMCC(lpIMC->hCandInfo);
    if (!lpCandInfo) {
        goto ChangeCandUnlockIMCC;
    }

    lpCandList = (LPCANDIDATELIST)((LPBYTE)lpCandInfo + lpCandInfo->dwOffset[0]);

    lpUIPriv->lpCandList = lpCandList;

    nCandWi = lpUIPriv->nCandWi;
    nCandHi = lpUIPriv->nCandHi;

    CalcCandSize(lpUIPriv->hCandWnd);

    if (nCandWi != lpUIPriv->nCandWi ||
        nCandHi != lpUIPriv->nCandHi) {
        SetWindowPos(lpUIPriv->hCandWnd, NULL, 0, 0,
                     lpUIPriv->nCandWi, lpUIPriv->nCandHi,
                     SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
        SetWindowPos(lpUIPriv->hScrBar, NULL,
                     lpUIPriv->rcCandText.right, lpUIPriv->rcCandText.top,
                     g_sImeUIG.cxVScroll, (lpUIPriv->rcCandText.bottom - lpUIPriv->rcCandText.top),
                     SWP_NOACTIVATE|SWP_NOZORDER);
    }

    InvalidateRect(lpUIPriv->hCandWnd, NULL, TRUE);
    ShowCand(hUIWnd, SW_SHOWNOACTIVATE);

ChangeCandUnlockIMCC:
    ImmUnlockIMCC(lpIMC->hCandInfo);

    ImmUnlockIMC(hIMC);

    return;
}