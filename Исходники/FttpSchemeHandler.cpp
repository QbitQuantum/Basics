HRESULT FttpSchemeHandler::WhenCreateByteStream(IMFAsyncResult*result) {
  auto hr = MFEndCreateFile(result, &http_stream);
  assert(!source_creator);
  if (SUCCEEDED(hr)) hr = BeginCreateMediaSource();

  if (FAILED(hr)) {
    caller_result->SetStatus(hr);
    hr = MFInvokeCallback(caller_result.Get());
  }
  return S_OK;
}