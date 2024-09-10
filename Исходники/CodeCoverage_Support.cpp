HRESULT CCodeCoverage::OpenCoverSupportInitialize(
    /* [in] */ IUnknown *pICorProfilerInfoUnk) {
    TCHAR ext[1024] = { 0 };
    ::GetEnvironmentVariable(_T("CHAIN_EXTERNAL_PROFILER"), ext, 1024);
    if (ext[0] != 0) {
		#ifdef TRACE_ENABLED
		ATLTRACE(_T("::OpenCoverSupportInitialize"));

        ATLTRACE(_T("    ::OpenCoverSupportInitialize(...) => ext = %s"), ext);
		#endif

        TCHAR loc[1024] = { 0 };
        ::GetEnvironmentVariable(_T("CHAIN_EXTERNAL_PROFILER_LOCATION"), loc, 1024);
		#ifdef TRACE_ENABLED
    	ATLTRACE(_T("    ::OpenCoverSupportInitialize(...) => loc = %s"), loc);
		#endif

        if (PathFileExists(loc)) {
            CLSID clsid;
            HRESULT hr = CLSIDFromString(T2OLE(ext), &clsid);
            ATLASSERT(hr == S_OK);

            chained_module_ = LoadLibrary(loc);
            ATLASSERT(chained_module_ != NULL);

            HRESULT(WINAPI*DllGetClassObject)(REFCLSID, REFIID, LPVOID) =
                (HRESULT(WINAPI*)(REFCLSID, REFIID, LPVOID))GetProcAddress(chained_module_, "DllGetClassObject");
            ATLASSERT(DllGetClassObject != NULL);

            CComPtr<IClassFactory> pClassFactory;
            hr = DllGetClassObject(clsid, IID_IClassFactory, &pClassFactory);
            ATLASSERT(hr == S_OK);

			CComPtr<ICorProfilerCallback> chainedProfiler;
            hr = pClassFactory->CreateInstance(nullptr, __uuidof(ICorProfilerCallback), (void**)&chainedProfiler);
            ATLASSERT(hr == S_OK);

            HRESULT hr2 = CComObject<CProfilerInfo>::CreateInstance(&m_infoHook);
            ULONG count = m_infoHook->AddRef();

            m_infoHook->SetProfilerHook(this);

            m_infoHook->ChainProfilerInfo(pICorProfilerInfoUnk);

            hr = chainedProfiler->Initialize(m_infoHook);

			HookChainedProfiler(chainedProfiler);

			#ifdef TRACE_ENABLED
            ATLTRACE(_T("    ::OpenCoverSupportInitialize => fakes = 0x%X"), hr);
			#endif
        }
        else {
			#ifdef TRACE_ENABLED
            RELTRACE(_T("    ::OpenCoverSupportInitialize => Failed to locate external profiler at '%s'"), loc);
			#endif
        }
    }

    return S_OK;
}