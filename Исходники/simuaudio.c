int RecData(int i)
{
  WORD wResult;

  SendInBuffers--;
  if (!StopRecord)
  {
    InFillBuffer(i);
    wResult = waveInAddBuffer(hWaveIn,WaveInBuf[i].lpWaveHdr,sizeof(WAVEHDR));
    if (wResult != 0)
    {
      WaveInFreeAll();
      return 0;
    }
    SendInBuffers++;
  }
  else
  {
    if (!SendInBuffers)
    {
      WaveInFreeAll();
      StopRecord=FALSE;
	  waveInClose(hWaveIn);
    }
  }
  return 1;
}