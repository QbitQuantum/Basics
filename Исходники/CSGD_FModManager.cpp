bool CSGD_FModManager::PlaySound( int nID )
{
	if( !m_pSystem ) return false;

	//	check that ID is in range
	assert( nID > -1 && nID < (int)m_SoundList.size() && "ID is out of range" );

	//	Address of a channel handle pointer that receives the newly playing channel
	FMOD::Channel *channel;
	//	used to catch fMod-specific error codes
	FMOD_RESULT result;

	if( ( result = m_pSystem->playSound(FMOD_CHANNEL_FREE, m_SoundList[ nID ].fmSound , false, &channel) ) != FMOD_OK )
	{
		FMODERR( result );
	}

	//  set the volume of this playing channel
	channel->setVolume(m_SoundList[nID].fVolume);

	//  set the pan of this playing channel
	channel->setPan(m_SoundList[nID].fPan);

	//  set the volume of this playing channel
	//channel->setFrequency(m_SoundList[nID].fFreq);

	//	hold on to channel pointer for late use
	m_SoundList[ nID ].m_SoundChannels.push_back( channel );

	//	return success
	return true;
}