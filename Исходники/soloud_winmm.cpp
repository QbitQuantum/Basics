 static void winMMThread(LPVOID aParam)
 {
     SoLoudWinMMData *data = static_cast<SoLoudWinMMData*>(aParam);
     while (WAIT_OBJECT_0 != WaitForSingleObject(data->audioProcessingDoneEvent, 0)) 
     {
         for (int i=0;i<BUFFER_COUNT;++i) 
         {
             if (0 != (data->header[i].dwFlags & WHDR_INQUEUE)) 
             {
                 continue;
             }
             data->soloud->mix(data->buffer, data->samples);
             short *tgtBuf = data->sampleBuffer[i];
             for (DWORD j=0;j<(data->header[i].dwBufferLength/sizeof(short));++j) 
             {
                 tgtBuf[j] = static_cast<short>(floor(data->buffer[j] 
                                                      * static_cast<float>(0x7fff)));
             }
             if (MMSYSERR_NOERROR != waveOutWrite(data->waveOut, &data->header[i], 
                                                  sizeof(WAVEHDR))) 
             {
                 return;
             }
         }
         WaitForSingleObject(data->bufferEndEvent, INFINITE);
     }
 }