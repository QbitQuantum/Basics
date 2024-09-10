BOOL FMPlayerDShow::GetAVIInfo(const tchar* pFileName)
{
	AVIFileInit();

	PAVIFILE pfile;
	BOOL bOK = FALSE; 
	if(AVIFileOpen(&pfile, pFileName, OF_SHARE_DENY_NONE, 0L) == 0)
	{
		AVIFILEINFO afi;
		memset(&afi, 0, sizeof(afi));
		AVIFileInfo(pfile, &afi, sizeof(AVIFILEINFO));

		CComPtr<IAVIStream> pavi;
		if(AVIFileGetStream(pfile, &pavi, streamtypeVIDEO, 0) == AVIERR_OK)
		{
			AVISTREAMINFO si;
			AVIStreamInfo(pavi, &si, sizeof(si));
			m_FourCC = FormatFourCC(si.fccHandler);
			m_FrameRate = (double)si.dwRate / (double)si.dwScale; 

			LONG lFormat; 
			if (0 == AVIStreamFormatSize(pavi, 0, &lFormat))
			{
				char* pBuf = new char[lFormat];
				if (0 == AVIStreamReadFormat(pavi, 0, pBuf, &lFormat))
				{
					BITMAPINFOHEADER* pHeader = (BITMAPINFOHEADER*)pBuf; 
					m_StreamFormat = FormatFourCC(pHeader->biCompression);
				}
				delete[] pBuf; 
			}

			bOK = TRUE; 
		}

		AVIFileRelease(pfile);
	}

	AVIFileExit();
	return bOK; 
}