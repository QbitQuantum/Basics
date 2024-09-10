static HRESULT WriteUsingWIC(const char* out_file_name, int use_stdout,
                             REFGUID container_guid,
                             uint8_t* rgb, int stride,
                             uint32_t width, uint32_t height, int has_alpha) {
  HRESULT hr = S_OK;
  IWICImagingFactory* factory = NULL;
  IWICBitmapFrameEncode* frame = NULL;
  IWICBitmapEncoder* encoder = NULL;
  IStream* stream = NULL;
  WICPixelFormatGUID pixel_format = has_alpha ? GUID_WICPixelFormat32bppBGRA
                                              : GUID_WICPixelFormat24bppBGR;

  if (out_file_name == NULL || rgb == NULL) return E_INVALIDARG;

  IFS(CoInitialize(NULL));
  IFS(CoCreateInstance(MAKE_REFGUID(CLSID_WICImagingFactory), NULL,
                       CLSCTX_INPROC_SERVER,
                       MAKE_REFGUID(IID_IWICImagingFactory),
                       (LPVOID*)&factory));
  if (hr == REGDB_E_CLASSNOTREG) {
    fprintf(stderr,
            "Couldn't access Windows Imaging Component (are you running "
            "Windows XP SP3 or newer?). PNG support not available. "
            "Use -ppm or -pgm for available PPM and PGM formats.\n");
  }
  IFS(CreateOutputStream(out_file_name, use_stdout, &stream));
  IFS(IWICImagingFactory_CreateEncoder(factory, container_guid, NULL,
                                       &encoder));
  IFS(IWICBitmapEncoder_Initialize(encoder, stream,
                                   WICBitmapEncoderNoCache));
  IFS(IWICBitmapEncoder_CreateNewFrame(encoder, &frame, NULL));
  IFS(IWICBitmapFrameEncode_Initialize(frame, NULL));
  IFS(IWICBitmapFrameEncode_SetSize(frame, width, height));
  IFS(IWICBitmapFrameEncode_SetPixelFormat(frame, &pixel_format));
  IFS(IWICBitmapFrameEncode_WritePixels(frame, height, stride,
                                        height * stride, rgb));
  IFS(IWICBitmapFrameEncode_Commit(frame));
  IFS(IWICBitmapEncoder_Commit(encoder));

  if (SUCCEEDED(hr) && use_stdout) {
    HGLOBAL image;
    IFS(GetHGlobalFromStream(stream, &image));
    if (SUCCEEDED(hr)) {
      HANDLE std_output = GetStdHandle(STD_OUTPUT_HANDLE);
      DWORD mode;
      const BOOL update_mode = GetConsoleMode(std_output, &mode);
      const void* const image_mem = GlobalLock(image);
      DWORD bytes_written = 0;

      // Clear output processing if necessary, then output the image.
      if (update_mode) SetConsoleMode(std_output, 0);
      if (!WriteFile(std_output, image_mem, (DWORD)GlobalSize(image),
                     &bytes_written, NULL) ||
          bytes_written != GlobalSize(image)) {
        hr = E_FAIL;
      }
      if (update_mode) SetConsoleMode(std_output, mode);
      GlobalUnlock(image);
    }
  }

  if (frame != NULL) IUnknown_Release(frame);
  if (encoder != NULL) IUnknown_Release(encoder);
  if (factory != NULL) IUnknown_Release(factory);
  if (stream != NULL) IUnknown_Release(stream);
  return hr;
}