BOOL WINAPI ChangeBackground(HBITMAP& hNewBGBitmap, DWORD& dwOverlayBGColor)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	srand(time(NULL)+GetTickCount());
	dwOverlayBGColor=COLORKEY;
	objSettings.dbBgImage.Destroy();
	objSettings.szBitmapSize=GetBitmapSize(hNewBGBitmap);
	objSettings.dbBgImage.Create(objSettings.szBitmapSize.cx, objSettings.szBitmapSize.cy);
	CDC dcScreen,dcReal;
	dcScreen.CreateDC("DISPLAY", NULL, NULL, NULL);
	dcReal.CreateCompatibleDC(&dcScreen);
	HBITMAP hbmpTmp=(HBITMAP)CopyImage(hNewBGBitmap,IMAGE_BITMAP, objSettings.szBitmapSize.cx, objSettings.szBitmapSize.cy, 0);
	objSettings.dbBgImage.SetBitmap(&dcReal,hbmpTmp);
	DWORD dwErr=GetLastError();
	ClearBitmap(hbmpTmp);
	InitImage();
	return TRUE;
};