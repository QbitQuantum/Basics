static HRESULT CreateOutputStream(const char* out_file_name,
                                  int write_to_mem, IStream** stream) {
  HRESULT hr = S_OK;
  if (write_to_mem) {
    // Output to a memory buffer. This is freed when 'stream' is released.
    IFS(CreateStreamOnHGlobal(NULL, TRUE, stream));
  } else {
    IFS(SHCreateStreamOnFileA(out_file_name, STGM_WRITE | STGM_CREATE, stream));
  }
  if (FAILED(hr)) {
    fprintf(stderr, "Error opening output file %s (%08lx)\n",
            out_file_name, hr);
  }
  return hr;
}