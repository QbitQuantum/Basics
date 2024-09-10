void obs_captions::main_thread()
try {
	ComPtr<CaptionStream>  audio;
	ComPtr<ISpObjectToken> token;
	ComPtr<ISpRecoGrammar> grammar;
	ComPtr<ISpRecognizer>  recognizer;
	ComPtr<ISpRecoContext> context;
	HRESULT hr;

	auto cb = [&] (const struct audio_data *audio_data,
			bool muted)
	{
		audio->PushAudio(audio_data, muted);
	};

	using cb_t = decltype(cb);

	auto pre_cb = [] (void *param, obs_source_t*,
		const struct audio_data *audio_data, bool muted)
	{
		return (*static_cast<cb_t*>(param))(audio_data, muted);
	};

	os_set_thread_name(__FUNCTION__);

	CoInitialize(nullptr);

	wchar_t lang_str[32];
	_snwprintf(lang_str, 31, L"language=%x", (int)captions->lang_id);

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

	HANDLE notify;

	hr = context->SetNotifyWin32Event();
	if (FAILED(hr))
		throw HRError("SetNotifyWin32Event", hr);

	notify = context->GetNotifyEventHandle();
	if (notify == INVALID_HANDLE_VALUE)
		throw HRError("GetNotifyEventHandle failed", E_NOINTERFACE);

	size_t sample_rate = audio_output_get_sample_rate(obs_get_audio());
	audio = new CaptionStream((DWORD)sample_rate);
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

	hr = grammar->SetDictationState(SPRS_ACTIVE);
	if (FAILED(hr))
		throw HRError("SetDictationState failed", hr);

	hr = recognizer->SetRecoState(SPRST_ACTIVE);
	if (FAILED(hr))
		throw HRError("SetRecoState(SPRST_ACTIVE) failed", hr);

	HANDLE events[] = {notify, stop_event};

	{
		captions->source = GetWeakSourceByName(
				captions->source_name.c_str());
		OBSSource strong = OBSGetStrongRef(source);
		if (strong)
			obs_source_add_audio_capture_callback(strong,
					pre_cb, &cb);
	}

	for (;;) {
		DWORD ret = WaitForMultipleObjects(2, events, false, INFINITE);
		if (ret != WAIT_OBJECT_0)
			break;

		CSpEvent event;
		bool exit = false;

		while (event.GetFrom(context) == S_OK) {
			if (event.eEventId == SPEI_RECOGNITION) {
				ISpRecoResult *result = event.RecoResult();

				CoTaskMemPtr<wchar_t> text;
				hr = result->GetText((ULONG)-1, (ULONG)-1,
						true, &text, nullptr);
				if (FAILED(hr))
					continue;

				char text_utf8[512];
				os_wcs_to_utf8(text, 0, text_utf8, 512);

				obs_output_t *output =
					obs_frontend_get_streaming_output();
				if (output)
					obs_output_output_caption_text1(output,
							text_utf8);

				debug("\"%s\"", text_utf8);

				obs_output_release(output);

			} else if (event.eEventId == SPEI_END_SR_STREAM) {
				exit = true;
				break;
			}
		}

		if (exit)
			break;
	}

	{
		OBSSource strong = OBSGetStrongRef(source);
		if (strong)
			obs_source_remove_audio_capture_callback(strong,
					pre_cb, &cb);
	}

	audio->Stop();

	CoUninitialize();

} catch (HRError err) {
	error("%s failed: %s (%lX)", __FUNCTION__, err.str, err.hr);
	CoUninitialize();
	captions->th.detach();
}