static bool DoDdePoke(HWND hwndServerDDE, HWND hwndClientDDE, LPCSTR szItem, LPCSTR szValue)
{
	HANDLE hPokeData = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, sizeof(DDEPOKE) + strlen(szValue) + 2);

	if (!hPokeData)
		return false;

	DDEPOKE* lpPokeData = (DDEPOKE*)GlobalLock(hPokeData);

	if (lpPokeData) 
	{ 
		lpPokeData->fRelease = true; 
		lpPokeData->cfFormat = CF_TEXT;

		strcpy(LPSTR(lpPokeData->Value), szValue);

		// Each line of CF_TEXT data is terminated by CR/LF. 
		strcat(LPSTR(lpPokeData->Value), "\r\n"); 

		GlobalUnlock(hPokeData);

		ATOM atomItem = GlobalAddAtom(szItem);

		if (atomItem)
		{ 
			if (PostMessage(hwndServerDDE, WM_DDE_POKE, (WPARAM) hwndClientDDE, PackDDElParam(WM_DDE_POKE, UINT(hPokeData), atomItem)))
				return true;

			GlobalDeleteAtom(atomItem); 
		}
	}

	GlobalFree(hPokeData);

	return false;
}