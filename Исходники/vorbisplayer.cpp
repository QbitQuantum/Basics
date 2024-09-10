  sBool Init(sInt rate, sInt channels)
  {
#ifndef KSDATAFORMAT_SUBTYPE_PCM
		const static GUID KSDATAFORMAT_SUBTYPE_PCM = {0x00000001,0x0000,0x0010,{0x80,0x00,0x00,0xaa,0x00,0x38,0x9b,0x71}};
#endif

    if FAILED(DirectSoundCreate8(0,&DS,0))
      return sFALSE;

    if FAILED(DS->SetCooperativeLevel(sHWND,DSSCL_PRIORITY))
      return sFALSE;

    // this is our output format.
    WAVEFORMATPCMEX wf;
    wf.Format.cbSize=22;
    wf.Format.wFormatTag=WAVE_FORMAT_EXTENSIBLE;
    wf.Format.nChannels=channels;
    wf.Format.wBitsPerSample=16;
    wf.Format.nSamplesPerSec=rate;
    wf.Format.nBlockAlign=channels*((wf.Format.wBitsPerSample+7)/8);
    wf.Format.nAvgBytesPerSec=wf.Format.nBlockAlign*rate;
    wf.dwChannelMask=(1<<channels)-1; // very space opera
    wf.Samples.wValidBitsPerSample=16;
    wf.SubFormat=KSDATAFORMAT_SUBTYPE_PCM;

    // set up some stuff while we're at it
    BufferSize = sAlign(rate*LATENCY_MS/1000,16);
    BytesPerSample= wf.Format.nBlockAlign;
    RenderBuffer = new sF32[channels*BufferSize];
    LastPlayPos=0;
    Channels=channels;
    Rate=rate;

    // create primary buffer...
    DSBUFFERDESC dsbd;
    sSetMem(&dsbd,0,sizeof(dsbd));
    dsbd.dwSize = sizeof(dsbd);
    dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
    dsbd.dwBufferBytes = 0;
    dsbd.lpwfxFormat = 0;
    if FAILED(DS->CreateSoundBuffer(&dsbd,&PrimBuffer,0))
      return sFALSE;

    // set primary buffer format to prepare DirectSound for what's coming (may fail)
    PrimBuffer->SetFormat((WAVEFORMATEX*)&wf);

    // create secondary buffer
    sSetMem(&dsbd,0,sizeof(dsbd));
    dsbd.dwSize = sizeof(dsbd);
    dsbd.dwFlags = DSBCAPS_GLOBALFOCUS|DSBCAPS_STICKYFOCUS|DSBCAPS_GETCURRENTPOSITION2;
    dsbd.dwBufferBytes = BufferSize*BytesPerSample;
    dsbd.lpwfxFormat = (WAVEFORMATEX*)&wf;
    if FAILED(DS->CreateSoundBuffer(&dsbd,&Buffer,0))
      return sFALSE;

    // now that everything seemed to work, let's switch over to the rendering thread
    Renderers.HintSize(8);
    Thread = new sThread(ThreadProxy,1,0,this);
    return sTRUE;
  }