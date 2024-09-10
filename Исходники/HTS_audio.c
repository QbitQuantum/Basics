/* HTS_Audio_close: close audio device */
static void HTS_Audio_close(HTS_Audio * audio)
{
   MMRESULT error;

   if (audio->max_buff_size <= 0)
      return;

   /* stop audio */
   error = waveOutReset(audio->hwaveout);
   if (error != MMSYSERR_NOERROR)
      HTS_error(0, "hts_engine: Cannot stop and reset your output audio device.\n");
   /* unprepare */
   error = waveOutUnprepareHeader(audio->hwaveout, &(audio->buff_1), sizeof(WAVEHDR));
   if (error != MMSYSERR_NOERROR)
      HTS_error(0, "hts_engine: Cannot cleanup the audio datablocks to play waveform.\n");
   error = waveOutUnprepareHeader(audio->hwaveout, &(audio->buff_2), sizeof(WAVEHDR));
   if (error != MMSYSERR_NOERROR)
      HTS_error(0, "hts_engine: Cannot cleanup the audio datablocks to play waveform.\n");
   /* close */
   error = waveOutClose(audio->hwaveout);
   if (error != MMSYSERR_NOERROR)
      HTS_error(0, "hts_engine: Failed to close your output audio device.\n");
   HTS_free(audio->buff_1.lpData);
   HTS_free(audio->buff_2.lpData);
   HTS_free(audio->buff);
}