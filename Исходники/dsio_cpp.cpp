sU32 __stdcall dsInit(DSIOCALLBACK *callback, void *parm, void *hwnd)
{
  static const WAVEFORMATEX wfxprimary = { WAVE_FORMAT_PCM, 2, 44100, 44100*2*2, 2*2, 16, 0 };
  //static const WAVEFORMATEX wfxprimary = { WAVE_FORMAT_PCM, 2, 48000, 48000*2*2, 2*2, 16, 0 };
  static const DSBUFFERDESC primdesc = { sizeof(DSBUFFERDESC), DSBCAPS_PRIMARYBUFFER, 0, 0, 0 };
  static const DSBUFFERDESC streamdesc = { sizeof(DSBUFFERDESC), DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS, BUFFERLEN, 0, (WAVEFORMATEX*)&wfxprimary };

  ZeroMemory(&g_dsound, sizeof(g_dsound));
  g_dsound.callback = callback;
  g_dsound.cbparm = parm;

  void *buf1, *buf2;
  DWORD len1, len2;

  if (DirectSoundCreate(0, &g_dsound.dssd, 0) != S_OK || // create DSound instance
    g_dsound.dssd->SetCooperativeLevel((HWND)hwnd, DSSCL_PRIORITY) != S_OK || // cooperative level
    g_dsound.dssd->CreateSoundBuffer(&primdesc, &g_dsound.pbuf, 0) != S_OK || // primary buffer
    g_dsound.dssd->CreateSoundBuffer(&streamdesc, &g_dsound.sbuf, 0) != S_OK || // secondary buffer
    g_dsound.pbuf->SetFormat(&wfxprimary) != S_OK || // set primary buf format
    g_dsound.sbuf->Lock(0, 0, &buf1, &len1, &buf2, &len2, DSBLOCK_ENTIREBUFFER) != S_OK) // lock secondary buf
    goto bad;

  // clear secondary buffer
  memset(buf1, 0, len1);
  memset(buf2, 0, len2);
  if (g_dsound.sbuf->Unlock(buf1, len1, buf2, len2) != S_OK)
    goto bad;

  g_dsound.bufcnt = -BUFFERLEN;
  g_dsound.ltg = -BUFFERLEN;

  g_dsound.tickev = CreateEvent(0, FALSE, FALSE, 0);
  g_dsound.exitev = CreateEvent(0, FALSE, FALSE, 0);
  InitializeCriticalSection(&g_dsound.crsec);

  if (g_dsound.sbuf->Play(0, 0, DSBPLAY_LOOPING) != S_OK)
    goto bad;

  dsSetVolume(1.0f);

  // start sound thread
  g_dsound.thndl = CreateThread(0, 0, threadfunc, 0, 0, &len1);
  SetThreadPriority(g_dsound.thndl, THREAD_PRIORITY_ABOVE_NORMAL);

  return 0;

bad:
  dsClose();
  return ~0u;
}