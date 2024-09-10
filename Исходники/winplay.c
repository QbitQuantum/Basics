int win32_audio_play(short *buffer, int buffer_len)
{
   int i, current_to_play, remained_to_play;
   short *des, *src;

   remained_to_play = buffer_len;

   while (remained_to_play > 0) {
      while (ri == ((wi + 1) % WO_MAX_BUCKETS))
         Sleep(100);            /* wait until there are available buckets */

      if (WHDR_DONE == (wOutHdr[wi].dwFlags & WHDR_DONE))
         waveOutUnprepareHeader(wOutDev, &wOutHdr[wi], sizeof(WAVEHDR));

      current_to_play =
          (remained_to_play >
           WO_BUCKET_SIZE) ? WO_BUCKET_SIZE : remained_to_play;
      if (0 < current_to_play) {
         des = (short *) wOutHdr[wi].lpData;
         src = (short *) &(buffer[buffer_len - remained_to_play]);
         for (i = 0; i < current_to_play; i++)
            des[i] = src[i];
         wOutHdr[wi].dwBufferLength = current_to_play * sizeof(short);

         waveOutPrepareHeader(wOutDev, &wOutHdr[wi], sizeof(WAVEHDR));
         waveOutWrite(wOutDev, &wOutHdr[wi], sizeof(WAVEHDR));

         remained_to_play -= current_to_play;
         wi = (wi + 1) % WO_MAX_BUCKETS;
      }
   }

   return (WIN32AUDIO_NO_ERROR);
}