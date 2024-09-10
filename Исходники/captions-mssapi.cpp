mssapi_captions::mssapi_captions(
		captions_cb callback,
		const std::string &lang) try
	: captions_handler(callback, AUDIO_FORMAT_16BIT, 16000)
{
	HRESULT hr;

	std::wstring wlang;
	wlang.resize(lang.size());

	for (size_t i = 0; i < lang.size(); i++)
		wlang[i] = (wchar_t)lang[i];

	LCID lang_id = LocaleNameToLCID(wlang.c_str(), 0);

	wchar_t lang_str[32];
	_snwprintf(lang_str, 31, L"language=%x", (int)lang_id);

	stop = CreateEvent(nullptr, false, false, nullptr);
	if (!stop.Valid())
		throw "Failed to create event";

	hr = SpFindBestToken(SPCAT_RECOGNIZERS, lang_str, nullptr, &token);
	if (FAILED(hr))
		throw HRError("SpFindBestToken failed", hr);

	hr = CoCreateInstance(CLSID_SpInprocRecognizer, nullptr, CLSCTX_ALL,
			__uuidof(ISpRecognizer), (void**)&recognizer);
	if (FAILED(hr))
		throw HRError("CoCreateInstance for recognizer failed", hr);

	hr = recognizer->SetRecognizer(token);
	if (FAILED(hr))
		throw HRError("SetRecognizer failed", hr);

	hr = recognizer->SetRecoState(SPRST_INACTIVE);
	if (FAILED(hr))
		throw HRError("SetRecoState(SPRST_INACTIVE) failed", hr);

	hr = recognizer->CreateRecoContext(&context);
	if (FAILED(hr))
		throw HRError("CreateRecoContext failed", hr);

	ULONGLONG interest = SPFEI(SPEI_RECOGNITION) |
	                     SPFEI(SPEI_END_SR_STREAM);
	hr = context->SetInterest(interest, interest);
	if (FAILED(hr))
		throw HRError("SetInterest failed", hr);

	hr = context->SetNotifyWin32Event();
	if (FAILED(hr))
		throw HRError("SetNotifyWin32Event", hr);

	notify = context->GetNotifyEventHandle();
	if (notify == INVALID_HANDLE_VALUE)
		throw HRError("GetNotifyEventHandle failed", E_NOINTERFACE);

	size_t sample_rate = audio_output_get_sample_rate(obs_get_audio());
	audio = new CaptionStream((DWORD)sample_rate, this);
	audio->Release();

	hr = recognizer->SetInput(audio, false);
	if (FAILED(hr))
		throw HRError("SetInput failed", hr);

	hr = context->CreateGrammar(1, &grammar);
	if (FAILED(hr))
		throw HRError("CreateGrammar failed", hr);

	hr = grammar->LoadDictation(nullptr, SPLO_STATIC);
	if (FAILED(hr))
		throw HRError("LoadDictation failed", hr);

	try {
		t = std::thread([this] () {main_thread();});
	} catch (...) {
		throw "Failed to create thread";
	}

} catch (const char *err) {
	blog(LOG_WARNING, "%s: %s", __FUNCTION__, err);
	throw CAPTIONS_ERROR_GENERIC_FAIL;

} catch (HRError err) {
	blog(LOG_WARNING, "%s: %s (%lX)", __FUNCTION__, err.str, err.hr);
	throw CAPTIONS_ERROR_GENERIC_FAIL;
}