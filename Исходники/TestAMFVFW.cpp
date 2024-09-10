bool CodecInst::BindDLLs()
{
    if (hModRuntime && AMFInit)
        return true;

    hModRuntime = LoadLibraryW(AMF_DLL_NAME);
    if (hModRuntime)
    {
        AMFInit = (AMFInit_Fn)GetProcAddress(hModRuntime, AMF_INIT_FUNCTION_NAME);
        AMFQueryVersion = (AMFQueryVersion_Fn)GetProcAddress(hModRuntime, AMF_QUERY_VERSION_FUNCTION_NAME);
    }
    else
        LogMsg(true, L"Failed to load AMF runtime DLL (%s)!", AMF_DLL_NAME);

    if (IsWindows8OrGreater() && !hD3DCompiler)
    {
        hD3DCompiler = LoadLibraryA("D3DCOMPILER_47.DLL");
        if (hD3DCompiler)
            pfn_D3DCompile = (decltype(pfn_D3DCompile))GetProcAddress(hD3DCompiler, "D3DCompile");
    }
    return !!hModRuntime && !!AMFInit;
}