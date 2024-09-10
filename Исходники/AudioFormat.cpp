void SuggestLocalCompressFormat() {

	bAudioCompressionLocal = TRUE;

	AllocLocalCompressFormat();

	//1st try MPEGLAYER3
	BuildLocalRecordingFormat();
	MMRESULT mmr;
	if ((m_FormatLocal.nSamplesPerSec == 22050) && (m_FormatLocal.nChannels==2) && (m_FormatLocal.wBitsPerSample <= 16)) {

		pwfxLocal->wFormatTag = WAVE_FORMAT_MPEGLAYER3;
		mmr = acmFormatSuggest(NULL, &m_FormatLocal,  pwfxLocal, cbwfxLocal, ACM_FORMATSUGGESTF_WFORMATTAG);

	}

	//if (mmr!=0) {

		//Then try ADPCM
		//BuildLocalRecordingFormat();
		//pwfxLocal->wFormatTag = WAVE_FORMAT_ADPCM;
		//MMRESULT mmr = acmFormatSuggest(NULL, &m_FormatLocal,  pwfxLocal, cbwfxLocal, ACM_FORMATSUGGESTF_WFORMATTAG);

		if (mmr!=0) {

			//Use the PCM as default
			BuildLocalRecordingFormat();
			pwfxLocal->wFormatTag = WAVE_FORMAT_PCM;
			MMRESULT mmr = acmFormatSuggest(NULL, &m_FormatLocal,  pwfxLocal, cbwfxLocal, ACM_FORMATSUGGESTF_WFORMATTAG);

			if (mmr!=0) {

				bAudioCompressionLocal = FALSE;

			}

		//}

	}

}