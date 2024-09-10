HRESULT ScreenshotCapture::GetBase64Data(std::wstring& data)
{
  if (m_pImage == NULL) {
    // CImage was not initialized.
    return E_POINTER;
  }
  CComPtr<IStream> stream;
  HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &stream);
  if (FAILED(hr)) {
    LOG(WARN) << "Error creating IStream" << hr;
    return hr;
  }
  hr = m_pImage->Save(stream, Gdiplus::ImageFormatPNG);
  if (FAILED(hr)) {
    LOG(WARN) << "Saving image failed" << hr;
    return hr;
  }
  // Get the size of the stream.
  STATSTG statstg;
  hr = stream->Stat(&statstg, STATFLAG_DEFAULT);
  if (FAILED(hr)) {
    LOG(WARN) << "No stat on stream" << hr;
    return hr;
  }
  HGLOBAL hGlobal = NULL;
  hr = ::GetHGlobalFromStream(stream, &hGlobal);
  if (FAILED(hr)) {
    LOG(WARN) << "No HGlobal in stream" << hr;
    return hr;
  }
  // TODO: What if the file is bigger than max_int?
  LOG(INFO) << "Size of stream: " << statstg.cbSize.QuadPart;
  int length = Base64EncodeGetRequiredLength(
      statstg.cbSize.QuadPart,
      ATL_BASE64_FLAG_NOCRLF);
  if (length <= 0) {
    LOG(WARN) << "Got zero or negative length from base64 required length";
    return E_FAIL;
  }
  char *array = new char[length + 1];
  if (!::Base64Encode(
        reinterpret_cast<BYTE*>(::GlobalLock(hGlobal)),
        statstg.cbSize.QuadPart,
        array,
        &length,
        ATL_BASE64_FLAG_NOCRLF)) {
    delete array;
    ::GlobalUnlock(hGlobal);
    LOG(WARN) << "Failure encoding to base64";
    return E_FAIL;
  }
  array[length] = '\0';
  data = CA2W(array);

  delete array;
  ::GlobalUnlock(hGlobal);

  return S_OK;
}