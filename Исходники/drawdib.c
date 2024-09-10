/***********************************************************************
 *              DrawDibBegin            [MSVFW32.@]
 */
BOOL VFWAPI DrawDibBegin(HDRAWDIB hdd,
                         HDC      hdc,
                         INT      dxDst,
                         INT      dyDst,
                         LPBITMAPINFOHEADER lpbi,
                         INT      dxSrc,
                         INT      dySrc,
                         UINT     wFlags) 
{
    BOOL ret = TRUE;
    WINE_HDD *whdd;

    TRACE("(%p,%p,%d,%d,%p,%d,%d,0x%08x)\n",
          hdd, hdc, dxDst, dyDst, lpbi, dxSrc, dySrc, wFlags);

    TRACE("lpbi: %d,%d/%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
          lpbi->biSize, lpbi->biWidth, lpbi->biHeight, lpbi->biPlanes,
          lpbi->biBitCount, lpbi->biCompression, lpbi->biSizeImage,
          lpbi->biXPelsPerMeter, lpbi->biYPelsPerMeter, lpbi->biClrUsed,
          lpbi->biClrImportant);

    if (wFlags & ~(DDF_BUFFER))
        FIXME("wFlags == 0x%08x not handled\n", wFlags & ~(DDF_BUFFER));

    whdd = MSVIDEO_GetHddPtr(hdd);
    if (!whdd) return FALSE;

    if (whdd->begun) DrawDibEnd(hdd);

    if (lpbi->biCompression) 
    {
        DWORD size = 0;

        whdd->hic = ICOpen(ICTYPE_VIDEO, lpbi->biCompression, ICMODE_DECOMPRESS);
        if (!whdd->hic) 
        {
            WARN("Could not open IC. biCompression == 0x%08x\n", lpbi->biCompression);
            ret = FALSE;
        }

        if (ret) 
        {
            size = ICDecompressGetFormat(whdd->hic, lpbi, NULL);
            if (size == ICERR_UNSUPPORTED) 
            {
                WARN("Codec doesn't support GetFormat, giving up.\n");
                ret = FALSE;
            }
        }

        if (ret) 
        {
            whdd->lpbiOut = HeapAlloc(GetProcessHeap(), 0, size);

            if (ICDecompressGetFormat(whdd->hic, lpbi, whdd->lpbiOut) != ICERR_OK)
                ret = FALSE;
        }

        if (ret) 
        {
            /* FIXME: Use Ex functions if available? */
            if (ICDecompressBegin(whdd->hic, lpbi, whdd->lpbiOut) != ICERR_OK)
                ret = FALSE;
            
            TRACE("biSizeImage == %d\n", whdd->lpbiOut->biSizeImage);
            TRACE("biCompression == %d\n", whdd->lpbiOut->biCompression);
            TRACE("biBitCount == %d\n", whdd->lpbiOut->biBitCount);
        }
    }
    else 
    {
        DWORD dwSize;
        /* No compression */
        TRACE("Not compressed!\n");
        if (lpbi->biHeight <= 0)
        {
            /* we don't draw inverted DIBs */
            TRACE("detected inverted DIB\n");
            ret = FALSE;
        }
        else
        {
            dwSize = lpbi->biSize + num_colours(lpbi)*sizeof(RGBQUAD);
            whdd->lpbiOut = HeapAlloc(GetProcessHeap(), 0, dwSize);
            memcpy(whdd->lpbiOut, lpbi, dwSize);
        }
    }

    if (ret) 
    {
        /*whdd->lpvbuf = HeapAlloc(GetProcessHeap(), 0, whdd->lpbiOut->biSizeImage);*/

        whdd->hMemDC = CreateCompatibleDC(hdc);
        TRACE("Creating: %d, %p\n", whdd->lpbiOut->biSize, whdd->lpvbits);
        whdd->hDib = CreateDIBSection(whdd->hMemDC, (BITMAPINFO *)whdd->lpbiOut, DIB_RGB_COLORS, &(whdd->lpvbits), 0, 0);
        if (whdd->hDib) 
        {
            TRACE("Created: %p,%p\n", whdd->hDib, whdd->lpvbits);
        }
        else
        {
            ret = FALSE;
            TRACE("Error: %d\n", GetLastError());
        }
        whdd->hOldDib = SelectObject(whdd->hMemDC, whdd->hDib);
    }

    if (ret) 
    {
        whdd->hdc = hdc;
        whdd->dxDst = dxDst;
        whdd->dyDst = dyDst;
        whdd->lpbi = HeapAlloc(GetProcessHeap(), 0, lpbi->biSize);
        memcpy(whdd->lpbi, lpbi, lpbi->biSize);
        whdd->dxSrc = dxSrc;
        whdd->dySrc = dySrc;
        whdd->begun = TRUE;
        whdd->hpal = 0;
    } 
    else 
    {
        if (whdd->hic)
            ICClose(whdd->hic);
        HeapFree(GetProcessHeap(), 0, whdd->lpbiOut);
        whdd->lpbiOut = NULL;
    }

    return ret;
}