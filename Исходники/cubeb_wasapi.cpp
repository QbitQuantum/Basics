int wasapi_init(cubeb ** context, char const * context_name)
{
  HRESULT hr;
  IMMDeviceEnumerator * enumerator = NULL;

  hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
  if (FAILED(hr)) {
    LOG("Could not init COM.");
    return CUBEB_ERROR;
  }

  cubeb * ctx = (cubeb *)calloc(1, sizeof(cubeb));

  ctx->ops = &wasapi_ops;

  hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
                        NULL, CLSCTX_INPROC_SERVER,
                        IID_PPV_ARGS(&enumerator));
  if (FAILED(hr)) {
    LOG("Could not get device enumerator.");
    wasapi_destroy(ctx);
    return CUBEB_ERROR;
  }

  /* eMultimedia is okay for now ("Music, movies, narration, [...]").
   * We will need to change this when we distinguish streams by use-case, other
   * possible values being eConsole ("Games, system notification sounds [...]")
   * and eCommunication ("Voice communication"). */
  hr = enumerator->GetDefaultAudioEndpoint(eRender,
                                           eMultimedia,
                                           &ctx->device);
  if (FAILED(hr)) {
    LOG("Could not get default audio endpoint.");
    SafeRelease(enumerator);
    wasapi_destroy(ctx);
    return CUBEB_ERROR;
  }

  ctx->mmcss_module = LoadLibraryA("Avrt.dll");

  if (ctx->mmcss_module) {
    ctx->set_mm_thread_characteristics =
      (set_mm_thread_characteristics_function) GetProcAddress(
          ctx->mmcss_module, "AvSetMmThreadCharacteristicsA");
    ctx->revert_mm_thread_characteristics =
      (revert_mm_thread_characteristics_function) GetProcAddress(
          ctx->mmcss_module, "AvRevertMmThreadCharacteristics");
    if (!(ctx->set_mm_thread_characteristics && ctx->revert_mm_thread_characteristics)) {
      LOG("Could not load AvSetMmThreadCharacteristics or AvRevertMmThreadCharacteristics: %d", GetLastError());
      FreeLibrary(ctx->mmcss_module);
    }
  } else {
    // This is not a fatal error, but we might end up glitching when
    // the system is under high load.
    LOG("Could not load Avrt.dll");
    ctx->set_mm_thread_characteristics = &set_mm_thread_characteristics_noop;
    ctx->revert_mm_thread_characteristics = &revert_mm_thread_characteristics_noop;
  }
  
  SafeRelease(enumerator);

  *context = ctx;

  return CUBEB_OK;
}