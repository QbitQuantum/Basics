static int _dsound_open_recorder(ALLEGRO_AUDIO_RECORDER *r)
{
   HRESULT hr;

   if (capture_device != NULL) {
      /* FIXME: It's wrong to assume only a single recording device, but since
                there is no enumeration of devices, it doesn't matter for now. */
      ALLEGRO_ERROR("Already recording.\n");
      return 1;
   }

   ALLEGRO_INFO("Creating default capture device.\n");

   /* FIXME: Use default device until we have device enumeration */
   hr = DirectSoundCaptureCreate8(NULL, &capture_device, NULL);
   if (FAILED(hr)) {
      ALLEGRO_ERROR("DirectSoundCaptureCreate8 failed: %s\n", ds_get_error(hr));
      return 1;
   }
   
   hr = device->SetCooperativeLevel(get_window(), DSSCL_PRIORITY);
   if (FAILED(hr)) {
      ALLEGRO_ERROR("SetCooperativeLevel failed: %s\n", ds_get_error(hr));
      return 1;
   }

   DSOUND_RECORD_DATA *extra = (DSOUND_RECORD_DATA *) al_calloc(1, sizeof(*extra));

   DSCCAPS dsccaps;   
   dsccaps.dwSize = sizeof(DSCCAPS);
   hr = capture_device->GetCaps(&dsccaps);
   if (FAILED(hr)) {
      ALLEGRO_ERROR("DirectSoundCaptureCreate8::GetCaps failed: %s\n", ds_get_error(hr));
   }
   else {
      ALLEGRO_INFO("caps: %lu %lu\n", dsccaps.dwFormats, dsccaps.dwFormats & WAVE_FORMAT_2M16);
   }

   memset(&extra->wave_fmt, 0, sizeof(extra->wave_fmt));
   extra->wave_fmt.wFormatTag = WAVE_FORMAT_PCM;
   extra->wave_fmt.nChannels = (WORD)al_get_channel_count(r->chan_conf);
   extra->wave_fmt.nSamplesPerSec = r->frequency;
   extra->wave_fmt.wBitsPerSample = (WORD)al_get_audio_depth_size(r->depth) * 8;
   extra->wave_fmt.nBlockAlign = extra->wave_fmt.nChannels * extra->wave_fmt.wBitsPerSample / 8;
   extra->wave_fmt.nAvgBytesPerSec = extra->wave_fmt.nSamplesPerSec * extra->wave_fmt.nBlockAlign;
   
   memset(&extra->desc, 0, sizeof(extra->desc));
   extra->desc.dwSize = sizeof(extra->desc);
   extra->desc.lpwfxFormat = &extra->wave_fmt;
   extra->desc.dwBufferBytes = extra->wave_fmt.nAvgBytesPerSec * 5;

   hr = capture_device->CreateCaptureBuffer(&extra->desc, &extra->buffer, NULL);
   if (FAILED(hr)) {
      al_free(extra);
      ALLEGRO_ERROR("Unable to create Capture Buffer\n");
      return 1;
   }

   extra->buffer->QueryInterface(_al_IID_IDirectSoundCaptureBuffer8, (void **) &extra->buffer8);
   
   r->extra = extra;
   r->thread = al_create_thread(_dsound_update_recorder, r);

   return 0;
}