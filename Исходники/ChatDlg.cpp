LRESULT CChatDlg::onWaveInData(WPARAM wParam, LPARAM lParam)
{
	HWAVEIN hwi = (HWAVEIN) wParam;
	LPWAVEHDR pwh = (LPWAVEHDR) lParam;

	waveInUnprepareHeader(hwi, pwh, sizeof(WAVEHDR));

	short val = *(short *) pwh->lpData;
	m_sendVol.SetPos(abs(val));
	session->sendSpeechData(pwh->lpData, pwh->dwBytesRecorded);

	waveInPrepareHeader(hwi, pwh, sizeof(WAVEHDR));
	waveInAddBuffer(hwi, pwh, sizeof(WAVEHDR));

	return 0;
}