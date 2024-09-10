void UpdateOSDEx(LPCSTR lpText, LPRTSS_SHARED_MEMORY pMem, char *OSD)
{
	lstrcpyn(OSD, lpText, 255);
	pMem->dwOSDFrame++;
	FlushViewOfFile(pMem, 0);
}