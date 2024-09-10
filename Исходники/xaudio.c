static xaudio2_t *xaudio2_new(unsigned samplerate, unsigned channels,
      size_t size, unsigned device)
{
   xaudio2_t *handle = NULL;
   WAVEFORMATEX wfx  = {0};

#if defined(__cplusplus) && !defined(CINTERFACE)
   handle = new xaudio2;
#else
   handle = (xaudio2_t*)calloc(1, sizeof(*handle));
#endif

   if (!handle)
      goto error;

#if !defined(__cplusplus) || defined(CINTERFACE)
   handle->lpVtbl = &voice_vtable;
#endif

   if (FAILED(XAudio2Create(&handle->pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
      goto error;

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
   if (FAILED(IXAudio2_CreateMasteringVoice(handle->pXAudio2, &handle->pMasterVoice, channels, samplerate, 0, (LPCWSTR)(uintptr_t)device, NULL, AudioCategory_GameEffects)))
      goto error;
#else
   if (FAILED(IXAudio2_CreateMasteringVoice(handle->pXAudio2, &handle->pMasterVoice, channels, samplerate, 0, device, NULL)))
      goto error;
#endif

   xaudio2_set_wavefmt(&wfx, channels, samplerate);

   if (FAILED(IXAudio2_CreateSourceVoice(handle->pXAudio2,
               &handle->pSourceVoice, &wfx,
               XAUDIO2_VOICE_NOSRC, XAUDIO2_DEFAULT_FREQ_RATIO,
               (IXAudio2VoiceCallback*)handle, 0, 0)))
      goto error;

   handle->hEvent  = CreateEvent(0, FALSE, FALSE, 0);
   if (!handle->hEvent)
      goto error;

   handle->bufsize = size / MAX_BUFFERS;
   handle->buf     = (uint8_t*)calloc(1, handle->bufsize * MAX_BUFFERS);
   if (!handle->buf)
      goto error;

   if (FAILED(IXAudio2SourceVoice_Start(handle->pSourceVoice, 0,
               XAUDIO2_COMMIT_NOW)))
      goto error;

   return handle;

error:
   xaudio2_free(handle);
   return NULL;
}