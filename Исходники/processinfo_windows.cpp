bool getFileVersion(const char* filePath, DWORD& fileVersionMS, DWORD& fileVersionLS) {
    DWORD verSize = GetFileVersionInfoSizeA(filePath, NULL);
    if (verSize == 0) {
        DWORD gle = GetLastError();
        warning() << "GetFileVersionInfoSizeA on " << filePath << " failed with "
                  << errnoWithDescription(gle);
        return false;
    }

    std::unique_ptr<char[]> verData(new char[verSize]);
    if (GetFileVersionInfoA(filePath, NULL, verSize, verData.get()) == 0) {
        DWORD gle = GetLastError();
        warning() << "GetFileVersionInfoSizeA on " << filePath << " failed with "
                  << errnoWithDescription(gle);
        return false;
    }

    UINT size;
    VS_FIXEDFILEINFO* verInfo;
    if (VerQueryValueA(verData.get(), "\\", (LPVOID*)&verInfo, &size) == 0) {
        DWORD gle = GetLastError();
        warning() << "VerQueryValueA on " << filePath << " failed with "
                  << errnoWithDescription(gle);
        return false;
    }

    if (size != sizeof(VS_FIXEDFILEINFO)) {
        warning() << "VerQueryValueA on " << filePath << " returned structure with unexpected size";
        return false;
    }

    fileVersionMS = verInfo->dwFileVersionMS;
    fileVersionLS = verInfo->dwFileVersionLS;
    return true;
}