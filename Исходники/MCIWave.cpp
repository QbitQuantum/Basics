int load_wave_file(const char* fname, LPWAVEHDR hdr, LPWAVEFORMATEX format)
{
	HMMIO       hmmio;            /* file handle for open file */ 
	MMCKINFO    mmckinfoParent;   /* parent chunk information structure */ 
	MMCKINFO    mmckinfoSubchunk; /* subchunk information structure    */ 
	DWORD       dwFmtSize;        /* size of "fmt" chunk               */ 
	DWORD       dwDataSize;       /* size of "data" chunk              */ 

	/* 
	* Open the given file for reading with buffered I/O 
	* using the default internal buffer. 
	*/ 
	hmmio = mmioOpen((LPSTR) fname, NULL, MMIO_READ | MMIO_ALLOCBUF); 

	if (hmmio == NULL) {
		Print("load_wave_file(): '%s' - Failed to open file.\n", fname); 
		return 0;
	}

	/* 
	* Locate a "RIFF" chunk with a "WAVE" form type 
	* to make sure the file is a WAVE file. 
	*/ 
	mmckinfoParent.fccType = mmioFOURCC('W', 'A', 'V', 'E'); 
	if (mmioDescend(hmmio, (LPMMCKINFO) &mmckinfoParent, NULL, MMIO_FINDRIFF)) { 
		Print("load_wave_file(): '%s' - This is not a WAVE file.\n", fname);
		mmioClose(hmmio, 0);
		return 0;
	}

	/* 
	* Find the "fmt " chunk (form type "fmt "); it must be 
	* a subchunk of the "RIFF" parent chunk. 
	*/ 
	mmckinfoSubchunk.ckid = mmioFOURCC('f', 'm', 't', ' '); 
	if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent, MMIO_FINDCHUNK)) { 
		Print("load_wave_file(): '%s' - WAVE file has no \"fmt\" chunk\n", fname);
		mmioClose(hmmio, 0);
		return 0;
	}

	/* 
	* Get the size of the "fmt " chunk--allocate and lock memory for it. 
	*/ 
	dwFmtSize = mmckinfoSubchunk.cksize; 

	/* Read the "fmt " chunk. */ 
	if (mmioRead(hmmio, (HPSTR) format, dwFmtSize) != (LRESULT)dwFmtSize) {
		Print("load_wave_file(): '%s' - Failed to read format chunk.\n", fname);
		mmioClose(hmmio, 0);
		return 0;
	}

	/* Ascend out of the "fmt " subchunk. */ 
	mmioAscend(hmmio, &mmckinfoSubchunk, 0); 

	/* 
	* Find the data subchunk. The current file position 
	* should be at the beginning of the data chunk. 
	*/ 
	mmckinfoSubchunk.ckid = mmioFOURCC('d', 'a', 't', 'a'); 
	if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent, MMIO_FINDCHUNK)) {
		Print("load_wave_file(): '%s' - WAVE file has no data chunk.\n", fname);
		mmioClose(hmmio, 0); 
		return 0; 
	} 

	/* Get the size of the data subchunk. */ 
	dwDataSize = mmckinfoSubchunk.cksize;
	if (dwDataSize == 0L) {
		Print("load_wave_file(): '%s' - The data chunk contains no data.\n", fname);
		mmioClose(hmmio, 0);
		return 0;
	}

	// allocate the data block:
	hdr->lpData = (LPSTR) new(__FILE__,__LINE__) BYTE[dwDataSize];
	hdr->dwBufferLength = dwDataSize;

	/* Read the waveform data subchunk. */
	if (mmioRead(hmmio, (HPSTR) hdr->lpData, dwDataSize) != (LRESULT)dwDataSize) {
		Print("load_wave_file(): '%s' - Failed to read data chunk.\n", fname);
		mmioClose(hmmio, 0);
		return 0;
	}

	/* Close the file. */
	mmioClose(hmmio, 0);

	return 1;
}