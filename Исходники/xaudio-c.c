xaudio2_t *xaudio2_new(unsigned samplerate, unsigned channels,
    size_t size, unsigned device)
{
   xaudio2_t *handle = (xaudio2_t*)calloc(1, sizeof(*handle));
   if (!handle)
      return NULL;

   handle->lpVtbl = &voice_vtable;
   CoInitializeEx(0, COINIT_MULTITHREADED);
   WAVEFORMATEX wfx = {0};

   if (FAILED(XAudio2Create(&handle->pXAudio2)))
      goto error;

   if (FAILED(IXAudio2_CreateMasteringVoice(handle->pXAudio2,
               &handle->pMasterVoice, channels, samplerate, 0, device, NULL)))
      goto error;

   wfx.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
   wfx.nChannels = channels;
   wfx.nSamplesPerSec = samplerate;
   wfx.nBlockAlign = channels * sizeof(float);
   wfx.wBitsPerSample = sizeof(float) * 8;
   wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
   wfx.cbSize = 0;

   if (FAILED(IXAudio2_CreateSourceVoice(handle->pXAudio2,
               &handle->pSourceVoice, &wfx,
               XAUDIO2_VOICE_NOSRC, XAUDIO2_DEFAULT_FREQ_RATIO,
               (IXAudio2VoiceCallback*)handle, 0, 0)))
      goto error;

   handle->hEvent = CreateEvent(0, FALSE, FALSE, 0);
   if (!handle->hEvent)
      goto error;

   handle->bufsize = size / MAX_BUFFERS;
   handle->buf = (uint8_t*)calloc(1, handle->bufsize * MAX_BUFFERS);
   if (!handle->buf)
      goto error;

   if (FAILED(IXAudio2SourceVoice_Start(handle->pSourceVoice, 0, XAUDIO2_COMMIT_NOW)))
      goto error;

   return handle;

error:
   xaudio2_free(handle);
   return NULL;
}