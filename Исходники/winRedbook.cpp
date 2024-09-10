void Win32RedBookDevice::closeVolume()
{
   setLastError("");
   if(!mVolumeInitialized)
      return;

   if(mUsingMixer)
   {
      mMixerVolumeValue.dwValue = mOriginalVolume;
      mixerSetControlDetails(mVolumeDeviceId, &mMixerVolumeDetails, MIXER_SETCONTROLDETAILSF_VALUE);
      mixerClose((HMIXER)mVolumeDeviceId);
   }
   else
      auxSetVolume(mAuxVolumeDeviceId, mOriginalVolume);

   mVolumeInitialized = false;
}