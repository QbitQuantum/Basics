void AudioEnvironment::setGain(float gain) {
	FMOD::ChannelGroup *channelgroup;
	_gain = gain;
	_system->getMasterChannelGroup(&channelgroup);
	channelgroup->setVolume(_gain);
} // AudioEnvironment::setGain