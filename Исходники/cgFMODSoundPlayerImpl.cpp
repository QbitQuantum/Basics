bool cgFMODSoundPlayerImpl::SetVolume( cgID channel, float fVolume )
{
	FMOD::Channel * pkChannel = m_pkChannelStorage->Find(channel);
	if (!pkChannel)
		return false;

	pkChannel->setVolume(fVolume);

	return true;
}