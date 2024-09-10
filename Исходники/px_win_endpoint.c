static PxVolume VolumeFunction(HMIXEROBJ hMixer, DWORD controlID, PxVolume volume)
{
   MIXERCONTROLDETAILS details;
   MMRESULT result;
   MIXERCONTROLDETAILS_UNSIGNED value;

   if (hMixer == NULL) {
      return -1.0;
   }
   
   memset(&value, 0, sizeof(MIXERCONTROLDETAILS_UNSIGNED));
   
   details.cbStruct = sizeof(MIXERCONTROLDETAILS);
   details.dwControlID = controlID;
   details.cChannels = 1; /* all channels */
   details.cMultipleItems = 0;
   details.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
   details.paDetails = &value;

   if (volume < 0.0) {
      result = mixerGetControlDetails(hMixer,
                                      &details,
                                      MIXER_GETCONTROLDETAILSF_VALUE);
      if (result != MMSYSERR_NOERROR)
         return -1.0;
      
      return (PxVolume)(value.dwValue / 65535.0);
   }
   
   value.dwValue = (unsigned short)(volume * 65535.0);
   result = mixerSetControlDetails(hMixer,
                                   &details,
                                   MIXER_GETCONTROLDETAILSF_VALUE);
   
   if (result != MMSYSERR_NOERROR)
      return -1.0;
   
   return 0.0;
}