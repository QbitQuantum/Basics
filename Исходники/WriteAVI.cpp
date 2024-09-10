bool CAVIFile::AddFrame(CBitmap& bmp)
{
	HRESULT hr;
//	char szMessage[BUFSIZE];

	if (!bOK)
		return false;
	LPBITMAPINFOHEADER alpbi = (LPBITMAPINFOHEADER)GlobalLock(MakeDib(bmp, 8));
	if (alpbi == NULL)
		return false;
	if (xDim>=0 && xDim != alpbi->biWidth)
	{
		GlobalFreePtr(alpbi);
		return false;
	}
	if (yDim>=0 && yDim != alpbi->biHeight)
	{
		GlobalFreePtr(alpbi);
		return false;
	}
	xDim = alpbi->biWidth;
	yDim = alpbi->biHeight;
	if (nFrames == 0)
	{
		hr = AVIFileOpen(&pfile,		    // returned file pointer
			       FName,							// file name
				   OF_WRITE | OF_CREATE,		    // mode to open file with
				   NULL);							// use handler determined
													// from file extension....
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}
		_fmemset(&strhdr, 0, sizeof(strhdr));
		strhdr.fccType                = streamtypeVIDEO;// stream type
		strhdr.fccHandler             = 0;
		strhdr.dwScale                = 1;
		strhdr.dwRate                 = 15;		    // 15 fps
		strhdr.dwSuggestedBufferSize  = alpbi->biSizeImage;
		SetRect(&strhdr.rcFrame, 0, 0,		    // rectangle for stream
			(int) alpbi->biWidth,
			(int) alpbi->biHeight);

		// And create the stream;
		hr = AVIFileCreateStream(pfile,		    // file pointer
						         &ps,		    // returned stream pointer
								 &strhdr);	    // stream header
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		_fmemset(&opts, 0, sizeof(opts));

		if (!AVISaveOptions(NULL, 0, 1, &ps, (LPAVICOMPRESSOPTIONS FAR *) &aopts))
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		hr = AVIMakeCompressedStream(&psCompressed, ps, &opts, NULL);
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		hr = AVIStreamSetFormat(psCompressed, 0,
					   alpbi,	    // stream format
				       alpbi->biSize +   // format size
				       alpbi->biClrUsed * sizeof(RGBQUAD));
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		// Fill in the stream header for the text stream....

		// The text stream is in 60ths of a second....
/*
		_fmemset(&strhdr, 0, sizeof(strhdr));
		strhdr.fccType                = streamtypeTEXT;
		strhdr.fccHandler             = mmioFOURCC('D', 'R', 'A', 'W');
		strhdr.dwScale                = 1;
		strhdr.dwRate                 = 60;
		strhdr.dwSuggestedBufferSize  = sizeof(szText);
		SetRect(&strhdr.rcFrame, 0, (int) alpbi->biHeight,
			(int) alpbi->biWidth, (int) alpbi->biHeight + TEXT_HEIGHT);

		// ....and create the stream.
		hr = AVIFileCreateStream(pfile, &psText, &strhdr);
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		dwTextFormat = sizeof(dwTextFormat);
		hr = AVIStreamSetFormat(psText, 0, &dwTextFormat, sizeof(dwTextFormat));
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}
*/
	}

	// Jetzt eigentliches Schreiben
	hr = AVIStreamWrite(psCompressed,	// stream pointer
		nFrames * 10,				// time of this frame
		1,				// number to write
		(LPBYTE) alpbi +		// pointer to data
			alpbi->biSize +
			alpbi->biClrUsed * sizeof(RGBQUAD),
			alpbi->biSizeImage,	// size of this frame
		AVIIF_KEYFRAME,			 // flags....
		NULL,
		NULL);
	if (hr != AVIERR_OK)
	{
		GlobalFreePtr(alpbi);
		bOK = false;
		return false;
	}

	// Make some text to put in the file ...
	//LoadString(hInstance, IDS_TEXTFORMAT, szMessage, BUFSIZE );
	/*
	strcpy(szMessage, "This is frame #%d");
		
	int iLen = wsprintf(szText, szMessage, (int)(nFrames + 1));

	// ... and write it as well.
	hr = AVIStreamWrite(psText,
			nFrames * 40,
			1,
			szText,
			iLen + 1,
			AVIIF_KEYFRAME,
			NULL,
			NULL);
	if (hr != AVIERR_OK)
	{
		GlobalFreePtr(alpbi);
		bOK = false;
		return false;
	}
	*/
	GlobalFreePtr(alpbi);

	nFrames++;
	return true;
}