ieResult ie_fif_Reader::ReadImageX(ieImage *pim, bool bLoadSmall, iePProgress pProgress, volatile bool *pbCancel)
{
	long	lCH;
    if (OpenDecompressor(&lCH)) return IE_E_GENERAL;

	if (SetFIFBuffer(lCH, (PBYTE)pMem->Ptr(), (long)pMem->Size())) return IE_E_GENERAL;

	// Init file
    TCHAR	szFTTFileName[256] = _T("");
    PBYTE	pbFTT = nullptr;
	DWORD	dw;
    IE_HFILE	hf;
    if (GetFIFFTTFileName(lCH, (PBYTE)szFTTFileName)) return IE_E_GENERAL;
    if (*szFTTFileName != 0) {
		hf = CreateFile(szFTTFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == IE_INVALIDHFILE) return IE_E_FILEOPEN;
        dw = (DWORD)ief_Size(hf);
        pbFTT = IE_NEW BYTE[dw];
		if (!pbFTT) return IE_E_OUTOFMEMORY;
		ief_Read(hf, pbFTT, dw);
        ief_Close(hf);
        if (SetFTTBuffer(lCH, pbFTT, dw)) return IE_E_GENERAL;
    }

	// Set options
    if (SetOutputFormat(lCH, BLUE8, GREEN8, RED8, BLANK8, TOP_LEFT)) return IE_E_GENERAL;
    if (SetOutputResolution(lCH, pim->X(), pim->Y())) return IE_E_GENERAL;

	// Decompress
	if (pProgress) {
        pProgressCB = pProgress;
	    SetDecompressCallback(lCH, &FIFCallback, CALLBACK_FREQ_LOW);
    }

	if (DecompressToBuffer(lCH, pim->RawPixelPtr(), 0, 0, 0, 0, pim->Pitch() * sizeof(ieBGRA))) return IE_E_CORRUPTEDFILE;

	// Clean up
    if (pbFTT) {
    	ClearFTTBuffer(lCH);
        delete[] pbFTT;
    }
    ClearFIFBuffer(lCH);
    CloseDecompressor(lCH);

	// Set alpha to 1.0
	iePBGRA p4 = pim->BGRA()->PixelPtr();
	DWORD nSkip = (pim->BGRA()->Pitch() - nX);
	for (DWORD y = nY; y--; p4 += nSkip)
		for (DWORD x = nX; x--; p4++)
			p4->A = 0xFF;

	return IE_S_OK;
}