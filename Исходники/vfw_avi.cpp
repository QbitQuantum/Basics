BOOL ExtractAVIFrames(CString szFileName)
{
	AVIFileInit();

	PAVIFILE avi;
	int res = AVIFileOpen(&avi, szFileName, OF_READ, NULL);

	if (res != AVIERR_OK)
	{
		//an error occures
		if (avi != NULL)
			AVIFileRelease(avi);

		return FALSE;
	}

	AVIFILEINFO avi_info;
	AVIFileInfo(avi, &avi_info, sizeof(AVIFILEINFO));

	CString szFileInfo;
	szFileInfo.Format("Dimention: %dx%d\n"
		"Length: %d frames\n"
		"Max bytes per second: %d\n"
		"Samples per second: %d\n"
		"Streams: %d\n"
		"File Type: %d", avi_info.dwWidth,
		avi_info.dwHeight,
		avi_info.dwLength,
		avi_info.dwMaxBytesPerSec,
		(DWORD)(avi_info.dwRate / avi_info.dwScale),
		avi_info.dwStreams,
		avi_info.szFileType);

	AfxMessageBox(szFileInfo, MB_ICONINFORMATION | MB_OK);

	PAVISTREAM pStream;
	res = AVIFileGetStream(avi, &pStream, streamtypeVIDEO /*video stream*/,
		0 /*first stream*/);

	if (res != AVIERR_OK)
	{
		if (pStream != NULL)
			AVIStreamRelease(pStream);

		AVIFileExit();
		return FALSE;
	}

	//do some task with the stream
	int iNumFrames;
	int iFirstFrame;

	iFirstFrame = AVIStreamStart(pStream);
	if (iFirstFrame == -1)
	{
		//Error getteing the frame inside the stream

		if (pStream != NULL)
			AVIStreamRelease(pStream);

		AVIFileExit();
		return FALSE;
	}

	iNumFrames = AVIStreamLength(pStream);
	if (iNumFrames == -1)
	{
		//Error getteing the number of frames inside the stream

		if (pStream != NULL)
			AVIStreamRelease(pStream);

		AVIFileExit();
		return FALSE;
	}

	//getting bitmap from frame
	BITMAPINFOHEADER bih;
	ZeroMemory(&bih, sizeof(BITMAPINFOHEADER));

	bih.biBitCount = 24;    //24 bit per pixel
	bih.biClrImportant = 0;
	bih.biClrUsed = 0;
	bih.biCompression = BI_RGB;
	bih.biPlanes = 1;
	bih.biSize = 40;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	//calculate total size of RGBQUAD scanlines (DWORD aligned)
	bih.biSizeImage = (((bih.biWidth * 3) + 3) & 0xFFFC) * bih.biHeight;

	PGETFRAME pFrame;
	pFrame = AVIStreamGetFrameOpen(pStream,
		NULL/*(BITMAPINFOHEADER*) AVIGETFRAMEF_BESTDISPLAYFMT*/ /*&bih*/);

	//Get the first frame
	int index = 0;
	for (int i = iFirstFrame; i<iNumFrames; i++)
	{
		index = i - iFirstFrame;

		BYTE* pDIB = (BYTE*)AVIStreamGetFrame(pFrame, index);

		CreateFromPackedDIBPointer(pDIB, index);
	}

	AVIStreamGetFrameClose(pFrame);

	//close the stream after finishing the task
	if (pStream != NULL)
		AVIStreamRelease(pStream);

	AVIFileExit();

	return TRUE;
}