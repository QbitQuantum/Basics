void Px_SetCurrentInputSource( PxMixer *mixer, int i )
{
   PxInfo *info = (PxInfo *)mixer;
   MIXERCONTROLDETAILS details;
   MIXERCONTROLDETAILS_BOOLEAN flags[32];
   MMRESULT result;
   int j;

   details.cbStruct = sizeof(MIXERCONTROLDETAILS);
   details.dwControlID = info->muxID;
   details.cMultipleItems = info->numInputs;
   details.cChannels = 1;   
   details.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
   details.paDetails = (LPMIXERCONTROLDETAILS_BOOLEAN)&flags[0];

   for(j=0; j<info->numInputs; j++)
      flags[j].fValue = (i == j);

   result = mixerSetControlDetails(info->hInputMixer,
                                   (LPMIXERCONTROLDETAILS)&details,
                                   MIXER_SETCONTROLDETAILSF_VALUE);
}