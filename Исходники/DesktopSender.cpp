int savepng(TCHAR *szFilename)
{
    HDC hdcSrc = GetDC(NULL);
    int nBitPerPixel = GetDeviceCaps(hdcSrc, BITSPIXEL);
    int nWidth = GetDeviceCaps(hdcSrc, HORZRES);
    int nHeight = GetDeviceCaps(hdcSrc, VERTRES);
    CImage image;
    image.Create(nWidth, nHeight, nBitPerPixel);
    BitBlt(image.GetDC(), 0, 0, nWidth, nHeight, hdcSrc, 0, 0, SRCCOPY);
    ReleaseDC(NULL, hdcSrc);
    image.ReleaseDC();
    image.Save(szFilename, Gdiplus::ImageFormatPNG);//ImageFormatJPEG
    return 0;
}