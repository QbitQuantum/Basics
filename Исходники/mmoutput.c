BOOL    MCIAVI_OpenVideo(WINE_MCIAVI* wma)
{
    HDC hDC;
    DWORD	outSize;
    FOURCC	fcc = wma->ash_video.fccHandler;

    TRACE("fcc %4.4s\n", (LPSTR)&fcc);

    wma->dwCachedFrame = -1;

    /* get the right handle */
    if (fcc == mmioFOURCC('C','R','A','M')) fcc = mmioFOURCC('M','S','V','C');

    /* try to get a decompressor for that type */
    wma->hic = ICLocate(ICTYPE_VIDEO, fcc, wma->inbih, NULL, ICMODE_DECOMPRESS);
    if (!wma->hic) {
        /* check for builtin DIB compressions */
        fcc = wma->inbih->biCompression;
        if ((fcc == mmioFOURCC('D','I','B',' ')) ||
            (fcc == mmioFOURCC('R','L','E',' ')) ||
            (fcc == BI_RGB) || (fcc == BI_RLE8) ||
            (fcc == BI_RLE4) || (fcc == BI_BITFIELDS))
            goto paint_frame;

	WARN("Can't locate codec for the file\n");
	return FALSE;
    }

    outSize = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);

    wma->outbih = HeapAlloc(GetProcessHeap(), 0, outSize);
    if (!wma->outbih) {
	WARN("Can't alloc output BIH\n");
	return FALSE;
    }
    if (!ICGetDisplayFormat(wma->hic, wma->inbih, wma->outbih, 0, 0, 0)) {
	WARN("Can't open decompressor\n");
	return FALSE;
    }

    TRACE("bih.biSize=%d\n", 		wma->outbih->biSize);
    TRACE("bih.biWidth=%d\n", 		wma->outbih->biWidth);
    TRACE("bih.biHeight=%d\n", 	wma->outbih->biHeight);
    TRACE("bih.biPlanes=%d\n", 		wma->outbih->biPlanes);
    TRACE("bih.biBitCount=%d\n", 	wma->outbih->biBitCount);
    TRACE("bih.biCompression=%x\n", 	wma->outbih->biCompression);
    TRACE("bih.biSizeImage=%d\n", 	wma->outbih->biSizeImage);
    TRACE("bih.biXPelsPerMeter=%d\n", 	wma->outbih->biXPelsPerMeter);
    TRACE("bih.biYPelsPerMeter=%d\n", 	wma->outbih->biYPelsPerMeter);
    TRACE("bih.biClrUsed=%d\n", 	wma->outbih->biClrUsed);
    TRACE("bih.biClrImportant=%d\n", 	wma->outbih->biClrImportant);

    wma->outdata = HeapAlloc(GetProcessHeap(), 0, wma->outbih->biSizeImage);
    if (!wma->outdata) {
	WARN("Can't alloc output buffer\n");
	return FALSE;
    }

    if (ICSendMessage(wma->hic, ICM_DECOMPRESS_BEGIN,
		      (DWORD_PTR)wma->inbih, (DWORD_PTR)wma->outbih) != ICERR_OK) {
	WARN("Can't begin decompression\n");
	return FALSE;
    }

paint_frame:
    hDC = wma->hWndPaint ? GetDC(wma->hWndPaint) : 0;
    if (hDC)
    {
        MCIAVI_PaintFrame(wma, hDC);
        ReleaseDC(wma->hWndPaint, hDC);
    }
    return TRUE;
}