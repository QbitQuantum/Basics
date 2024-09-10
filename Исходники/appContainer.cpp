HRESULT AppContainerLauncherProcess(LPCWSTR app,LPCWSTR cmdArgs,LPCWSTR workDir)
{
    wchar_t appContainerName[]=L"Phoenix.Container.AppContainer.Profile.v1.test";
    wchar_t appContainerDisplayName[]=L"Phoenix.Container.AppContainer.Profile.v1.test\0";
    wchar_t appContainerDesc[]=L"Phoenix Container Default AppContainer Profile  Test,Revision 1\0";
	DeleteAppContainerProfile(appContainerName);///Remove this AppContainerProfile
    std::vector<SID_AND_ATTRIBUTES> capabilities;
    std::vector<SHARED_SID> capabilitiesSidList;
    if(!MakeWellKnownSIDAttributes(capabilities,capabilitiesSidList))
        return S_FALSE;
    PSID sidImpl;
    HRESULT hr=::CreateAppContainerProfile(appContainerName,
        appContainerDisplayName,
        appContainerDesc,
        (capabilities.empty() ? NULL : &capabilities.front()), capabilities.size(), &sidImpl);
    if(hr!=S_OK){
		std::cout<<"CreateAppContainerProfile Failed"<<std::endl;
		return hr;
	}
	wchar_t *psArgs=nullptr;
    psArgs=_wcsdup(cmdArgs);
    PROCESS_INFORMATION pi;
	STARTUPINFOEX siex = { sizeof(STARTUPINFOEX) };
    siex.StartupInfo.cb = sizeof(STARTUPINFOEXW);
    SIZE_T cbAttributeListSize = 0;
    BOOL bReturn = InitializeProcThreadAttributeList(
        NULL, 3, 0, &cbAttributeListSize);
    siex.lpAttributeList = (PPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), 0, cbAttributeListSize);
    bReturn = InitializeProcThreadAttributeList(siex.lpAttributeList, 3, 0, &cbAttributeListSize);
    SECURITY_CAPABILITIES sc;
    sc.AppContainerSid = sidImpl;
    sc.Capabilities = (capabilities.empty() ? NULL : &capabilities.front());
    sc.CapabilityCount = capabilities.size();
    sc.Reserved = 0;
    if(UpdateProcThreadAttribute(siex.lpAttributeList, 0,
        PROC_THREAD_ATTRIBUTE_SECURITY_CAPABILITIES,
        &sc,
        sizeof(sc) ,
        NULL, NULL)==FALSE)
    {
        goto Cleanup;
    }
    BOOL bRet=CreateProcessW(app, psArgs, nullptr, nullptr,
		FALSE, EXTENDED_STARTUPINFO_PRESENT, NULL, workDir, reinterpret_cast<LPSTARTUPINFOW>(&siex), &pi);
    ::CloseHandle(pi.hThread);
    ::CloseHandle(pi.hProcess);
Cleanup:
    DeleteProcThreadAttributeList(siex.lpAttributeList);
	DeleteAppContainerProfile(appContainerName);
    free(psArgs);
    FreeSid(sidImpl);
    return hr;
}