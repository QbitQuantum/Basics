int main(int argc, char* argv[])
{
	
	
	IGraphBuilder         *pGraph = NULL;
	ICaptureGraphBuilder2 *pBuilder = NULL;
	IBaseFilter           *pSrc = NULL;
	IBaseFilter           *ppf = NULL;
	IFileSinkFilter       *pSink = NULL;
	IMediaControl         *pMC   = NULL;
	HRESULT hr;
	
	CoInitialize (NULL);
	// Create the filter graph.
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
	      IID_IGraphBuilder, (void **)&pGraph);

	// Create the capture graph builder.
	CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, 
	      IID_ICaptureGraphBuilder2, (void **)&pBuilder);

	pBuilder->SetFiltergraph(pGraph);    
	
	pSrc=GetAudioDevice ();
	// add the first audio filter in the list
	pGraph->AddFilter(pSrc, L"Video Capture");

/*	pBuilder->SetOutputFileName(
		&MEDIASUBTYPE_Avi,
		L"C:\\Example.avi", 
		&ppf, 
		&pSink);*/
//	pBuilder->AllocCapFile (L"C:\\temp.avi", _MAX_PATH);

	pBuilder->RenderStream(
        &PIN_CATEGORY_CAPTURE,  // Pin category
        &MEDIATYPE_Audio,       // Media type
        pSrc,                   // Capture filter
        NULL,                   // Compression filter (optional)
        ppf                     // Multiplexer or renderer filter
    );


 
	REFERENCE_TIME  rtStart = 20000000, 
                rtStop = 50000000;

/*	pBuilder->ControlStream(
        &PIN_CATEGORY_CAPTURE, 
        &MEDIATYPE_Audio, 
        pSrc,       // Source filter
        &rtStart,   // Start time
        &rtStop,    // Stop time
        0,          // Start cookie
        0           // Stop cookie
	 );*/

	pGraph->QueryInterface (IID_IMediaControl, (void **) &pMC);
	pMC->Run ();

	MessageBox (NULL, "Stop Recording", NULL, NULL);
	pMC->Stop ();

/*	CProgress *pProg = new CProgress(TEXT(""), NULL, &hr);
        IAMCopyCaptureFileProgress *pIProg = NULL;
        
            hr = pProg->QueryInterface(IID_IAMCopyCaptureFileProgress,
                                            (void **)&pIProg);
	//pBuilder->CopyCaptureFile (L"C:\\temp.avi", L"C:\\final.avi", TRUE, pIProg);*/
   
	CoUninitialize ();
	
	return 0;
}