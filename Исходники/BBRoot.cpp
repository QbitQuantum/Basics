static HBITMAP read_bitmap(const char* path, bool delete_after)
{
    HWND hwnd_desk = GetDesktopWindow();
    HDC hdc_desk = GetDC(hwnd_desk);
    BITMAP bm;
#if 0
    HBITMAP bmp = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
#else
    HBITMAP bmp = NULL;
    FILE *fp=fopen(path, "rb");
    if (fp)
    {
        BITMAPFILEHEADER hdr;
        fread(&hdr, 1, sizeof(hdr), fp);
        if (0x4D42 == hdr.bfType)
        {
            BITMAPINFOHEADER bih, *pbih; int CU, s; void *lpBits;
            fread(&bih, 1, sizeof(bih), fp);
            CU = bih.biClrUsed * sizeof(RGBQUAD);
            pbih = (PBITMAPINFOHEADER)m_alloc(bih.biSize + CU);
            memmove(pbih, &bih, bih.biSize);
            fread(&((BITMAPINFO*)pbih)->bmiColors, 1, CU, fp);
            s = hdr.bfSize - hdr.bfOffBits;
            lpBits = m_alloc(s);
            fseek(fp, hdr.bfOffBits, SEEK_SET);
            fread(lpBits, 1, s, fp);
            bmp = CreateDIBitmap(hdc_desk, pbih, CBM_INIT, lpBits, (LPBITMAPINFO)pbih, DIB_RGB_COLORS);
            m_free(lpBits);
            m_free(pbih);
        }
        fclose(fp);
    }
#endif
    if (bmp && GetObject(bmp, sizeof bm, &bm))
    {
        // convert in any case (20ms), bc if it's compatible, it's faster to paint.
        HDC hdc_old = CreateCompatibleDC(hdc_desk);
        HGDIOBJ old_bmp = SelectObject(hdc_old, bmp);
        HDC hdc_new = CreateCompatibleDC(hdc_desk);
        HBITMAP bmp_new = CreateCompatibleBitmap(hdc_desk, VScreenWidth, VScreenHeight);
        SelectObject(hdc_new, bmp_new);
        StretchBlt(hdc_new, 0, 0, VScreenWidth, VScreenHeight, hdc_old, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        DeleteDC(hdc_new);
        DeleteObject(SelectObject(hdc_old, old_bmp));
        DeleteDC(hdc_old);
        bmp = bmp_new;
    }

    ReleaseDC(hwnd_desk, hdc_desk);
    if (delete_after)
        DeleteFile(path);
    return bmp;
}