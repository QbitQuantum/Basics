char testNoCallback(float seconds, float frequency)
{
  MMRESULT result;

  HWAVEOUT waveOut;
  result = waveOutOpen(&waveOut,
		       WAVE_MAPPER,
		       &waveFormat,
		       0,
		       0,
		       CALLBACK_NULL);
  if(result != MMSYSERR_NOERROR) {
    printf("waveOutOpen failed (result=%d)\n", result);
    return 1;
  }

  printf("Opened Wave Mapper!\n");
  fflush(stdout);
  
  DWORD sampleCount = seconds * waveFormat.nSamplesPerSec;
  LPSTR block = allocateBlock(sampleCount);
  fillSinWave(block, frequency, sampleCount);
  
  printf("Writing block...\n");
  fflush(stdout);
  writeAudioBlock(waveOut, block, sampleCount * waveFormat.nBlockAlign);

  waveOutClose(waveOut);

  return 0;
}