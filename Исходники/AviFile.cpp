HRESULT	CAviFile::AppendFrameFirstTime(int nWidth, int nHeight, LPVOID pBits,int nBitsPerPixel)
{
	int	nMaxWidth=GetSystemMetrics(SM_CXSCREEN),nMaxHeight=GetSystemMetrics(SM_CYSCREEN);

	BITMAPINFO	bmpInfo;

	m_hAviDC=CreateCompatibleDC(NULL);
	if(m_hAviDC==NULL)
	{
		//MessageBox(NULL,"Unable to Create Compatible DC","Error",MB_OK|MB_ICONERROR);
		goto TerminateInitBits;
	}

	ZeroMemory(&bmpInfo,sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biPlanes=1;
	bmpInfo.bmiHeader.biWidth=nWidth;
	bmpInfo.bmiHeader.biHeight=nHeight;
	bmpInfo.bmiHeader.biCompression=BI_RGB;
	bmpInfo.bmiHeader.biBitCount=nBitsPerPixel;
	bmpInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biSizeImage=bmpInfo.bmiHeader.biWidth*bmpInfo.bmiHeader.biHeight*bmpInfo.bmiHeader.biBitCount/8;

	if(bmpInfo.bmiHeader.biHeight>nMaxHeight)	nMaxHeight=bmpInfo.bmiHeader.biHeight;
	if(bmpInfo.bmiHeader.biWidth>nMaxWidth)	nMaxWidth=bmpInfo.bmiHeader.biWidth;

	m_hHeap=HeapCreate(HEAP_NO_SERIALIZE,nMaxWidth*nMaxHeight*4,0);
	if(m_hHeap==NULL)
	{
		//MessageBox(NULL,"Unable to Allocate Memory","Error",MB_OK);
		goto TerminateInitBits;
	}

	m_lpBits=HeapAlloc(m_hHeap,HEAP_ZERO_MEMORY|HEAP_NO_SERIALIZE,nMaxWidth*nMaxHeight*4);
	if(m_lpBits==NULL)
	{
		//MessageBox(NULL,"Unable to Allocate Memory","Error",MB_OK);
		goto TerminateInitBits;
	}

	if(FAILED(AVIFileOpen(&m_pAviFile,m_szFileName,OF_CREATE|OF_WRITE,NULL)))
	{
		//MessageBox(NULL,"Unable to Create the Movie File","Error",MB_OK|MB_ICONERROR);
		goto TerminateInitBits;
	}

	ZeroMemory(&m_AviStreamInfo,sizeof(AVISTREAMINFO));
	m_AviStreamInfo.fccType=streamtypeVIDEO;
	m_AviStreamInfo.fccHandler=VIDEOCODEC;
	m_AviStreamInfo.dwScale=1;
	m_AviStreamInfo.dwRate= FPS;	//Frames Per Second;
	m_AviStreamInfo.dwQuality=-1;	//Default Quality
	m_AviStreamInfo.dwSuggestedBufferSize=nMaxWidth*nMaxHeight*4;
    SetRect(&m_AviStreamInfo.rcFrame,0,0,bmpInfo.bmiHeader.biWidth,bmpInfo.bmiHeader.biHeight);
	strcpy(m_AviStreamInfo.szName,"Video Stream");

	if(FAILED(AVIFileCreateStream(m_pAviFile,&m_pAviStream,&m_AviStreamInfo)))
	{
		//MessageBox(NULL,"Unable to Create Stream","Error",MB_OK|MB_ICONERROR);
		goto TerminateInitBits;

	}

	ZeroMemory(&m_AviCompressOptions,sizeof(AVICOMPRESSOPTIONS));
	m_AviCompressOptions.fccType=streamtypeVIDEO;
	m_AviCompressOptions.fccHandler=m_AviStreamInfo.fccHandler;
	m_AviCompressOptions.dwFlags=AVICOMPRESSF_KEYFRAMES|AVICOMPRESSF_VALID;//|AVICOMPRESSF_DATARATE;
	m_AviCompressOptions.dwKeyFrameEvery=15;
	//m_AviCompressOptions.dwBytesPerSecond=1000/8;
	//m_AviCompressOptions.dwQuality=100;

	if(FAILED(AVIMakeCompressedStream(&m_pAviCompressedStream,m_pAviStream,&m_AviCompressOptions,NULL)))
	{
		//MessageBox(NULL,"Unable to Create Compressed Stream","Error",MB_OK);
		goto TerminateInitBits;
	}

	if(FAILED(AVIStreamSetFormat(m_pAviCompressedStream,0,(LPVOID)&bmpInfo,bmpInfo.bmiHeader.biSize)))
	{
		//MessageBox(NULL,"Unable to Set Format","Error",MB_OK);
		goto TerminateInitBits;
	}

	nAppendFuncSelector=2;		//Point to UsualAppend Function

	return AppendFrameUsual(nWidth,nHeight,pBits,nBitsPerPixel);

TerminateInitBits:

	ReleaseMemory();	MessageBox(NULL,"Error Occured While Rendering the Movie","Error",MB_OK|MB_ICONERROR);

	return E_FAIL;

}