void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback){
 try{
    FMOD::Channel * channel = mapChannelInfo[audioID].channel;
    mapChannelInfo[audioID].callback = callback; 
    FMOD_RESULT result = channel->setCallback(channelCallback);
    ERRCHECK(result);
    }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::setFinishCallback: invalid audioID: %d\n", audioID);
  }
};