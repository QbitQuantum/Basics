void XApp::destroy()
{
    // Wait for the GPU to be done with all resources.
    //WaitForGpu();
    app->destroy();

    //Sleep(150);
    //CloseHandle(fenceEvent);
#ifdef _DEBUG
    //ThrowIfFailed(DXGIGetDebugInterface1(0, ));
    typedef HRESULT(__stdcall *fPtr)(const IID&, void**);
    HMODULE hDll = GetModuleHandleW(L"dxgidebug.dll");
    fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");
    IDXGIDebug *pDxgiDebug;
    DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&pDxgiDebug);

    //pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);

#endif
}