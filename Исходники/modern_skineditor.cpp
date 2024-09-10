int GetFileSizes(HWND hwndDlg)
{
	char buf[MAX_PATH];
	SIZE sz={0};
	SendDlgItemMessageA(hwndDlg,IDC_FILE,WM_GETTEXT,(WPARAM)MAX_PATH,(LPARAM)buf);
	ske_GetFullFilename(buf,buf,0,TRUE);
	{
		HBITMAP hbmp=ske_LoadGlyphImage(buf);
		if (hbmp)
		{
			BITMAP bm={0};
			GetObject(hbmp,sizeof(BITMAP),&bm);
			sz.cx=bm.bmWidth;
			sz.cy=bm.bmHeight;
			ske_UnloadGlyphImage(hbmp);
		}
	}
	_snprintf(buf, MAX_PATH, "%s %d x %d %s",Translate("Image size is"),sz.cx, sz.cy, Translate("pixels")); 
	SendDlgItemMessageA(hwndDlg,IDC_S_SIZE,WM_SETTEXT,0,(LPARAM)buf);
	return 0;
}