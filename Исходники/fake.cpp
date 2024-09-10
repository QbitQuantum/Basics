BOOL WINAPI __GetSaveFileNameW(LPOPENFILENAMEW lpofn) {
	if (g_bOutput)
		if (!wcscmp(lpofn->lpstrTitle, L"Save .VDR signpost for AVIFile handler"))
			return FALSE;
	return GetSaveFileNameW(lpofn);
}