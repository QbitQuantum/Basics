Bool CWinVideoGrabber::Draw(int twidth,int theight, HDC hdcMem)
{
	if (!inited) return False;
	HGLOBAL videodib = NULL;
	char *dibdata = NULL;
	char *dibbits = NULL;
	BITMAPINFO *pbmp;
	Bool res = False;
	capEditCopy(videowindow); // Copy the frame in the clipboard as a DIB
	OpenClipboard(parentwindow);
	if (IsClipboardFormatAvailable(CF_DIB)){
		videodib=GetClipboardData(CF_DIB);
		dibdata = (char *)GlobalLock(videodib);
		pbmp = (BITMAPINFO *)dibdata;
		int tsourcewidth  = pbmp->bmiHeader.biWidth;
		int tsourceheight = pbmp->bmiHeader.biHeight;
		int palentries = pbmp->bmiHeader.biClrUsed;
		int bitcount = pbmp->bmiHeader.biBitCount;
		int lenrgb = 0;
		if (bitcount < 24) {
			if (palentries == 0)
				palentries = (1 << bitcount);
			lenrgb = palentries * sizeof(RGBQUAD);
		}
		dibbits = (char *)(dibdata + sizeof(BITMAPINFOHEADER) + lenrgb);
		StretchDIBits(hdcMem,0,0,twidth,theight,0,0,tsourcewidth,tsourceheight,
			(BITMAPINFO *)dibbits, pbmp, DIB_RGB_COLORS,SRCCOPY);
		GlobalUnlock(videodib);
		res = True;
	}
	CloseClipboard();
	return res;
}