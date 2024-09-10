sDSTexture* CreateDSGraph(char* path,IDirect3DTexture9** tex) {
    g_userid++;
    HRESULT hr;
    size_t unused;
    wchar_t wpath[256];
    mbstowcs_s(&unused,wpath,256,path,256);
    *tex=NULL;

    sDSTexture* result=new sDSTexture();
    ZeroPointer(result);

    LoadedVideoCount++;

    // Create the Capture Graph Builder.
    hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, 0, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&result->pBuild );
    if(hr!=S_OK) return FreeMovie(result);

    // Create the Filter Graph Manager.
    hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&result->pGraph);
    if(hr!=S_OK) return FreeMovie(result);

    // Initialize the Capture Graph Builder.
    hr = result->pBuild->SetFiltergraph(result->pGraph);
    if(hr!=S_OK) return FreeMovie(result);

    hr = CoCreateInstance(CLSID_VideoMixingRenderer9, 0, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&result->pVmr);
    if(hr!=S_OK) return FreeMovie(result);

    hr = result->pGraph->AddFilter(result->pVmr, L"VMR9");
    if(hr!=S_OK) return FreeMovie(result);

    result->pVmr->QueryInterface(IID_IVMRFilterConfig9, (void**)&result->pConfig);
    result->pConfig->SetRenderingMode(VMR9Mode_Renderless);
    result->pVmr->QueryInterface(IID_IVMRSurfaceAllocatorNotify9,(void**)&result->pAlloc);

    result->pMyAlloc=new CAllocator();

    result->pMyAlloc->AdviseNotify(result->pAlloc);
    result->pAlloc->AdviseSurfaceAllocator(g_userid, (IVMRSurfaceAllocator9*)result->pMyAlloc);

    hr = result->pGraph->QueryInterface(IID_IMediaControl, (void**)&result->pControl);
    hr |= result->pGraph->QueryInterface(IID_IMediaSeeking, (void**)&result->pSeek);
    if(hr!=S_OK) return FreeMovie(result);
    
    //hr = pGraph->RenderFile(L"C:\\Games\\Morrowind\\Data Files\\MGE videos\\test.avi", NULL);
    result->pGraph->RenderFile(wpath, NULL);
    result->pControl->Run();

    *tex=result->pMyAlloc->tex;
    return result;
}