void MMS_Audio_Init()
{
  MMRESULT	status;
  LPWAVEOUTCAPS	lpCaps;


  if( waveOutGetNumDevs() < 1 ) 
  {
    fprintf(stderr,"Audio disabled - No Multimedia Services compatible audio devices available\n");
    return;
  }

  /* Figure out device capabilities  - Just use device 0 for now */

  if((lpCaps = (LPWAVEOUTCAPS)mmeAllocMem(sizeof(WAVEOUTCAPS))) == NULL ) {
      fprintf(stderr,"Failed to allocate WAVEOUTCAPS struct\n");
      return;
  }
  status = waveOutGetDevCaps( 0, lpCaps, sizeof(WAVEOUTCAPS));
  if( status != MMSYSERR_NOERROR ) {
      fprintf(stderr,"waveOutGetDevCaps failed - status = %d\n", status);
  }

  mmeFreeMem(lpCaps);

}