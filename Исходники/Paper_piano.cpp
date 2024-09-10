static int midi_init(void){

	MIDIHDR mhMidi;

	/* GMリセット用データ */
	BYTE abyGMReset[] = {0xf0, 0x7e, 0x7f, 0x09, 0x01, 0xf7};


	/* MIDIデバイスオープン */
	if (midiOutOpen(&g_hMidi, MIDIMAPPER, 0, 0, 0) != MMSYSERR_NOERROR) {
		return 0;
	}

	ZeroMemory(&mhMidi, sizeof(mhMidi));

	/* GMリセット送信用バッファ設定 */
	mhMidi.lpData = (LPSTR)abyGMReset;
	mhMidi.dwBufferLength = 6;
	mhMidi.dwBytesRecorded = 6;
	midiOutPrepareHeader(g_hMidi, &mhMidi, sizeof(mhMidi));

	/* GMリセットメッセージ送信 */
	if (midiOutLongMsg(g_hMidi, &mhMidi, sizeof(mhMidi)) != MMSYSERR_NOERROR) {

		midiOutUnprepareHeader(g_hMidi, &mhMidi, sizeof(mhMidi));

		std::cout<<"MIDI音源の初期化に失敗しました。"<<std::endl;
		midiOutClose(g_hMidi);

		return 0;

	}

		/* GMリセット完了待機 */
		while ((mhMidi.dwFlags & MHDR_DONE) == 0);

		midiOutUnprepareHeader(g_hMidi, &mhMidi, sizeof(mhMidi));


		return 0;
}