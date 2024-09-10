void CRotateAVIDlg::ProcessAVI(const TCHAR *source_filename, const TCHAR *dest_filename, eRotation rot)
{
	TCHAR error_buf[1024];

    PAVIFILE source_avi = 0;
    PAVIFILE dest_avi = 0;
    PAVISTREAM pSrcVidStream = 0;
    PAVISTREAM pSrcAudioStream = 0;
	PAVISTREAM pDestVidStream = 0;
	PAVISTREAM pDestAudioStream = 0;
	char *pSrcBuffer = 0;
	char *pJPGBuffer = 0;
	char *pDecompBuffer = 0;
	char *pRotateBuffer = 0;
	char *pDestBuffer = 0;

    AVIFileInit();

	// source setup

    if (AVIFileOpen(&source_avi, source_filename, OF_READ, NULL) != AVIERR_OK)
	{
		_stprintf(error_buf, TEXT("Couldn't open file %s"), source_filename);
		MessageBox(error_buf);
		goto cleanup;
	}

	AVIFILEINFO src_avi_info;
    AVIFileInfo(source_avi, &src_avi_info, sizeof(AVIFILEINFO));

    if (AVIFileGetStream(source_avi, &pSrcVidStream, streamtypeVIDEO, 0) != AVIERR_OK)
    {
		_stprintf(error_buf, TEXT("No video stream in %s"), source_filename);
		MessageBox(error_buf);
		goto cleanup;
    }

	BITMAPINFOHEADER srcBIH;
	long srcvidstreamsize;
    AVIStreamFormatSize(pSrcVidStream, 0, &srcvidstreamsize); 
    if (srcvidstreamsize > sizeof(BITMAPINFOHEADER))
	{
		_stprintf(error_buf, TEXT("Unable to handle video stream format in %s"), source_filename);
		MessageBox(error_buf);
		goto cleanup;
	}
 
    srcvidstreamsize = sizeof(BITMAPINFOHEADER); 
    if (AVIStreamReadFormat(pSrcVidStream, 0, &srcBIH, &srcvidstreamsize) != AVIERR_OK)
	{
		_stprintf(error_buf, TEXT("Error reading stream format in %s"), source_filename);
		MessageBox(error_buf);
		goto cleanup;
	}
    if (srcBIH.biCompression != MKFOURCC('M','J','P','G'))
	{
		_stprintf(error_buf, TEXT("%s is not motion JPEG format"), source_filename);
		MessageBox(error_buf);
		goto cleanup;
	}
 
	AVISTREAMINFO vidstream_info;
    if (AVIStreamInfo(pSrcVidStream, &vidstream_info, sizeof(AVISTREAMINFO)) != AVIERR_OK)
	{
		_stprintf(error_buf, TEXT("Error reading stream info in %s"), source_filename);
		MessageBox(error_buf);
		goto cleanup;
	}

    int firstVidSrcFrame = AVIStreamStart(pSrcVidStream);
    if (firstVidSrcFrame == -1)
	{
		_stprintf(error_buf, TEXT("Video stream start error in %s"), source_filename);
		MessageBox(error_buf);
		goto cleanup;
	}
    int numVidSrcFrames = AVIStreamLength(pSrcVidStream);
    if (numVidSrcFrames == -1)
	{
		_stprintf(error_buf, TEXT("Video stream length error in %s"), source_filename);
		MessageBox(error_buf);
		goto cleanup;
	}

    AVIFileGetStream(source_avi, &pSrcAudioStream, streamtypeAUDIO, 0);
	int firstAudioSrcFrame = 0;
	int numAudioSrcFrames = 0;
	if (pSrcAudioStream)
	{
		firstAudioSrcFrame = AVIStreamStart(pSrcAudioStream);
		if (firstAudioSrcFrame == -1)
		{
			_stprintf(error_buf, TEXT("Audio stream start error in %s"), source_filename);
			MessageBox(error_buf);
			goto cleanup;
		}
		numAudioSrcFrames = AVIStreamLength(pSrcAudioStream);
		if (numAudioSrcFrames == -1)
		{
			_stprintf(error_buf, TEXT("Audio stream length error in %s"), source_filename);
			MessageBox(error_buf);
			goto cleanup;
		}
	}

	// dest setup

	BITMAPINFOHEADER destBIH;
	destBIH = srcBIH;
	if (rot != CW_180)
	{
		destBIH.biWidth = srcBIH.biHeight;
		destBIH.biHeight = srcBIH.biWidth;
	}

    if (AVIFileOpen(&dest_avi, dest_filename, OF_CREATE | OF_WRITE, NULL) != AVIERR_OK)
	{
		_stprintf(error_buf, TEXT("Couldn't open file %s"), dest_filename);
		MessageBox(error_buf);
		goto cleanup;
	}
	vidstream_info.rcFrame.left = vidstream_info.rcFrame.top = 0;
	vidstream_info.rcFrame.right = destBIH.biWidth;
	vidstream_info.rcFrame.bottom = destBIH.biHeight;
 
    if (AVIFileCreateStream(dest_avi, &pDestVidStream, &vidstream_info) != AVIERR_OK)
	{
		_stprintf(error_buf, TEXT("Error creating video stream in %s"), dest_filename);
		MessageBox(error_buf);
		goto cleanup;
	}
 
    if (AVIStreamSetFormat(pDestVidStream, 0, &destBIH, sizeof(BITMAPINFOHEADER)) != AVIERR_OK)
	{ 
		_stprintf(error_buf, TEXT("Error setting video stream format in %s"), dest_filename);
		MessageBox(error_buf);
		goto cleanup;
    } 

    if (AVIStreamSetFormat(pDestVidStream, 0, &destBIH, sizeof(BITMAPINFOHEADER)) != AVIERR_OK)
	{ 
		_stprintf(error_buf, TEXT("Error setting video stream format in %s"), dest_filename);
		MessageBox(error_buf);
		goto cleanup;
    } 

	// video memory
	int img_rgb_size = srcBIH.biHeight * srcBIH.biWidth * 3;
	pSrcBuffer = new char[img_rgb_size];
	pJPGBuffer = new char[img_rgb_size];
	pDecompBuffer = new char[img_rgb_size];
	pRotateBuffer = new char[img_rgb_size];
	pDestBuffer = new char[img_rgb_size];

	long bytes_read;
	long bytes_written;

	for (int i = firstVidSrcFrame; i < numVidSrcFrames; ++i)
	{
		if (AVIStreamRead(pSrcVidStream, i, 1, pSrcBuffer, img_rgb_size, &bytes_read, 0) != AVIERR_OK)
		{
			_stprintf(error_buf, TEXT("Error reading video stream from %s"), source_filename);
			MessageBox(error_buf);
			goto cleanup;
		}

		// well-form the jpg
		int jpglen = ConstructWellFormedJPEG(pSrcBuffer, pJPGBuffer, bytes_read);
		// decompress
		JPEGHandler jpgh_decomp(pJPGBuffer, jpglen);
		jpgh_decomp.DecompressToRGB(pDecompBuffer, img_rgb_size);
		// rotate
		int destx, desty;
		char *pRotSrc;
		char *pRotDest;
		switch (rot)
		{
		case CW_90:
			for (int srcy = 0; srcy < srcBIH.biHeight; ++srcy)
			{
				for (int srcx = 0; srcx < srcBIH.biWidth; ++srcx)
				{
					destx = srcBIH.biHeight-1-srcy;
					desty = srcx;
					pRotSrc = &pDecompBuffer[(srcy * srcBIH.biWidth + srcx) * 3];
					pRotDest = &pRotateBuffer[(desty * srcBIH.biHeight + destx) * 3];

					*pRotDest++ = *pRotSrc++;
					*pRotDest++ = *pRotSrc++;
					*pRotDest++ = *pRotSrc++;
				}
			}
			break;

		case CW_180:
			for (int srcy = 0; srcy < srcBIH.biHeight; ++srcy)
			{
				for (int srcx = 0; srcx < srcBIH.biWidth; ++srcx)
				{
					destx = srcBIH.biWidth-1-srcx;
					desty = srcBIH.biHeight-1-srcy;
					pRotSrc = &pDecompBuffer[(srcy * srcBIH.biWidth + srcx) * 3];
					pRotDest = &pRotateBuffer[(desty * srcBIH.biWidth + destx) * 3];

					*pRotDest++ = *pRotSrc++;
					*pRotDest++ = *pRotSrc++;
					*pRotDest++ = *pRotSrc++;
				}
			}
			break;

		case ACW_90:
			for (int srcy = 0; srcy < srcBIH.biHeight; ++srcy)
			{
				for (int srcx = 0; srcx < srcBIH.biWidth; ++srcx)
				{
					destx = srcy;
					desty = srcBIH.biWidth-1-srcx;
					pRotSrc = &pDecompBuffer[(srcy * srcBIH.biWidth + srcx) * 3];
					pRotDest = &pRotateBuffer[(desty * srcBIH.biHeight + destx) * 3];

					*pRotDest++ = *pRotSrc++;
					*pRotDest++ = *pRotSrc++;
					*pRotDest++ = *pRotSrc++;
				}
			}
			break;
		}
		// compress
		JPEGHandler jpgh_comp(pRotateBuffer, img_rgb_size);
		if (rot != CW_180)
			destBIH.biSizeImage = jpgh_comp.CompressFromRGB(pDestBuffer, img_rgb_size, srcBIH.biHeight, srcBIH.biWidth);
		else
			destBIH.biSizeImage = jpgh_comp.CompressFromRGB(pDestBuffer, img_rgb_size, srcBIH.biWidth, srcBIH.biHeight);

		if (AVIStreamWrite(pDestVidStream, i, 1, pDestBuffer, destBIH.biSizeImage, AVIIF_KEYFRAME, NULL, &bytes_written) != AVIERR_OK)
		{
			_stprintf(error_buf, TEXT("Error writing video stream to %s"), dest_filename);
			MessageBox(error_buf);
			goto cleanup;
		}
	} 
 
cleanup:
	delete[] pSrcBuffer;
	delete[] pDestBuffer;
	delete[] pJPGBuffer;
	delete[] pDecompBuffer;
	delete[] pRotateBuffer;
	if (pDestAudioStream) AVIStreamRelease(pDestAudioStream);
	if (pDestVidStream) AVIStreamRelease(pDestVidStream);
	if (pSrcAudioStream) AVIStreamRelease(pSrcAudioStream);
	if (pSrcVidStream) AVIStreamRelease(pSrcVidStream);
	if (dest_avi) AVIFileRelease(dest_avi);
	if (source_avi) AVIFileRelease(source_avi);

	AVIFileExit();
}