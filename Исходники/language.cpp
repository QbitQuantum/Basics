LANGID Language::getLangID(ISpObjectToken * pVoiceToken) {
	LANGID langID;
	HRESULT hr = SpGetLanguageFromToken(pVoiceToken, &langID);
	if (FAILED(hr)) throw new COMException(hr);
	return langID;
}