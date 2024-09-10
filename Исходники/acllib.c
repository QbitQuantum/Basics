void loadImage(const char *image, ACL_Image *mapbuf)
{
	HDC hmapdc;
	IPicture *ipicture;
	IStream *istream;
	DWORD filesize = 0, bytes;
	OLE_XSIZE_HIMETRIC width;
	OLE_YSIZE_HIMETRIC height;
	HANDLE file = NULL;
	HGLOBAL global = NULL;
	LPVOID data = NULL;

	ACL_ASSERT_HWND;

	file = CreateFileA(image, GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
	if(file == INVALID_HANDLE_VALUE)
		acl_error("Fail to load image, File not exist");
	filesize = GetFileSize(file, NULL);
	
	global = GlobalAlloc(GMEM_MOVEABLE, filesize);
	data = GlobalLock(global);
	ReadFile(file, data, filesize, &bytes, NULL);
	GlobalUnlock(global);
	CreateStreamOnHGlobal(global, TRUE, &istream);
	
	OleLoadPicture(istream, filesize, TRUE, &IID_IPicture, (LPVOID*)&ipicture);
	ipicture->lpVtbl->get_Width(ipicture, &width);
	ipicture->lpVtbl->get_Height(ipicture, &height);

	mapbuf->width = (int)(width / 26.45833333333);
	mapbuf->height = (int)(height / 26.45833333333);
	
	hmapdc = CreateCompatibleDC(GetDC(g_hWnd));
	if (mapbuf->hbitmap != NULL)
		DeleteObject(mapbuf->hbitmap);
	mapbuf->hbitmap = CreateCompatibleBitmap(GetDC(g_hWnd), mapbuf->width, mapbuf->height);
	SelectObject(hmapdc, mapbuf->hbitmap);

    ipicture->lpVtbl->Render(ipicture, hmapdc, 0, 0, mapbuf->width, mapbuf->height, 0, height, width, -height, NULL);
	ipicture->lpVtbl->Release(ipicture);
	istream->lpVtbl->Release(istream);

	DeleteDC(hmapdc);
	GlobalFree(global);
	CloseHandle(file);
} 