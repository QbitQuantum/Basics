//------------------------------------------------------------------------------
std::vector<std::wstring> SpeechApi51::getVoices() const
{
	std::vector<std::wstring> ret;
	
	CoInitialize(NULL);

	// get a voice enumerator
	CComPtr<IEnumSpObjectTokens> cpEnum;
	if (S_OK != SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum))
	{
		return ret;
	}

	// iterate through the voices and add them to the string vector
	ISpObjectToken *voice_token;
	while (S_OK == cpEnum->Next(1, &voice_token, NULL))
	{
		CSpDynamicString voice_str;

		if (SUCCEEDED(SpGetDescription(voice_token, &voice_str)))
		{
			ret.push_back(voice_str.Copy());
		}
	}

	return ret;
}