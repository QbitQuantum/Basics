VOID OpenImage(HWND hWnd, LPCWSTR fileName)
{
	HDC windowDC = GetDC(hWnd);
	HENHMETAFILE hemf = GetEnhMetaFile(fileName);  
	GetClientRect(hWnd, &rect); 
	ClearWindow(memoryDC);
	RefreshMetafileDC(hWnd);
	PlayEnhMetaFile(memoryDC, hemf, &rect);
	PlayEnhMetaFile(metafileDC, hemf, &rect);
	ReleaseDC(hWnd, windowDC); 
	DeleteEnhMetaFile(hemf);
}