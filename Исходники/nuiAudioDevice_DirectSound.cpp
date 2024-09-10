nuiAudioDevice_DirectSound::nuiAudioDevice_DirectSound()
: nuiAudioDevice()
{
  mInName = _T("Default Device");
  mOutName = _T("Default Device");

  mIsPresent = false;
  mHasInput = false;
  mHasOutput = false;

  mpDirectSound = NULL;
  mpDirectSoundCapture = NULL;

  mAPIName = API_NAME;

  mpRingBuffer = NULL;
  mpInputBuffer = NULL;
  mpOutputBuffer = NULL;

  mpProcessingTh = NULL;
  mpOutputTh = NULL;

  mNotifInputEvent[0] = NULL;
  mNotifInputEvent[1] = NULL;
  mNotifOutputEvent[0] = NULL;
  mNotifOutputEvent[1] = NULL;

  HRESULT hr;
  // Get Input device caps:
  hr = DirectSoundCaptureCreate(NULL, &mpDirectSoundCapture, NULL);
  if (hr != S_OK || !mpDirectSoundCapture)
  {
    NGL_LOG(_T("nuiAudioDevice_DirectSound"), NGL_LOG_INFO, _T("constructor ERROR : could not create DirectSoundCapture object!\n"));
  }

  // Get Output device caps:
  hr = DirectSoundCreate(NULL, &mpDirectSound, NULL);
  if (hr != S_OK || !mpDirectSound)
  {
    NGL_LOG(_T("nuiAudioDevice_DirectSound"), NGL_LOG_ERROR, _T("constructor ERROR : could not create DirectSound object!\n"));// if there is no output, consider the device as not valid
    return;
  }

  Init();
}