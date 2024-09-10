HRESULT STDMETHODCALLTYPE DWriteFontFileStream::GetFileSize(UINT64* fileSize) {
  *fileSize = mData.Length();
  return S_OK;
}