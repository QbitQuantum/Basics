STDAPI requester_init(void)
{
    vss_ctx.hEventFrozen =  INVALID_HANDLE_VALUE;
    vss_ctx.hEventThaw = INVALID_HANDLE_VALUE;
    vss_ctx.hEventTimeout = INVALID_HANDLE_VALUE;

    COMInitializer initializer; /* to call CoInitializeSecurity */
    HRESULT hr = CoInitializeSecurity(
        NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
        RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE, NULL);
    if (FAILED(hr)) {
        fprintf(stderr, "failed to CoInitializeSecurity (error %lx)\n", hr);
        return hr;
    }

    hLib = LoadLibraryA("VSSAPI.DLL");
    if (!hLib) {
        fprintf(stderr, "failed to load VSSAPI.DLL\n");
        return HRESULT_FROM_WIN32(GetLastError());
    }

    pCreateVssBackupComponents = (t_CreateVssBackupComponents)
        GetProcAddress(hLib,
#ifdef _WIN64 /* 64bit environment */
        "?CreateVssBackupComponents@@YAJPEAPEAVIVssBackupComponents@@@Z"
#else /* 32bit environment */
        "?CreateVssBackupComponents@@YGJPAPAVIVssBackupComponents@@@Z"
#endif
        );
    if (!pCreateVssBackupComponents) {
        fprintf(stderr, "failed to get proc address from VSSAPI.DLL\n");
        return HRESULT_FROM_WIN32(GetLastError());
    }

    pVssFreeSnapshotProperties = (t_VssFreeSnapshotProperties)
        GetProcAddress(hLib, "VssFreeSnapshotProperties");
    if (!pVssFreeSnapshotProperties) {
        fprintf(stderr, "failed to get proc address from VSSAPI.DLL\n");
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}