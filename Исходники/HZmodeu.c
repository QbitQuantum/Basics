BOOL CharHandleU( HIMC hIMC,WORD wParam,LONG lParam)
{
    LPINPUTCONTEXT lpIMC;
	LPCANDIDATEINFO lpCandInfo;
	LPCANDIDATELIST lpCandList;
	LPCOMPOSITIONSTRING lpCompStr;
	WORD wHead;

    lpIMC = ImmLockIMC(hIMC);
	lpCandInfo = (LPCANDIDATEINFO)ImmLockIMCC(lpIMC->hCandInfo);
	lpCandList = (LPCANDIDATELIST)((LPSTR)lpCandInfo  + lpCandInfo->dwOffset[0]);
	lpCompStr = (LPCOMPOSITIONSTRING)ImmLockIMCC(lpIMC->hCompStr);
	

	if( !lpCandList->dwCount ){
		int i;
		
		
		wHead = wParam - _T('!');

		for( i=0;_tcslen(aPunct[wHead][i]);i++){
			_tcscpy(GETLPCANDSTR(lpCandList,i+2),aPunct[wHead][i]);
		}

		if( i == 0)  MessageBeep(0xFFFFFFFF );
		else if( i == 1 ){
			LPTSTR lpConvStr;
			lpConvStr = ((LPMYCOMPSTR)lpCompStr)->FreePYComp.szConvCompStr;
			_tcscpy(lpConvStr,aPunct[wHead][0]);
			MakeResultString(hIMC,TRUE);
		}
		else {
			LPTSTR lpStr;
			WORD wStrLen;

			lpStr = GETLPCOMPSTR(lpCompStr);
			wStrLen = _tcslen(lpStr);
			*(lpStr + wStrLen) = (TCHAR)wParam;
			*(lpStr + wStrLen +1) = _T('\0');

			lpStr = ((LPMYCOMPSTR)lpCompStr)->FreePYComp.szPaintCompStr;
			wStrLen = _tcslen(lpStr);
			*(lpStr + wStrLen) = (TCHAR)wParam;
			*(lpStr + wStrLen +1) = _T('\0');

			lpCandList->dwSelection = 0;
			lpCandList->dwCount = i;
			lpCandList->dwPageStart = 2;
			lpCandList->dwPageSize = 0;
			SelectForwardFromCand(hIMC,lpCandList);
		}
	}
	else{
		if( wParam == _T('=') || wParam == _T('.') || wParam == _T('>')) {
			SelectForwardFromCand(hIMC,lpCandList);
		}
		else if( wParam == _T('-') || wParam == _T(',') || wParam == _T('<')) {
			SelectBackwardFromCand(hIMC,lpCandList);
		}
		else if( wParam >= _T('0') && wParam <= _T('9') ){
			SelectCandFromCandlist(hIMC, wParam);
		}
	}

	ImmUnlockIMCC(lpIMC->hCompStr);
	ImmUnlockIMCC(lpIMC->hCandInfo);
	ImmUnlockIMC(hIMC);
	return TRUE;
}