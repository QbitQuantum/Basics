HRESULT touchmind::util::BitmapHelper::CreateBitmapFromWICBitmapSource(IN IWICBitmapSource *pBitmapSource,
                                                                       OUT HBITMAP *pHBitmap) {
  HRESULT hr = S_OK;

  UINT width = 0;
  UINT height = 0;

  void *pvImageBits = nullptr;

  WICPixelFormatGUID pixelFormat = {0};
  hr = pBitmapSource->GetPixelFormat(&pixelFormat);

  if (SUCCEEDED(hr)) {
    hr = (pixelFormat == GUID_WICPixelFormat32bppPBGRA) ? S_OK : E_FAIL;
  }

  if (SUCCEEDED(hr)) {
    hr = pBitmapSource->GetSize(&width, &height);
  }

  if (SUCCEEDED(hr)) {
    BITMAPINFO bminfo;
    ZeroMemory(&bminfo, sizeof(bminfo));
    bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bminfo.bmiHeader.biWidth = width;
    bminfo.bmiHeader.biHeight = -(LONG)height;
    bminfo.bmiHeader.biPlanes = 1;
    bminfo.bmiHeader.biBitCount = 32;
    bminfo.bmiHeader.biCompression = BI_RGB;

    HDC hdcScreen = GetDC(nullptr);

    hr = hdcScreen ? S_OK : E_FAIL;

    if (SUCCEEDED(hr)) {
      if (pHBitmap) {
        DeleteObject(pHBitmap);
      }

      *pHBitmap = CreateDIBSection(hdcScreen, &bminfo, DIB_RGB_COLORS, &pvImageBits, nullptr, 0);
      ReleaseDC(nullptr, hdcScreen);

      hr = *pHBitmap ? S_OK : E_FAIL;
    }
  }

  UINT cbStride = 0;
  if (SUCCEEDED(hr)) {
    hr = UIntMult(width, sizeof(ARGB), &cbStride);
  }

  UINT cbImage = 0;
  if (SUCCEEDED(hr)) {
    hr = UIntMult(cbStride, height, &cbImage);
  }

  if (SUCCEEDED(hr)) {
    hr = pBitmapSource->CopyPixels(nullptr, cbStride, cbImage, reinterpret_cast<BYTE *>(pvImageBits));
  }

  if (FAILED(hr)) {
    DeleteObject(*pHBitmap);
    *pHBitmap = nullptr;
  }

  return hr;
}