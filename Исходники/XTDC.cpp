/**
 *\fn           HDC AddImageDC(int id, int resId)
 *\brief        Ìí¼ÓJPGÍ¼ÏñDC
 *\param[in]    int id Í¼ÏñDCÐòºÅ
 *\param[in]    int resId ×ÊÔ´ID
 *\return       JPGÍ¼ÏñDC¾ä±ú
 */
HDC CXTDC::AddImageDC(int id, int resId)
{
    DeleteDC(IMAGEDC, id);

    HRSRC   res     = FindResource(module_, MAKEINTRESOURCE(resId), _T("jpg"));
    HGLOBAL resData = LoadResource(module_, (HRSRC)res);
    DWORD   resSize = SizeofResource(module_, (HRSRC)res);

    if (NULL == resData)
    {
        return NULL;
    }

    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, resSize);
    if (NULL == hGlobal)
    {
        return NULL;
    }

    LPVOID pvData = GlobalLock(hGlobal);// Ëø¶¨ÄÚ´æ
    if (NULL == pvData)
    {
        FreeResource(resData);
        GlobalFree(hGlobal);
        return NULL;
    }

    LockResource(resData);              // Ëø¶¨×ÊÔ´
    memcpy(pvData, resData, resSize);   // ÔØÈëÄÚ´æ
    GlobalUnlock(hGlobal);              // ½âËøÄÚ´æ
    FreeResource(resData);              // ÊÍ·Å×ÊÔ´

    CComPtr<IStream> spStream = NULL;
    HRESULT hr = ::CreateStreamOnHGlobal(hGlobal, TRUE, &spStream); // ½¨Á¢IStream
    if (!SUCCEEDED(hr))
    {
        GlobalFree(hGlobal);
        return NULL;
    }

    CComPtr<IPicture> spPicture;
    hr = OleLoadPicture(spStream, resSize, FALSE, IID_IPicture, (LPVOID*)&spPicture);   // ½¨Á¢IPicture
    if (!SUCCEEDED(hr))
    {
        GlobalFree(hGlobal);
        return NULL;
    }

    GlobalFree(hGlobal);

    OLE_HANDLE picHandle = NULL;
    spPicture->get_Handle(&picHandle);

    XTDC xtDC;
    xtDC.dc = CreateCompatibleDC(NULL);
    xtDC.image = (HGDIOBJ)picHandle;
    xtDC.oldImage = SelectObject(xtDC.dc, xtDC.image);

    imageDcMap_[id] = xtDC;

    return xtDC.dc;
}