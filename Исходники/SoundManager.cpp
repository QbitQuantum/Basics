void SoundManager::update(Camera* p_gameCamera)
{
	m_masterVoice->SetVolume(m_masterVolume,0);
	updateListener(p_gameCamera);

	X3DAudioCalculate(m_X3DAudioInstance, &m_listener, &m_music->getEmitter(),
		X3DAUDIO_CALCULATE_MATRIX, &m_music->getDSPSettings());

	IXAudio2SourceVoice* voice = m_music->getSource();
	m_left = m_matrixCoefficients[0];
	m_right = m_matrixCoefficients[1];
	voice->SetOutputMatrix( m_masterVoice, 1, m_destChannels, m_matrixCoefficients);

	if(!m_music->isPlaying())
		m_music->play();
}