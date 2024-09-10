//////////////////////////////////////////////////////////////////////
// mciClose()
// close the music stream.
//////////////////////////////////////////////////////////////////////
DWORD MUSIC::Close() {
	if(m_DID != MUSIC_ERROR) {
		MCIERROR mciERR = ERROR_SUCCESS;
		MCI_GENERIC_PARMS mci_p = {0};

		mci_p.dwCallback = (DWORD_PTR)m_dwCallBack;

		mciERR = mciSendCommandW(
			m_DID,
			MCI_CLOSE,
			MCI_NOTIFY,
			(DWORD_PTR)&mci_p);

		m_DID = MUSIC_ERROR;
		return mciERR;
	} else {
		return ERROR_SUCCESS;
	}
}