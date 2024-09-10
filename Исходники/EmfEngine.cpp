bool EmfPaintEngine::begin(QPaintDevice* p)
{
	if (!p)
		return false;

	setPaintDevice(p);

	HWND desktop = GetDesktopWindow();
	HDC dc = GetDC(desktop);
	PCSTR description = "Metafile created\0with EmfEngine\0";

	metaDC = CreateEnhMetaFileA(dc, fname.toLocal8Bit().data(), &d_rect, description);//create null rectangle metafile

	d_rect.left = 0;
	d_rect.top = 0;
	d_rect.right = 100*p->width()*GetDeviceCaps(metaDC, HORZSIZE)/(double)GetDeviceCaps(metaDC, HORZRES);
	d_rect.bottom = 100*p->height()*GetDeviceCaps(metaDC, VERTSIZE)/(double)GetDeviceCaps(metaDC, VERTRES);

	end();//delete the dummy metafile

	metaDC = CreateEnhMetaFileA(dc, fname.toLocal8Bit().data(), &d_rect, description);

	SetWindowExtEx(metaDC, p->width(), p->height(), 0);
	SetViewportExtEx(metaDC, p->width(), p->height(), 0);

	return true;
}