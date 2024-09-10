//Get available voices in system
std::vector<WCHAR*> TTSLib::GetVoices()
{
	std::vector<WCHAR*> voiceNames;
	voiceNames.resize(m_ispObjectTokens.size());
	WCHAR *description;

	for (size_t i = 0; i < m_ispObjectTokens.size(); ++i)
	{
		SpGetDescription(m_ispObjectTokens[i], &description);
		voiceNames[i]= description;
	}
	
	return voiceNames;
}