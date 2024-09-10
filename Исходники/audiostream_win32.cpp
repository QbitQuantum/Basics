int audioStreamer_ds::Open(int iswrite, int srate, int nch, int bps, int sleep, int nbufs, int bufsize, GUID *device)
{
  // todo: use device
  m_sleep = sleep >= 0 ? sleep : 0;

  GUID zero={0,};
  if (!memcmp(device,&zero,sizeof(zero))) device=NULL;

  m_nch = nch;
  m_srate=srate;
  m_bps=bps;

  int fmt_align=(bps>>3)*nch;
  int fmt_mul=fmt_align*srate;
  WAVEFORMATEX wfx={
		WAVE_FORMAT_PCM,
		nch,
		srate,
		fmt_mul,
		fmt_align,
		bps,
		0
	};
  m_totalbufsize=nbufs*bufsize;

  if (iswrite)
  {
      DirectSoundCreate(device,&m_lpds,NULL);

      if (m_lpds)
      {
        HWND hWnd = GetForegroundWindow();
        if (hWnd == NULL) hWnd = GetDesktopWindow();
        m_lpds->SetCooperativeLevel(hWnd,DSSCL_PRIORITY);

        // create a secondary buffer for now
        DSBUFFERDESC ds={sizeof(ds),DSBCAPS_GETCURRENTPOSITION2|DSBCAPS_GLOBALFOCUS,m_totalbufsize,0,&wfx, };
        m_lpds->CreateSoundBuffer(&ds,&m_outbuf,NULL);
        
      }

  }
  else
  {
    DirectSoundCaptureCreate(device,&m_lpcap,NULL);
    if (m_lpcap)
    {
      DSCBUFFERDESC ds={sizeof(ds),0,m_totalbufsize,0,&wfx, };
      m_lpcap->CreateCaptureBuffer(&ds,&m_inbuf,NULL);
    }
  }

  m_bufsize=bufsize;


  return 0;
}