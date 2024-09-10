HKL GetLayoutOfText(LPCTSTR ptszInText)
{
	HKL hklCurLay = hklLayouts[0];
	LPTSTR ptszKeybBuff = ptszLayStrings[0];
	DWORD dwMaxSymbols = 0, dwTemp = 0;

	for (DWORD j = 0; j < _tcslen(ptszInText); j++)
		if (_tcschr(ptszKeybBuff, ptszInText[j]) != NULL)
			++dwMaxSymbols;

	for (DWORD i = 1; i < bLayNum; i++) {
		ptszKeybBuff = ptszLayStrings[i];
		DWORD dwCountSymbols = 0;
			
		for (DWORD j = 0; j<_tcslen(ptszInText); j++)
			if (_tcschr(ptszKeybBuff, ptszInText[j]) != NULL)
				++dwCountSymbols;
		
		if (dwCountSymbols == dwMaxSymbols)
			dwTemp = dwCountSymbols;
		else if (dwCountSymbols>dwMaxSymbols) {
			dwMaxSymbols = dwCountSymbols;
			hklCurLay = hklLayouts[i];
		}
	}

	if (dwMaxSymbols == dwTemp)
		hklCurLay = GetKeyboardLayout(0);
	
	return hklCurLay;
}