static bool_t LoadDriver(gapi* p)
{
	HMODULE GX;
	tchar_t Path[MAXPATH];

	if (p->Windows)
		GetSystemPath(Path,TSIZEOF(Path),T("gx.dll"));
	else
		tcscpy_s(Path,TSIZEOF(Path),T("gx.dll"));

	if ((GX = LoadLibrary(Path))==NULL)
	{
		if (!p->Windows)
		{
			p->Windows = 1;
			return LoadDriver(p);
		}
		return 0;
	}

	if (p->GX)
		FreeLibrary(p->GX);
	p->GX = GX;

	GetProc(&p->GX,&p->GXOpenDisplay,T("?GXOpenDisplay@@YAHPAUHWND__@@K@Z"),0);
	GetProc(&p->GX,&p->GXCloseDisplay,T("?GXCloseDisplay@@YAHXZ"),0);
	GetProc(&p->GX,&p->GXBeginDraw,T("?GXBeginDraw@@YAPAXXZ"),0);
	GetProc(&p->GX,&p->GXEndDraw,T("?GXEndDraw@@YAHXZ"),0);
	GetProc(&p->GX,&p->GXGetDisplayProperties,T("?GXGetDisplayProperties@@YA?AUGXDisplayProperties@@XZ"),0);
	GetProc(&p->GX,&p->GXSetViewport,T("?GXSetViewport@@YAHKKKK@Z"),1);
	GetProc(&p->GX,&p->GXIsDisplayDRAMBuffer,T("?GXIsDisplayDRAMBuffer@@YAHXZ"),1);

	return p->GX!=NULL;
}