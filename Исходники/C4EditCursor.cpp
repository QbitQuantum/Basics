bool SetMenuItemText(HMENU hMenu, WORD id, const char *szText)
{
	MENUITEMINFOW minfo;
	ZeroMem(&minfo,sizeof(minfo));
	minfo.cbSize = sizeof(minfo);
	minfo.fMask = MIIM_ID | MIIM_TYPE | MIIM_DATA;
	minfo.fType = MFT_STRING;
	minfo.wID = id;
	StdBuf td = GetWideCharBuf(szText);
	minfo.dwTypeData = getMBufPtr<wchar_t>(td);
	minfo.cch = wcslen(minfo.dwTypeData);
	return !!SetMenuItemInfoW(hMenu,id,false,&minfo);
}