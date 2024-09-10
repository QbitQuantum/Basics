bool LuaProxy::Misc::isSamePath(const std::string first, const std::string second) 
{
    HANDLE hFileFirst = CreateFileA(first.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
    if (hFileFirst == INVALID_HANDLE_VALUE) return false;
    HANDLE hFileSecond = CreateFileA(second.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
    if (hFileSecond == INVALID_HANDLE_VALUE) {
        CloseHandle(hFileFirst);
        return false;
    }

    BY_HANDLE_FILE_INFORMATION fInfoFirst = { 0 };
    BY_HANDLE_FILE_INFORMATION fInfoSecond = { 0 };
    BOOL success = GetFileInformationByHandle(hFileFirst, &fInfoFirst);
    success = success && GetFileInformationByHandle(hFileSecond, &fInfoSecond);
    if (!success) {
        CloseHandle(hFileFirst);
        CloseHandle(hFileSecond);
        return false;
    }

    bool isSame = fInfoFirst.dwVolumeSerialNumber == fInfoSecond.dwVolumeSerialNumber &&
        fInfoFirst.nFileIndexLow == fInfoSecond.nFileIndexLow &&
        fInfoFirst.nFileIndexHigh == fInfoSecond.nFileIndexHigh;

    CloseHandle(hFileFirst);
    CloseHandle(hFileSecond);
    
    return isSame;
}