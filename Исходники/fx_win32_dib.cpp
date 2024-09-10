CFX_DIBitmap* CFX_WindowsDIB::LoadDIBitmap(WINDIB_Open_Args_ args)
{
    CWin32Platform* pPlatform = (CWin32Platform*)CFX_GEModule::Get()->GetPlatformData();
    if (pPlatform->m_GdiplusExt.IsAvailable()) {
        return pPlatform->m_GdiplusExt.LoadDIBitmap(args);
    } else if (args.flags == WINDIB_OPEN_MEMORY) {
        return NULL;
    }
    HBITMAP hBitmap = (HBITMAP)LoadImageW(NULL, (wchar_t*)args.path_name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap == NULL) {
        return NULL;
    }
    HDC hDC = CreateCompatibleDC(NULL);
    int width, height;
    GetBitmapSize(hBitmap, width, height);
    CFX_DIBitmap* pDIBitmap = new CFX_DIBitmap;
    if (!pDIBitmap->Create(width, height, FXDIB_Rgb)) {
        delete pDIBitmap;
        DeleteDC(hDC);
        return NULL;
    }
    CFX_ByteString info = GetBitmapInfo(pDIBitmap);
    int ret = GetDIBits(hDC, hBitmap, 0, height, pDIBitmap->GetBuffer(), (BITMAPINFO*)info.c_str(), DIB_RGB_COLORS);
    if (!ret) {
        delete pDIBitmap;
        pDIBitmap = NULL;
    }
    DeleteDC(hDC);
    return pDIBitmap;
}