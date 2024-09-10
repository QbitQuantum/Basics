MMRESULT EnumerateACMDrivers() {
    AcmDriverList list;

    MMRESULT mmr = acmDriverEnum(
        myAcmDriverEnumCallback,
        reinterpret_cast<DWORD_PTR>(&list), // app-specific pointer
        ACM_DRIVERENUMF_DISABLED // include disabled drivers
    );

    if (MMSYSERR_NOERROR != mmr) {
        ERR(L"acmDriverEnum failed: mmr = 0x%08x", mmr);
        return mmr;
    }
    
    LOG(L"ACM Drivers found: %u", list.nCount);
    for (UINT32 i = 0; i < list.nCount; i++) {
        ACMDRIVERDETAILS details = {0};
        details.cbStruct = sizeof(details);
        
        mmr = acmDriverDetails(list.pDrivers[i].id, &details, 0);
        if (MMSYSERR_NOERROR != mmr) {
            ERR(L"acmDriverDetails failed: mmr = 0x%08x", mmr);
            return mmr;
        }
    
        if (list.pDrivers[i].fdwSupport != details.fdwSupport) {
            ERR(
                L"Different fdwSupport values from "
                L"acmDriverEnum Callback (0x%08x) and acmDriverDetails (0x%08x)",
                list.pDrivers[i].fdwSupport,
                details.fdwSupport
            );
        }
        
        LogDetails(details);
        
        LOG(L""); // blank line
    }
    
    return MMSYSERR_NOERROR;
}