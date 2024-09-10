BOOL IsCandidate(HIMC hIMC)
{
    LPINPUTCONTEXT lpIMC;
    LPCANDIDATEINFO lpCandInfo;
	LPCANDIDATELIST lpCandList;
    BOOL fRet = FALSE;

    if (!(lpIMC = ImmLockIMC(hIMC)))
        return FALSE;

    if (ImmGetIMCCSize(lpIMC->hCandInfo) < sizeof (CANDIDATEINFO)){
		ImmUnlockIMC(hIMC);
        return FALSE;
	}

    lpCandInfo = (LPCANDIDATEINFO)ImmLockIMCC(lpIMC->hCandInfo);
	lpCandList = (LPCANDIDATELIST)((LPBYTE)lpCandInfo  + lpCandInfo->dwOffset[0]);

    fRet = (lpCandList->dwCount > 0);

    ImmUnlockIMCC(lpIMC->hCandInfo);
	ImmUnlockIMC(hIMC);
    return fRet;
}