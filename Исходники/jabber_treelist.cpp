int TreeList_AddIcon(HWND hwnd, HICON hIcon, int iOverlay)
{
	HIMAGELIST hIml = ListView_GetImageList(hwnd, LVSIL_SMALL);
	int idx = ImageList_AddIcon(hIml, hIcon);
	g_ReleaseIcon(hIcon);
	if (iOverlay) ImageList_SetOverlayImage(hIml, idx, iOverlay);
	return idx;
}