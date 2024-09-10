HRESULT CCodeCoverage::OpenCoverInitialise(IUnknown *pICorProfilerInfoUnk){
	ATLTRACE(_T("::OpenCoverInitialise"));

    OLECHAR szGuid[40]={0};
    int nCount = ::StringFromGUID2(CLSID_CodeCoverage, szGuid, 40);
    RELTRACE(L"    ::Initialize(...) => CLSID == %s", szGuid);
    //::OutputDebugStringW(szGuid);

    WCHAR szExeName[MAX_PATH];
    GetModuleFileNameW(NULL, szExeName, MAX_PATH);
    RELTRACE(L"    ::Initialize(...) => EXE = %s", szExeName);

    WCHAR szModuleName[MAX_PATH];
    GetModuleFileNameW(_AtlModule.m_hModule, szModuleName, MAX_PATH);
    RELTRACE(L"    ::Initialize(...) => PROFILER = %s", szModuleName);
    //::OutputDebugStringW(szModuleName);

    if (g_pProfiler!=NULL) 
        RELTRACE(_T("Another instance of the profiler is running under this process..."));

    m_profilerInfo = pICorProfilerInfoUnk;
    if (m_profilerInfo != NULL) ATLTRACE(_T("    ::Initialize (m_profilerInfo OK)"));
    if (m_profilerInfo == NULL) return E_FAIL;
    m_profilerInfo2 = pICorProfilerInfoUnk;
    if (m_profilerInfo2 != NULL) ATLTRACE(_T("    ::Initialize (m_profilerInfo2 OK)"));
    if (m_profilerInfo2 == NULL) return E_FAIL;
    m_profilerInfo3 = pICorProfilerInfoUnk;
#ifndef _TOOLSETV71
    m_profilerInfo4 = pICorProfilerInfoUnk;
#endif

    ZeroMemory(&m_runtimeVersion, sizeof(m_runtimeVersion));
    if (m_profilerInfo3 != NULL) 
    {
        ATLTRACE(_T("    ::Initialize (m_profilerInfo3 OK)"));
        
        ZeroMemory(&m_runtimeVersion, sizeof(m_runtimeVersion));
        m_profilerInfo3->GetRuntimeInformation(NULL, &m_runtimeType, 
            &m_runtimeVersion.usMajorVersion, 
            &m_runtimeVersion.usMinorVersion, 
            &m_runtimeVersion.usBuildNumber, 
            &m_runtimeVersion.usRevisionNumber, 0, NULL, NULL); 

        ATLTRACE(_T("    ::Initialize (Runtime %d)"), m_runtimeType);
    }

    TCHAR key[1024] = {0};
    ::GetEnvironmentVariable(_T("OpenCover_Profiler_Key"), key, 1024);
    RELTRACE(_T("    ::Initialize(...) => key = %s"), key);

    TCHAR ns[1024] = {0};
    ::GetEnvironmentVariable(_T("OpenCover_Profiler_Namespace"), ns, 1024);
    ATLTRACE(_T("    ::Initialize(...) => ns = %s"), ns);

    TCHAR instrumentation[1024] = {0};
    ::GetEnvironmentVariable(_T("OpenCover_Profiler_Instrumentation"), instrumentation, 1024);
    ATLTRACE(_T("    ::Initialize(...) => instrumentation = %s"), instrumentation);

    TCHAR threshold[1024] = {0};
    ::GetEnvironmentVariable(_T("OpenCover_Profiler_Threshold"), threshold, 1024);
    m_threshold = _tcstoul(threshold, NULL, 10);
    ATLTRACE(_T("    ::Initialize(...) => threshold = %ul"), m_threshold);

    TCHAR tracebyTest[1024] = {0};
    ::GetEnvironmentVariable(_T("OpenCover_Profiler_TraceByTest"), tracebyTest, 1024);
    m_tracingEnabled = _tcslen(tracebyTest) != 0;
	ATLTRACE(_T("    ::Initialize(...) => tracingEnabled = %s (%s)"), m_tracingEnabled ? _T("true") : _T("false"), tracebyTest);


    m_useOldStyle = (tstring(instrumentation) == _T("oldSchool"));

    if (!m_host.Initialise(key, ns))
    {
        RELTRACE(_T("    ::Initialize => Failed to initialise the profiler communications -> GetLastError() => %d"), ::GetLastError());
        return E_FAIL;
    }

    OpenCoverSupportInitialize(pICorProfilerInfoUnk);

	if (m_chainedProfiler == NULL){
		DWORD dwMask = AppendProfilerEventMask(0); 

		COM_FAIL_MSG_RETURN_ERROR(m_profilerInfo2->SetEventMask(dwMask),
			_T("    ::Initialize(...) => SetEventMask => 0x%X"));
	}

    if(m_profilerInfo3 != NULL)
    {
        COM_FAIL_MSG_RETURN_ERROR(m_profilerInfo3->SetFunctionIDMapper2(FunctionMapper2, this), 
            _T("    ::Initialize(...) => SetFunctionIDMapper2 => 0x%X"));
    }
    else
    {
        COM_FAIL_MSG_RETURN_ERROR(m_profilerInfo2->SetFunctionIDMapper(FunctionMapper), 
            _T("    ::Initialize(...) => SetFunctionIDMapper => 0x%X"));
    }

    g_pProfiler = this;

#ifndef _TOOLSETV71
    COM_FAIL_MSG_RETURN_ERROR(m_profilerInfo2->SetEnterLeaveFunctionHooks2(
        _FunctionEnter2, _FunctionLeave2, _FunctionTailcall2), 
        _T("    ::Initialize(...) => SetEnterLeaveFunctionHooks2 => 0x%X"));
#endif
    RELTRACE(_T("::Initialize - Done!"));
    
    return S_OK; 
}