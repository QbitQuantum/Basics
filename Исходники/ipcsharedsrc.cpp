//-----------------------------------------------------------------------------
// Based on the pid, write a unique name for the IPCBlockTable on Vista and Higher
//-----------------------------------------------------------------------------
HRESULT IPCShared::GenerateBlockTableName(DWORD pid, SString & sName, HANDLE & pBoundaryDesc, HANDLE & pPrivateNamespace, PSID* pSID, BOOL bCreate)
{
    WRAPPER_NO_CONTRACT;
    HRESULT hr = E_FAIL;

#define SIZE 100
    const WCHAR * szFormat = CorSxSPublicIPCBlock;
    static HMODULE hKernel32 = NULL;
    if(hKernel32 == NULL)
        hKernel32 = WszGetModuleHandle(L"kernel32.dll");
    if(hKernel32 == NULL)
    {
        hr = HRESULT_FROM_GetLastError();
        return hr;
    }
    //We are using static function pointers so that we dont call GetProcAddress every time
    //We know that the Writer will call this function only once and the reader (perfmon) is a single
    //threaded App. Therefore its safe to assign static local variables in this case. 
    typedef WINBASEAPI BOOL (WINAPI ADD_SID_TO_BOUNDARY_DESCRIPTOR)(HANDLE*, PSID);
    static ADD_SID_TO_BOUNDARY_DESCRIPTOR * pAddSIDToBoundaryDescriptor = NULL;

    typedef WINBASEAPI HANDLE (WINAPI CREATE_BOUNDARY_DESCRIPTOR)(LPCWSTR,ULONG);
    static CREATE_BOUNDARY_DESCRIPTOR * pCreateBoundaryDescriptor = NULL;
    
    typedef WINBASEAPI HANDLE (WINAPI CREATE_PRIVATE_NAMESPACE )(LPSECURITY_ATTRIBUTES, LPVOID, LPCWSTR);
    static CREATE_PRIVATE_NAMESPACE * pCreatePrivateNamespace = NULL;

    typedef WINBASEAPI HANDLE (WINAPI OPEN_PRIVATE_NAMESPACE)(LPVOID,LPCWSTR);
    static OPEN_PRIVATE_NAMESPACE * pOpenPrivateNamespace = NULL;

    if(pAddSIDToBoundaryDescriptor == NULL)
        pAddSIDToBoundaryDescriptor = (ADD_SID_TO_BOUNDARY_DESCRIPTOR *)GetProcAddress(hKernel32, "AddSIDToBoundaryDescriptor"); 
    if(pCreateBoundaryDescriptor == NULL)
        pCreateBoundaryDescriptor = (CREATE_BOUNDARY_DESCRIPTOR *)GetProcAddress(hKernel32, "CreateBoundaryDescriptorW"); 
    if(pCreatePrivateNamespace == NULL)
        pCreatePrivateNamespace = (CREATE_PRIVATE_NAMESPACE *)GetProcAddress(hKernel32, "CreatePrivateNamespaceW"); 
    if(pOpenPrivateNamespace==NULL)
        pOpenPrivateNamespace = (OPEN_PRIVATE_NAMESPACE *)GetProcAddress(hKernel32, "OpenPrivateNamespaceW");
    _ASSERTE((pAddSIDToBoundaryDescriptor != NULL) && 
            (pCreateBoundaryDescriptor != NULL) && 
            (pCreatePrivateNamespace != NULL) && 
            (pOpenPrivateNamespace != NULL));

    if ((pAddSIDToBoundaryDescriptor == NULL) || 
            (pCreateBoundaryDescriptor == NULL) || 
            (pCreatePrivateNamespace == NULL) || 
            (pOpenPrivateNamespace == NULL))
    {
        return ERROR_PROC_NOT_FOUND;
    }

    WCHAR wsz[SIZE];
    swprintf_s(wsz,SIZE, CorSxSBoundaryDescriptor, pid);

    ULONG flags = 0;
    if (RunningOnWin8())
    {
        // on win8 we specify this flag regardless if the process is inside an appcontainer, the kernel will do the right thing.
        // note that for appcontainers this flag is necessary regardless of producer or consumer, ie you can't create a boundary
        // descriptor in an appcontainer process without adding the appcontainer SID (the API call will fail).
        flags |= CREATE_BOUNDARY_DESCRIPTOR_ADD_APPCONTAINER_SID;
    }

    pBoundaryDesc = (*pCreateBoundaryDescriptor)((LPCWSTR)&wsz, flags);
    if(!pBoundaryDesc)
    {
        hr = HRESULT_FROM_GetLastError();
        return hr;
    }        
    SID_IDENTIFIER_AUTHORITY SIDWorldAuth = SECURITY_WORLD_SID_AUTHORITY;
    if(!AllocateAndInitializeSid( &SIDWorldAuth, 1,SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, pSID)) 
    {
         hr = HRESULT_FROM_GetLastError();
         return hr;
    }
    if(!(*pAddSIDToBoundaryDescriptor) (&pBoundaryDesc,*pSID))
    {
        hr = HRESULT_FROM_GetLastError();
        return hr;
    }

#ifndef FEATURE_CORECLR
    // when pid != GetCurrentProcessId() it means we're the consumer opening other process perf counter data
    if (pid != GetCurrentProcessId())
    {
        // if the target process is inside an appcontainer we need to add the appcontainer SID to the boundary descriptor.
        NewArrayHolder<BYTE> pbTokenMem;
        hr = AppX::GetAppContainerTokenInfoForProcess(pid, pbTokenMem);

        if (FAILED(hr))
        {
            // failed to open the target's process, continue on
            // assuming that the process isn't in an AppContainer.
            _ASSERTE(pbTokenMem == NULL);
        }
        else
        {
            if (hr == S_FALSE)
            {
                // not an appcontainer
                _ASSERTE(pbTokenMem == NULL);
            }
            else
            {
                // process is an appcontainer so add the SID
                PTOKEN_APPCONTAINER_INFORMATION pAppContainerTokenInfo =
                    reinterpret_cast<PTOKEN_APPCONTAINER_INFORMATION>(pbTokenMem.GetValue());
                _ASSERTE(pAppContainerTokenInfo);
                _ASSERTE(pAppContainerTokenInfo->TokenAppContainer);

                if (!(*pAddSIDToBoundaryDescriptor)(&pBoundaryDesc, pAppContainerTokenInfo->TokenAppContainer))
                    return HRESULT_FROM_WIN32(GetLastError());
            }
        }
    }
#endif // FEATURE_CORECLR
    
    if(bCreate)
    {
        SECURITY_ATTRIBUTES *pSA = NULL;
        IPCShared::CreateWinNTDescriptor(pid, FALSE, &pSA, PrivateNamespace, eDescriptor_Public);
        pPrivateNamespace = (*pCreatePrivateNamespace)(pSA, (VOID *)(pBoundaryDesc), 
                                                        (LPCWSTR)CorSxSWriterPrivateNamespacePrefix);
        if(!pPrivateNamespace)
        { 
            hr = HRESULT_FROM_GetLastError();
        }
        IPCShared::DestroySecurityAttributes(pSA);

        if(!pPrivateNamespace)
        { 
            //if already created by a different version of the runtime we return OK.
            if(hr ==HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS))
            {
                hr = S_OK;
            }
            else
            {
                return hr;
            }
        }
     }
     else
     {
        pPrivateNamespace = (*pOpenPrivateNamespace)((VOID *)(pBoundaryDesc), (LPCWSTR)CorSxSReaderPrivateNamespacePrefix);
        if(!pPrivateNamespace)
        { 
            hr = HRESULT_FROM_GetLastError();
            return hr;
        }
     }
    szFormat = (bCreate ? CorSxSWriterPrivateNamespacePrefix L"\\"  CorSxSVistaPublicIPCBlock : CorSxSReaderPrivateNamespacePrefix L"\\"  CorSxSVistaPublicIPCBlock);
    sName.Printf(szFormat);
    hr=S_OK;

    return hr;
}