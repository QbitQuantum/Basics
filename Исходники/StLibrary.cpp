StString StLibrary::DLibGetVersion(const StStringUtfWide& theLibPath) {
    DWORD aFVInfoSize = GetFileVersionInfoSizeW(theLibPath.toCString(), NULL);
    if(aFVInfoSize == 0) {
        return StString();
    }
    LPVOID aBlock = stMemAlloc(aFVInfoSize);
    GetFileVersionInfoW(theLibPath.toCString(), NULL, aFVInfoSize, aBlock);
    VS_FIXEDFILEINFO* aFixedInfo;
    UINT aBufferSize;
    stUtfWide_t aPathToSubBlock[] = L"\\";
    if(VerQueryValueW(aBlock, aPathToSubBlock, (LPVOID* )&aFixedInfo, &aBufferSize) == FALSE ||
       aBufferSize < sizeof(VS_FIXEDFILEINFO)) {
        stMemFree(aBlock);
        return StString();
    }
    StString aVersion = StString("ver.")
        + HIWORD(aFixedInfo->dwFileVersionMS) + '.'
        + LOWORD(aFixedInfo->dwFileVersionMS) + '.'
        + HIWORD(aFixedInfo->dwFileVersionLS) + '.'
        + LOWORD(aFixedInfo->dwFileVersionLS);
    stMemFree(aBlock);
    return aVersion;
}