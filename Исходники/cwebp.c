static HRESULT OpenInputStream(const char* filename, IStream** ppStream) {
  HRESULT hr = S_OK;
  IFS(SHCreateStreamOnFileA(filename, STGM_READ, ppStream));
  if (FAILED(hr))
    printf("Error opening input file %s (%08x)\n", filename, hr);
  return hr;
}