void initAudioDevices(SIPX_INSTANCE_DATA& pInst)
{
#if defined(_WIN32)
   WAVEOUTCAPS outcaps;
   WAVEINCAPS  incaps;
   int numDevices;
   MMRESULT result;

   numDevices = waveInGetNumDevs();
   for (int i = 0; i < numDevices && i < MAX_AUDIO_DEVICES; i++)
   {
      result = waveInGetDevCaps(i, &incaps, sizeof(WAVEINCAPS));
      assert(result == MMSYSERR_NOERROR);
      pInst.inputAudioDevices[i] = SAFE_STRDUP(incaps.szPname);
   }
   pInst.nInputAudioDevices = numDevices;

   numDevices = waveOutGetNumDevs();
   for (int i = 0; i < numDevices && i < MAX_AUDIO_DEVICES; i++)
   {
      result = waveOutGetDevCaps(i, &outcaps, sizeof(WAVEOUTCAPS));
      assert(result == MMSYSERR_NOERROR);
      pInst.outputAudioDevices[i] = SAFE_STRDUP(outcaps.szPname) ;
   }
   pInst.nOutputAudioDevices = numDevices;

#else
   pInst.inputAudioDevices[0] = SAFE_STRDUP("Default");
   pInst.outputAudioDevices[0] = SAFE_STRDUP("Default");
#endif
}