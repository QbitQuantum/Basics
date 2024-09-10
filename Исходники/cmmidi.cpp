COMMNG cmmidi_create(const OEMCHAR *midiout, const OEMCHAR *midiin,
													const OEMCHAR *module) {

	UINT		opened;
	UINT		id;
	void		(*shortout)(CMMIDI self, UINT32 msg);
	void		(*longout)(CMMIDI self, const UINT8 *msg, UINT leng);
	HMIDIFNOUT	out;
	HMIDIIN		hmidiin = NULL;
	COMMNG		ret;
	CMMIDI		midi;

	opened = 0;
	ZeroMemory(&out, sizeof(out));
	shortout = midi_ncshort;
	longout = midi_nclong;
	if (getmidioutid(midiout, &id) == SUCCESS) {
		if (midiOutOpen(&out.win32.hmidiout, id, 0, 0, CALLBACK_NULL)
														== MMSYSERR_NOERROR) {
			midiOutReset(out.win32.hmidiout);
			shortout = midi_win32short;
			longout = midi_win32long;
			opened |= CMMIDI_MIDIOUT;
		}
	}
	if (getmidiinid(midiin, &id) == SUCCESS) {
		if (midiInOpen(&hmidiin, id, (DWORD)g_hWndMain, 0, CALLBACK_WINDOW)
														== MMSYSERR_NOERROR) {
			midiInReset(hmidiin);
			opened |= CMMIDI_MIDIIN;
		}
	}
#if defined(VERMOUTH_LIB)
	else if (!milstr_cmp(midiout, cmmidi_vermouth)) {
		out.vermouth = midiout_create(vermouth_module, 512);
		if (out.vermouth != NULL) {
			shortout = midi_vermouthshort;
			longout = midi_vermouthlong;
			opened |= CMMIDI_VERMOUTH;
		}
	}
#endif
#if defined(MT32SOUND_DLL)
	else if (!milstr_cmp(midiout, cmmidi_mt32sound)) {
		if (mt32sound_open() == SUCCESS) {
			shortout = midi_mt32short;
			longout = midi_mt32long;
			opened |= CMMIDI_MT32SOUND;
		}
	}
#endif
	if (!opened) {
		goto cmcre_err1;
	}
	ret = (COMMNG)_MALLOC(sizeof(_COMMNG) + sizeof(_CMMIDI), "MIDI");
	if (ret == NULL) {
		goto cmcre_err2;
	}
	ret->connect = COMCONNECT_MIDI;
	ret->read = midiread;
	ret->write = midiwrite;
	ret->getstat = midigetstat;
	ret->msg = midimsg;
	ret->release = midirelease;
	midi = (CMMIDI)(ret + 1);
	ZeroMemory(midi, sizeof(_CMMIDI));
	midi->opened = opened;
	midi->shortout = shortout;
	midi->longout = longout;
	midi->out = out;
	midi->midictrl = MIDICTRL_READY;
#if 1
	midi->hmidiin = hmidiin;
	if (opened & CMMIDI_MIDIIN) {
		if (midiinhdlreg(midi, hmidiin) == SUCCESS) {
			midi->opened |= CMMIDI_MIDIINSTART;
			midi->hmidiinhdr.lpData = (char *)midi->midiinbuf;
			midi->hmidiinhdr.dwBufferLength = MIDI_BUFFER;
			midiInPrepareHeader(hmidiin, &midi->hmidiinhdr, sizeof(MIDIHDR));
			midiInAddBuffer(hmidiin, &midi->hmidiinhdr, sizeof(MIDIHDR));
			midiInStart(hmidiin);
		}
	}
#endif
#if defined(VERMOUTH_LIB)
	if (opened & CMMIDI_VERMOUTH) {
		sound_streamregist((void *)out.vermouth, (SOUNDCB)vermouth_getpcm);
	}
#endif
#if defined(MT32SOUND_DLL)
	if (opened & CMMIDI_MT32SOUND) {
		sound_streamregist(NULL, (SOUNDCB)mt32_getpcm);
	}
#endif
//	midi->midisyscnt = 0;
//	midi->mpos = 0;

	midi->midilast = 0x80;
//	midi->midiexcvwait = 0;
	midi->midimodule = (UINT8)module2number(module);
	FillMemory(midi->mch, sizeof(midi->mch), 0xff);
	return(ret);

cmcre_err2:
	if (opened & CMMIDI_MIDIOUT) {
		midiOutReset(out.win32.hmidiout);
		midiOutClose(out.win32.hmidiout);
	}
#if defined(VERMOUTH_LIB)
	if (opened & CMMIDI_VERMOUTH) {
		midiout_destroy(out.vermouth);
	}
#endif
#if defined(MT32SOUND_DLL)
	if (opened & CMMIDI_MT32SOUND) {
		mt32sound_close();
	}
#endif

cmcre_err1:
	return(NULL);
}