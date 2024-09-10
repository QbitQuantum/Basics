void CImgBitsDIB::SetTransIndex(LONG lIndex)
{
    Assert(_iBitCount <= 8);
    Assert(lIndex>=-1 && lIndex<(1<<_iBitCount));

    _iTrans = lIndex;

    if(lIndex >= 0)
    {
        if(_hbmImg)
        {
            HDC hdcMem;
            HBITMAP hbmSav;

            hdcMem = GetMemoryDC();
            if(!hdcMem)
            {
                return;
            }

            hbmSav = (HBITMAP)SelectObject(hdcMem, _hbmImg);
            SetDIBColorTable(hdcMem, lIndex, 1, &g_rgbWhite);
            SelectObject(hdcMem, hbmSav);
            ReleaseMemoryDC(hdcMem);
        }
        else if(_pbmih)
        {
            ((RGBQUAD*)(_pbmih+1))[_iTrans] = g_rgbWhite;
        }
    }
}