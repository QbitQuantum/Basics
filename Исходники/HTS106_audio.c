/* HTS106_Audio_open: open audio device */
static void HTS106_Audio_open(HTS106_Audio * audio, int sampling_rate, int max_buff_size)
{
   MMRESULT error;

   if (audio->sampling_rate == sampling_rate && audio->max_buff_size == max_buff_size)
      return;

   HTS106_Audio_close(audio);

   audio->sampling_rate = sampling_rate;
   audio->max_buff_size = max_buff_size;

   if (audio->max_buff_size <= 0)
      return;

   /* queue */
   audio->which_buff = 1;
   audio->now_buff_1 = FALSE;
   audio->now_buff_2 = FALSE;
   audio->buff = (short *) HTS106_calloc(max_buff_size, sizeof(short));

   /* format */
   audio->waveformatex.wFormatTag = WAVE_FORMAT_PCM;
   audio->waveformatex.nChannels = AUDIO_CHANNEL;
   audio->waveformatex.nSamplesPerSec = sampling_rate;
   audio->waveformatex.wBitsPerSample = sizeof(short) * 8;
   audio->waveformatex.nBlockAlign = AUDIO_CHANNEL * audio->waveformatex.wBitsPerSample / 8;
   audio->waveformatex.nAvgBytesPerSec = sampling_rate * audio->waveformatex.nBlockAlign;
   /* open */
   error = waveOutOpen(&audio->hwaveout, WAVE_MAPPER, &audio->waveformatex, (DWORD) HTS106_Audio_callback_function, (DWORD) audio, CALLBACK_FUNCTION);
   if (error != MMSYSERR_NOERROR)
      HTS106_error(0, "hts_engine: Failed to open your output audio device to play waveform.\n");

   /* prepare */
   audio->buff_1.lpData = (LPSTR) HTS106_calloc(max_buff_size, sizeof(short));
   audio->buff_1.dwBufferLength = max_buff_size * sizeof(short);
   audio->buff_1.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
   audio->buff_1.dwLoops = 1;
   audio->buff_1.lpNext = 0;
   audio->buff_1.reserved = 0;
   error = waveOutPrepareHeader(audio->hwaveout, &(audio->buff_1), sizeof(WAVEHDR));
   if (error != MMSYSERR_NOERROR)
      HTS106_error(0, "hts_engine: Cannot initialize audio datablocks to play waveform.\n");
   audio->buff_2.lpData = (LPSTR) HTS106_calloc(max_buff_size, sizeof(short));
   audio->buff_2.dwBufferLength = max_buff_size * sizeof(short);
   audio->buff_2.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
   audio->buff_2.dwLoops = 1;
   audio->buff_2.lpNext = 0;
   audio->buff_2.reserved = 0;
   error = waveOutPrepareHeader(audio->hwaveout, &(audio->buff_2), sizeof(WAVEHDR));
   if (error != MMSYSERR_NOERROR)
      HTS106_error(0, "hts_engine: Cannot initialize audio datablocks to play waveform.\n");
}