static int v4w_open_videodevice(V4wState *s)
{
	// Initialize COM
	CoInitialize(NULL);

	// get a Graph
	HRESULT hr= CoCreateInstance (CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, //IID_IBaseFilter,
		(void **)&s->m_pGraph);
	if(FAILED(hr))
	{
		return -1;
	}

	// get a CaptureGraphBuilder2
	hr= CoCreateInstance (CLSID_CaptureGraphBuilder2,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ICaptureGraphBuilder2, //IID_IBaseFilter,
		(void **)&s->m_pBuilder);
	if(FAILED(hr))
	{
		return -2;
	}

	// connect capture graph builder with the graph
	s->m_pBuilder->SetFiltergraph(s->m_pGraph);

	// get mediacontrol so we can start and stop the filter graph
	hr=s->m_pGraph->QueryInterface (IID_IMediaControl, (void **)&s->m_pControl);
	if(FAILED(hr))
	{
		return -3;
	}


	ICreateDevEnum *pCreateDevEnum = NULL;
	IEnumMoniker *pEnumMoniker = NULL;
	IMoniker *pMoniker = NULL;

	ULONG nFetched = 0;

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, 
		IID_ICreateDevEnum, (PVOID *)&pCreateDevEnum);
	if(FAILED(hr))
	{
		return -4;
	}

	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
		&pEnumMoniker, 0);
	if (FAILED(hr) || pEnumMoniker == NULL) {
		//printf("no device\n");
		return -5;
	}

	pEnumMoniker->Reset();

	int pos=0;
	while(S_OK == pEnumMoniker->Next(1, &pMoniker, &nFetched) )
	{
		IPropertyBag *pBag;
		hr = pMoniker->BindToStorage( 0, 0, IID_IPropertyBag, (void**) &pBag );
		if( hr != S_OK )
			continue; 

		if (s->dev[0]=='\0')
			break;

		VARIANT var;
		VariantInit(&var);
		hr = pBag->Read( L"FriendlyName", &var, NULL ); 
		if( hr != S_OK )
		{
			pMoniker->Release();
			continue;
		}
		//USES_CONVERSION;
		char szName[256];

		WideCharToMultiByte(CP_UTF8,0,var.bstrVal,-1,szName,256,0,0);
		VariantClear(&var); 

		if (strcmp(szName, s->dev)==0)
			break;

		pMoniker->Release();
		pBag->Release();
		pMoniker=NULL;
		pBag=NULL;
	}

	if(pMoniker==NULL)
	{
		return -6;
	}

	hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&s->m_pDeviceFilter );
	if(FAILED(hr))
	{
		return -7;
	}

	s->m_pGraph->AddFilter(s->m_pDeviceFilter, L"Device Filter");

	pMoniker->Release();
	pEnumMoniker->Release();
	pCreateDevEnum->Release();


	GUID pPinCategory;

	if (try_format(s->m_pDeviceFilter, s->pix_fmt, &pPinCategory)==0)
		s->pix_fmt = s->pix_fmt;
	else if (try_format(s->m_pDeviceFilter,MS_YUV420P, &pPinCategory)==0)
		s->pix_fmt = MS_YUV420P;
	else if (try_format(s->m_pDeviceFilter,MS_YUY2, &pPinCategory)==0)
		s->pix_fmt = MS_YUY2;
	else if (try_format(s->m_pDeviceFilter,MS_YUYV, &pPinCategory)==0)
		s->pix_fmt = MS_YUYV;
	else if (try_format(s->m_pDeviceFilter,MS_UYVY, &pPinCategory)==0)
		s->pix_fmt = MS_UYVY;
	else if (try_format(s->m_pDeviceFilter,MS_RGB24, &pPinCategory)==0)
		s->pix_fmt = MS_RGB24;
	else
	{
		ms_error("Unsupported video pixel format.");
		return -8;
	}

	if (s->pix_fmt == MS_YUV420P)
		ms_message("Driver supports YUV420P, using that format.");
	else if (s->pix_fmt == MS_YUY2)
		ms_message("Driver supports YUY2 (YUYV), using that format.");
	else if (s->pix_fmt == MS_YUYV)
		ms_message("Driver supports YUV422, using that format.");
	else if (s->pix_fmt == MS_UYVY)
		ms_message("Driver supports UYVY, using that format.");
	else if (s->pix_fmt == MS_RGB24)
		ms_message("Driver supports RGB24, using that format.");

	if (try_format_size(s, s->pix_fmt, s->vsize.width, s->vsize.height, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", s->vsize.width, s->vsize.height);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_QCIF_W, MS_VIDEO_SIZE_QCIF_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_QCIF_W, MS_VIDEO_SIZE_QCIF_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_CIF_W, MS_VIDEO_SIZE_CIF_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_CIF_W, MS_VIDEO_SIZE_CIF_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_4CIF_W, MS_VIDEO_SIZE_4CIF_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_4CIF_W, MS_VIDEO_SIZE_4CIF_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_QVGA_W, MS_VIDEO_SIZE_QVGA_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_QVGA_W, MS_VIDEO_SIZE_QVGA_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_QQVGA_W, MS_VIDEO_SIZE_QQVGA_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_QQVGA_W, MS_VIDEO_SIZE_QQVGA_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_NS1_W, MS_VIDEO_SIZE_NS1_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_NS1_W, MS_VIDEO_SIZE_NS1_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_QSIF_W, MS_VIDEO_SIZE_QSIF_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_QSIF_W, MS_VIDEO_SIZE_QSIF_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_SIF_W, MS_VIDEO_SIZE_SIF_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_SIF_W, MS_VIDEO_SIZE_SIF_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_VGA_W, MS_VIDEO_SIZE_VGA_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_VGA_W, MS_VIDEO_SIZE_VGA_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_SDTV_W, MS_VIDEO_SIZE_SDTV_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_SDTV_W, MS_VIDEO_SIZE_SDTV_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_288P_W, MS_VIDEO_SIZE_288P_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_288P_W, MS_VIDEO_SIZE_288P_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_448P_W, MS_VIDEO_SIZE_448P_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_448P_W, MS_VIDEO_SIZE_448P_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_576P_W, MS_VIDEO_SIZE_576P_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_576P_W, MS_VIDEO_SIZE_576P_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_720P_W, MS_VIDEO_SIZE_720P_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_720P_W, MS_VIDEO_SIZE_720P_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_1080P_W, MS_VIDEO_SIZE_1080P_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_1080P_W, MS_VIDEO_SIZE_1080P_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_4SIF_W, MS_VIDEO_SIZE_4SIF_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_4SIF_W, MS_VIDEO_SIZE_4SIF_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_SVGA_W, MS_VIDEO_SIZE_SVGA_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_SVGA_W, MS_VIDEO_SIZE_SVGA_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_XGA_W, MS_VIDEO_SIZE_XGA_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_XGA_W, MS_VIDEO_SIZE_XGA_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_WXGA_W, MS_VIDEO_SIZE_WXGA_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_WXGA_W, MS_VIDEO_SIZE_WXGA_H);
	else if (try_format_size(s, s->pix_fmt, MS_VIDEO_SIZE_HDTVP_W, MS_VIDEO_SIZE_HDTVP_H, &pPinCategory)==0)
		ms_message("Selected Size: %ix%i.", MS_VIDEO_SIZE_HDTVP_W, MS_VIDEO_SIZE_HDTVP_H);
	else
	{
		ms_error("No supported size found for format.");
		/* size not supported? */
		return -9;
	}

	// get DXFilter
	s->m_pDXFilter = new CDXFilter(NULL, &hr, FALSE);
	if(s->m_pDXFilter==NULL)
	{
		return -10;
	}
	s->m_pDXFilter->AddRef();

	CMediaType mt;
	mt.SetType(&MEDIATYPE_Video);

	GUID m = MEDIASUBTYPE_RGB24;
	if (s->pix_fmt == MS_YUV420P)
		m = (GUID)FOURCCMap(MAKEFOURCC('I','4','2','0'));
	else if (s->pix_fmt == MS_YUY2)
		m = MEDIASUBTYPE_YUY2;
	else if (s->pix_fmt == MS_YUYV)
		m = MEDIASUBTYPE_YUYV;
	else if (s->pix_fmt == MS_UYVY)
		m = MEDIASUBTYPE_UYVY;
	else if (s->pix_fmt == MS_RGB24)
		m = MEDIASUBTYPE_RGB24;
	mt.SetSubtype(&m);

	mt.formattype = FORMAT_VideoInfo;
	mt.SetTemporalCompression(FALSE);

	VIDEOINFO *pvi = (VIDEOINFO *)
		mt.AllocFormatBuffer(sizeof(VIDEOINFO));
	if (NULL == pvi)
		return -11;
	ZeroMemory(pvi, sizeof(VIDEOINFO));

	if (s->pix_fmt == MS_YUV420P)
		pvi->bmiHeader.biCompression = MAKEFOURCC('I','4','2','0');
	else if (s->pix_fmt == MS_YUY2)
		pvi->bmiHeader.biCompression = MAKEFOURCC('Y','U','Y','2');
	else if (s->pix_fmt == MS_YUYV)
		pvi->bmiHeader.biCompression = MAKEFOURCC('Y','U','Y','V');
	else if (s->pix_fmt == MS_UYVY)
		pvi->bmiHeader.biCompression = MAKEFOURCC('U','Y','V','Y');
	else if (s->pix_fmt == MS_RGB24)
		pvi->bmiHeader.biCompression = BI_RGB;

	if (s->pix_fmt == MS_YUV420P)
		pvi->bmiHeader.biBitCount = 12;
	else if (s->pix_fmt == MS_YUY2)
		pvi->bmiHeader.biBitCount = 16;
	else if (s->pix_fmt == MS_YUYV)
		pvi->bmiHeader.biBitCount = 16;
	else if (s->pix_fmt == MS_UYVY)
		pvi->bmiHeader.biBitCount = 16;
	else if (s->pix_fmt == MS_RGB24)
		pvi->bmiHeader.biBitCount = 24;

	pvi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pvi->bmiHeader.biWidth = s->vsize.width;
	pvi->bmiHeader.biHeight = s->vsize.height;
	pvi->bmiHeader.biPlanes = 1;
	pvi->bmiHeader.biSizeImage = GetBitmapSize(&pvi->bmiHeader);
	pvi->bmiHeader.biClrImportant = 0;
	mt.SetSampleSize(pvi->bmiHeader.biSizeImage);

	mt.SetFormat((BYTE*)pvi, sizeof(VIDEOINFO));

	hr = s->m_pDXFilter->SetAcceptedMediaType(&mt);
	if(FAILED(hr))
	{
		return -12;
	}

	hr = s->m_pDXFilter->SetCallback(Callback); 
	if(FAILED(hr))
	{
		return -13;
	}

	hr = s->m_pDXFilter->QueryInterface(IID_IBaseFilter,
		(LPVOID *)&s->m_pIDXFilter);
	if(FAILED(hr))
	{
		return -14;
	}

	hr = s->m_pGraph->AddFilter(s->m_pIDXFilter, L"DXFilter Filter");
	if(FAILED(hr))
	{
		return -15;
	}


	// get null renderer
	hr=CoCreateInstance (CLSID_NullRenderer,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IBaseFilter,
		(void **)&s->m_pNullRenderer);
	if(FAILED(hr))
	{
		return -16;
	}
	if (s->m_pNullRenderer!=NULL)
	{
		s->m_pGraph->AddFilter(s->m_pNullRenderer, L"Null Renderer");
	}

	hr = s->m_pBuilder->RenderStream(&pPinCategory,
		&MEDIATYPE_Video, s->m_pDeviceFilter, s->m_pIDXFilter, s->m_pNullRenderer);
	if (FAILED(hr))
	{
		return -17;
	}

	IAMStreamConfig *pConfig = NULL;
	hr = s->m_pBuilder->FindInterface(
		&pPinCategory, // Preview pin.
		&MEDIATYPE_Video,    // Any media type.
		s->m_pDeviceFilter, // Pointer to the capture filter.
		IID_IAMStreamConfig, (void**)&pConfig); 
	if (pConfig!=NULL)
	{
		AM_MEDIA_TYPE *pType = NULL;
		int iCount, iSize;
		pConfig->GetNumberOfCapabilities(&iCount, &iSize);

		for (int i = 0; i < iCount; i++) {
			VIDEO_STREAM_CONFIG_CAPS scc;
			pType = NULL;
			pConfig->GetStreamCaps(i, &pType, (BYTE *)&scc);

			if (!((pType->formattype == FORMAT_VideoInfo) &&
				(pType->cbFormat >= sizeof(VIDEOINFOHEADER)) &&
				(pType->pbFormat != NULL)))
				continue;

			VIDEOINFOHEADER & videoInfo = *(VIDEOINFOHEADER *)pType->pbFormat;

			if (m != pType->subtype)
				continue;

			if (videoInfo.bmiHeader.biWidth != s->vsize.width)
				continue;

			if (videoInfo.bmiHeader.biHeight != s->vsize.height)
				continue;

			if (videoInfo.bmiHeader.biBitCount != pvi->bmiHeader.biBitCount)
				continue;

			if (videoInfo.bmiHeader.biCompression != pvi->bmiHeader.biCompression)
				continue;

			videoInfo.AvgTimePerFrame = UNITS / (LONGLONG)s->fps;
			pConfig->SetFormat(pType);    
		}

		pConfig->GetFormat(&pType);
		if (pType!=NULL)
		{
			VIDEOINFO *pvi;
			pvi = (VIDEOINFO *)pType->pbFormat;
			ms_message("v4w: camera asked fps=%.2f // real fps=%.2f", s->fps, ((float)UNITS / (float)pvi->AvgTimePerFrame));
		}

		pConfig->Release();
	}

	//m_pDXFilter->SetBufferSamples(TRUE);

	s_callback = s;
	hr = s->m_pControl->Run();
	if(FAILED(hr))
	{
		return -18;
	}


	s->rotregvalue=1;
	return 0;
}