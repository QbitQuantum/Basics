void DirectShowFrameGrabber::init() {
	InitializeDirectX();
	HRESULT hr = S_OK;
	mediaEvent = NULL;
	mediaControl = NULL;
	sampleGrabber = NULL;
	buffer = NULL;
	bufferLength = 0;
	width = 640; // just default, will be overriden
	height = 480;  // just default, will be overriden

	CComPtr<IBaseFilter> captureFilter = NULL;

	// choose video capture device
	hr = ChooseDirectXFilter(captureFilter, CLSID_VideoInputDeviceCategory);

	ASSERT(SUCCEEDED(hr));
	//ASSERT(captureFilter != NULL, "no capturing device available!");
	CComPtr<IBaseFilter> sampleGrabberFilter = NULL;
	hr = sampleGrabberFilter.CoCreateInstance(CLSID_SampleGrabber);
	ASSERT(SUCCEEDED(hr));
	CComPtr<IBaseFilter> nullRendererFilter = NULL;
	hr = nullRendererFilter.CoCreateInstance(CLSID_NullRenderer);
	ASSERT(SUCCEEDED(hr));
	graphBuilder = NULL;
	hr = graphBuilder.CoCreateInstance(CLSID_FilterGraph);


	ASSERT(SUCCEEDED(hr));
	IMediaFilter *mediaFilter = 0;
	graphBuilder->QueryInterface(IID_IMediaFilter, (void**)&mediaFilter);
	mediaFilter->SetSyncSource(NULL);	  
	mediaFilter->Release();
	

	hr = graphBuilder->AddFilter(captureFilter, NULL);	  
	ASSERT(SUCCEEDED(hr));

	// open ui with video capture device properties
	displayProperties( captureFilter );

	hr = graphBuilder->AddFilter(nullRendererFilter, L"NullRenderer");
	ASSERT(SUCCEEDED(hr));
	hr = graphBuilder->AddFilter(sampleGrabberFilter, L"Grabber");
	ASSERT(SUCCEEDED(hr));


	hr = sampleGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&sampleGrabber);
	ASSERT(SUCCEEDED(hr));

	AM_MEDIA_TYPE mediaType;
	ZeroMemory(&mediaType, sizeof(AM_MEDIA_TYPE));
	mediaType.majortype = MEDIATYPE_Video;
	mediaType.subtype = MEDIASUBTYPE_RGB24;
	mediaType.formattype = FORMAT_VideoInfo; 
	hr = sampleGrabber->SetMediaType(&mediaType);
	ASSERT(SUCCEEDED(hr));

	CComPtr<IEnumPins> pins = NULL;
	CComPtr<IPin> cameraOutputPin = NULL;

	{
		hr = captureFilter->EnumPins(&pins);
		ASSERT(SUCCEEDED(hr));
		hr = pins->Reset();
		ASSERT(SUCCEEDED(hr));
		
		hr = pins->Next(1, &cameraOutputPin, NULL); 
		ASSERT(SUCCEEDED(hr));
		pins = NULL; 
	}


	hr = sampleGrabberFilter->EnumPins(&pins);
	ASSERT(SUCCEEDED(hr));
	hr = pins->Reset();
	ASSERT(SUCCEEDED(hr));
	CComPtr<IPin> grabberInputPin = NULL;
	hr = pins->Next(1, &grabberInputPin, NULL);
	ASSERT(SUCCEEDED(hr));
	CComPtr<IPin> grabberOutputPin = NULL;
	hr = pins->Next(1, &grabberOutputPin, NULL);
	ASSERT(SUCCEEDED(hr));
	pins = NULL;
	hr = nullRendererFilter->EnumPins(&pins);
	ASSERT(SUCCEEDED(hr));
	hr = pins->Reset();
	ASSERT(SUCCEEDED(hr));
	CComPtr<IPin> nullRendererInputPin = NULL;
	hr = pins->Next(1, &nullRendererInputPin, NULL);
	ASSERT(SUCCEEDED(hr));

	// show camera properties
		CComPtr<ISpecifyPropertyPages> propertyPages;
		hr = cameraOutputPin->QueryInterface(IID_ISpecifyPropertyPages, (void**)&propertyPages);
		if (SUCCEEDED(hr)) {
			PIN_INFO pinInfo;
			cameraOutputPin->QueryPinInfo(&pinInfo);
			CAUUID caGUID;
			propertyPages->GetPages(&caGUID);
			OleCreatePropertyFrame(NULL, 0, 0, L"Property Sheet", 1,
				(IUnknown **)&(cameraOutputPin.p), caGUID.cElems,
				caGUID.pElems, 0, 0, NULL);
			CoTaskMemFree(caGUID.pElems);
			pinInfo.pFilter->Release();
		}


	hr = graphBuilder->Connect(cameraOutputPin, grabberInputPin);
	ASSERT(SUCCEEDED(hr));
	hr = graphBuilder->Connect(grabberOutputPin, nullRendererInputPin);
	ASSERT(SUCCEEDED(hr));

	hr = graphBuilder->Render(grabberOutputPin);
	//      ASSERT(SUCCEEDED(hr)); // produces an error: "An invalid field name was used in a query string"

	hr = sampleGrabber->SetBufferSamples(TRUE);
	ASSERT(SUCCEEDED(hr));
	hr = sampleGrabber->SetOneShot(FALSE);
	ASSERT(SUCCEEDED(hr));
	hr = graphBuilder->QueryInterface(IID_IMediaControl, (void**)&mediaControl);
	ASSERT(SUCCEEDED(hr));
	hr = graphBuilder->QueryInterface(IID_IMediaEvent, (void**)&mediaEvent);
	ASSERT(SUCCEEDED(hr));
	AM_MEDIA_TYPE mt;
	hr = sampleGrabber->GetConnectedMediaType(&mt);
	ASSERT(SUCCEEDED(hr));
	ASSERT(mt.formattype == FORMAT_VideoInfo);
	VIDEOINFOHEADER *videoHeader;
	videoHeader = reinterpret_cast<VIDEOINFOHEADER*>(mt.pbFormat);
	width = videoHeader->bmiHeader.biWidth;
	height = videoHeader->bmiHeader.biHeight;
	bitmapFormat = 0;
	CComPtr<IAMVideoControl> videoControl;
	hr = captureFilter->QueryInterface(IID_IAMVideoControl, (void**)&videoControl);
	
	// run the graph!
	mediaControl->Run();
}