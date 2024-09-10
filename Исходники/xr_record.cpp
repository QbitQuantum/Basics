void RecordStart()
{
 WAVEFORMATEX pcmwf;

 // setup header in the same format as our directsound stream
 memset(&pcmwf,0,sizeof(WAVEFORMATEX));
 pcmwf.wFormatTag      = WAVE_FORMAT_PCM;

 if(iDisStereo)
  {
   pcmwf.nChannels       = 1;
   pcmwf.nBlockAlign     = 2;
  }
 else
  {
   pcmwf.nChannels       = 2;
   pcmwf.nBlockAlign     = 4;
  }

 pcmwf.nSamplesPerSec  = 44100;
 pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
 pcmwf.wBitsPerSample  = 16;

 // create file
 hWaveFile=mmioOpen(szFileName,NULL,MMIO_CREATE|MMIO_WRITE|MMIO_EXCLUSIVE | MMIO_ALLOCBUF);
 if(!hWaveFile) return;
 
 // setup WAVE, fmt and data chunks
 memset(&mmckMain,0,sizeof(MMCKINFO));
 mmckMain.fccType = mmioFOURCC('W','A','V','E');

 mmioCreateChunk(hWaveFile,&mmckMain,MMIO_CREATERIFF);

 memset(&mmckData,0,sizeof(MMCKINFO));
 mmckData.ckid    = mmioFOURCC('f','m','t',' ');
 mmckData.cksize  = sizeof(WAVEFORMATEX);

 mmioCreateChunk(hWaveFile,&mmckData,0);
 mmioWrite(hWaveFile,(char*)&pcmwf,sizeof(WAVEFORMATEX)); 
 mmioAscend(hWaveFile,&mmckData,0);

 mmckData.ckid = mmioFOURCC('d','a','t','a');
 mmioCreateChunk(hWaveFile,&mmckData,0);
}