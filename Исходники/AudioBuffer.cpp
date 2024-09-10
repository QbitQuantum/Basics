bool WaveFileHelper::Read(HMMIO hio)
{
	assertRetVal(hio && !_format && !_data, false);

	MMCKINFO ckRiff;
	ff::ZeroObject(ckRiff);
	assertRetVal(MMSYSERR_NOERROR == mmioDescend(hio, &ckRiff, nullptr, 0), false);
	assertRetVal(ckRiff.ckid == FOURCC_RIFF && ckRiff.fccType == mmioFOURCC('W', 'A', 'V', 'E'), false);

	MMCKINFO ckIn;
	ff::ZeroObject(ckIn);
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	assertRetVal(MMSYSERR_NOERROR == mmioDescend(hio, &ckIn, &ckRiff, MMIO_FINDCHUNK), false);
	assertRetVal(ckIn.cksize >= sizeof(PCMWAVEFORMAT), false);

	PCMWAVEFORMAT pcmFormat;
	ff::ZeroObject(pcmFormat);
	assertRetVal(mmioRead(hio, (HPSTR)&pcmFormat, sizeof(pcmFormat)) == sizeof(pcmFormat), false);

	if(pcmFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		_format.reset(new WAVEFORMATEX);
		*_format = *(WAVEFORMATEX*)&pcmFormat;
		_format->cbSize = 0;
	}
	else
	{
		// Read in length of extra bytes.
		WORD cbExtraBytes;
		assertRetVal(mmioRead(hio, (HPSTR)&cbExtraBytes, sizeof(WORD)) == sizeof(WORD), false);

		_format.reset((WAVEFORMATEX*)new BYTE[sizeof(WAVEFORMATEX) + cbExtraBytes]);
		*_format = *(WAVEFORMATEX*)&pcmFormat;
		_format->cbSize = cbExtraBytes;

		assertRetVal(mmioRead(hio, (HPSTR)(&_format->cbSize + 1), cbExtraBytes) == cbExtraBytes, false);
	}

	assertRetVal(MMSYSERR_NOERROR == mmioAscend(hio, &ckIn, 0), false);

	// Seek to the data
	MMCKINFO ckData;
	ff::ZeroObject(ckData);
	ckData.ckid = mmioFOURCC('d', 'a', 't', 'a');
	assertRetVal(-1 != mmioSeek(hio, ckRiff.dwDataOffset + sizeof(FOURCC), SEEK_SET), false);
	assertRetVal(MMSYSERR_NOERROR == mmioDescend(hio, &ckData, &ckRiff, MMIO_FINDCHUNK), false);

	assertRetVal(ff::CreateDataInData(_fullData, ckData.dwDataOffset, ckData.cksize, &_data), false);

	return true;
}