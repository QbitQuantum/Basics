void MCFMODSourceManager::setSourceVolume(unsigned int SourceIndex, float Volume)
{
   sSources[SourceIndex].Volume = Volume;

   FMOD::Channel* fmodChannel = reinterpret_cast<FMOD::Channel*>(sSources[SourceIndex].Source);
   bool bChannelPlaying;

   fmodChannel->isPlaying(&bChannelPlaying);

   if(bChannelPlaying)
      fmodChannel->setVolume(Volume);
}