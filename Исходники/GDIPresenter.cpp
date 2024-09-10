HRESULT GDIPresenter::Initialize(UINT uWidth, UINT uHeight)
{
    HRESULT hr;

    _hMemoryDC = ::CreateCompatibleDC(NULL);

    BITMAPINFO info = { 0 };
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biHeight = uWidth;
    info.bmiHeader.biWidth = uHeight;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    _hBitmap = ::CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &_pvBits, NULL, 0);

    ::SelectObject(_hMemoryDC, _hBitmap);

    CComObject<GDIPresenterBuffer> *pBuffer = NULL;
    IFR( CComObject<GDIPresenterBuffer>::CreateInstance(&pBuffer) );
    pBuffer->Initialize(CSize(uWidth, uHeight), _pvBits);
    IFR( pBuffer->QueryInterface(&_spBuffer) );

    return hr;
}