static HRESULT OpenInputStream(const char* filename, IStream** stream) {
  HRESULT hr = S_OK;
  if (!strcmp(filename, "-")) {
    const uint8_t* data = NULL;
    size_t data_size = 0;
    const int ok = ImgIoUtilReadFile(filename, &data, &data_size);
    if (ok) {
      HGLOBAL image = GlobalAlloc(GMEM_MOVEABLE, data_size);
      if (image != NULL) {
        void* const image_mem = GlobalLock(image);
        if (image_mem != NULL) {
          memcpy(image_mem, data, data_size);
          GlobalUnlock(image);
          IFS(CreateStreamOnHGlobal(image, TRUE, stream));
        } else {
          hr = E_FAIL;
        }
      } else {
        hr = E_OUTOFMEMORY;
      }
      free((void*)data);
    } else {
      hr = E_FAIL;
    }
  } else {
    IFS(SHCreateStreamOnFileA(filename, STGM_READ, stream));
  }

  if (FAILED(hr)) {
    fprintf(stderr, "Error opening input file %s (%08lx)\n", filename, hr);
  }
  return hr;
}