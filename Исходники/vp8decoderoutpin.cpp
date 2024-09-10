void Outpin::AddVIH(
    CMediaTypes& mtv,
    const GUID& subtype,
    REFERENCE_TIME AvgTimePerFrame,
    LONG width,
    LONG height,
    DWORD dwBitCount,
    DWORD dwSizeImage)
{
    AM_MEDIA_TYPE mt;

    VIDEOINFOHEADER vih;
    BITMAPINFOHEADER& bmih = vih.bmiHeader;

    mt.majortype = MEDIATYPE_Video;
    mt.subtype = subtype;
    mt.bFixedSizeSamples = TRUE;
    mt.bTemporalCompression = FALSE;
    mt.lSampleSize = 0;
    mt.formattype = FORMAT_VideoInfo;
    mt.pUnk = 0;
    mt.cbFormat = sizeof vih;
    mt.pbFormat = (BYTE*)&vih;

    SetRectEmpty(&vih.rcSource);
    SetRectEmpty(&vih.rcTarget);
    vih.dwBitRate = 0;
    vih.dwBitErrorRate = 0;
    vih.AvgTimePerFrame = AvgTimePerFrame;

    bmih.biSize = sizeof bmih;
    bmih.biWidth = width;
    bmih.biHeight = height;
    bmih.biPlanes = 1;  //because Microsoft says so
    bmih.biBitCount = static_cast<WORD>(dwBitCount);
    bmih.biCompression = subtype.Data1;
    bmih.biSizeImage = dwSizeImage;
    bmih.biXPelsPerMeter = 0;
    bmih.biYPelsPerMeter = 0;
    bmih.biClrUsed = 0;
    bmih.biClrImportant = 0;

    mtv.Add(mt);
}