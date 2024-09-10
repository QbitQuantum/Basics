void CAviHelper::AVItoBmp(const wstring& strAVIFileName, const wstring& strBmpDir)
{
	AVIFileInit();
	PAVIFILE avi;
	int res = AVIFileOpen(&avi, WS2S(strAVIFileName).c_str(), OF_READ, NULL);
	int n = GetLastError();
	if (res!=AVIERR_OK)
	{
		//an error occures
		if (avi!=NULL)
			AVIFileRelease(avi);
		return ;
	}
	
	AVIFILEINFO avi_info;
	AVIFileInfo(avi, &avi_info, sizeof(AVIFILEINFO));
	PAVISTREAM pStream;
	res=AVIFileGetStream(avi, &pStream, streamtypeVIDEO /*video stream*/, 0 /*first stream*/);
	if (res!=AVIERR_OK)
	{
		if (pStream!=NULL)
			AVIStreamRelease(pStream);
		AVIFileExit();
		return ;
	}
	
	//do some task with the stream
	int iNumFrames;
	int iFirstFrame;
	iFirstFrame = AVIStreamStart(pStream);
	if (iFirstFrame==-1)
	{
		//Error getteing the frame inside the stream
		if (pStream!=NULL)
			AVIStreamRelease(pStream);
		AVIFileExit();
		return ;
	}
	
	iNumFrames = AVIStreamLength(pStream);
	if (iNumFrames==-1)
	{
		//Error getteing the number of frames inside the stream
		if (pStream!=NULL)
			AVIStreamRelease(pStream);
		AVIFileExit();
		return ;
	}
	
	//getting bitmap from frame
	BITMAPINFOHEADER bih;
	ZeroMemory(&bih, sizeof(BITMAPINFOHEADER));
	bih.biBitCount=24; //24 bit per pixel
	bih.biClrImportant=0;
	bih.biClrUsed = 0;
	bih.biCompression = BI_RGB;
	bih.biPlanes = 1;
	bih.biSize = 40;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	
	//calculate total size of RGBQUAD scanlines (DWORD aligned)
	bih.biSizeImage = (((bih.biWidth * 3) + 3) & 0xFFFC) * bih.biHeight ;
	PGETFRAME pFrame;
	pFrame=AVIStreamGetFrameOpen(pStream, NULL );
	AVISTREAMINFO streaminfo;
	AVIStreamInfo(pStream,&streaminfo,sizeof(AVISTREAMINFO));
	
	//Get the first frame
	BITMAPINFOHEADER bih2;
	long lsize = sizeof(bih2);
	int index= 0;
	for (int i = iFirstFrame; i < iNumFrames; i++)
	{
		index= i-iFirstFrame;
		BYTE* pDIB = (BYTE*) AVIStreamGetFrame(pFrame, index); //
		AVIStreamReadFormat(pStream,index,&bih2,&lsize);
		BITMAPFILEHEADER stFileHdr;
		BYTE* Bits=new BYTE[bih2.biSizeImage];
		AVIStreamRead(pStream,index,1,Bits,bih2.biSizeImage,NULL,NULL);
		//RtlMoveMemory(Bits, pDIB + sizeof(BITMAPINFOHEADER), bih2.biSizeImage);
		bih2.biClrUsed =0;
		stFileHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
		stFileHdr.bfSize=sizeof(BITMAPFILEHEADER);
		stFileHdr.bfType=0x4d42; 
		CString FileName;
		FileName.Format(_T("Frame-%05d.bmp"), index);
		CString strtemp;
		strtemp.Format(_T("%s\\%s"), strBmpDir.c_str(), FileName);
		FILE* fp=_tfopen(strtemp ,_T("wb"));
		fwrite(&stFileHdr,1,sizeof(BITMAPFILEHEADER),fp);
		fwrite(&bih2,1,sizeof(BITMAPINFOHEADER),fp);
		int ff = fwrite(Bits,1,bih2.biSizeImage,fp);
		int e = GetLastError();
		fclose(fp);
		/////
		delete Bits;
		//CreateFromPackedDIBPointer(pDIB, index);
	}
	
	AVIStreamGetFrameClose(pFrame);
	//close the stream after finishing the task
	if (pStream!=NULL)
		AVIStreamRelease(pStream);
	AVIFileExit();
}